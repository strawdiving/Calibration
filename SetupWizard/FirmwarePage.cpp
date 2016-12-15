#include "FirmwarePage.h"

#include <QStandardPaths>
#include <QUrl>
#include <QMessageBox>

FirmwarePage::FirmwarePage(QWidget *parent) :
    QWidget(parent)
{
    _title = new TitleLabel(tr("Firmware Upgrade"));

    _statusTextArea = new QTextBrowser();
    _progressBar = new QProgressBar();
    _updateBtn = new QPushButton(tr("固件更新"));
    _updateBtn->setEnabled(false);
    connect(_updateBtn,SIGNAL(clicked()),this,SLOT(_flash()));

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(_title,0,0,1,1);
    layout->addWidget(_progressBar,1,0,1,4);
    layout->addWidget(_statusTextArea,2,0,2,4);
    layout->addWidget(_updateBtn,4,3,1,1);
    layout->setSpacing(20);
    this->setLayout(layout);

    _controller = new PX4FirmUpgradeThreadController();
    connect(_controller,SIGNAL(updateProgress(int,int)),this,SLOT(_updateProgress(int,int)));
    connect(_controller,SIGNAL(foundBoard(bool,QString,QString)),this,SLOT(_foundBoard(bool,QString,QString)));
    connect(_controller,SIGNAL(noBoardFound()),this,SLOT(_noBoardFound()));
    connect(_controller,SIGNAL(boardGone()),this,SLOT(_boardGone()));
    connect(_controller,SIGNAL(error(QString)),this,SLOT(_error(QString)));
    connect(_controller,SIGNAL(foundBootloader(int,int,int)),this,SLOT(_foundBootloader(int,int,int)));
    connect(_controller,SIGNAL(eraseStarted()),this,SLOT(_eraseStarted()));
    connect(_controller,SIGNAL(eraseCompleted()),this,SLOT(_eraseCompleted()));
    connect(_controller,SIGNAL(flashCompleted()),this,SLOT(_flashCompleted()));

    connect(&_eraseTimer,SIGNAL(timeout()),this,SLOT(_eraseProgress()));

    _controller->startFindBoard();
}

FirmwarePage::~FirmwarePage()
{
}

void FirmwarePage::_flash()
{
 qDebug()<<"update firmware:flash";
 _updateBtn->setEnabled(false);
 _getFimwareFile();
}

void FirmwarePage::_getFimwareFile()
{
 if(_bootloaderBoardID == boardIDPX4FMUV2)
 {
     _firmwareFilename = "http://px4-travis.s3.amazonaws.com/Firmware/stable/px4fmu-v2_default.px4";
   // _firmwareFilename = "http://pic101.nipic.com/file/20160615/13948737_131159994001_2.jpg";
     _status("---------------  Update  ------------------",true);
     _downloadFirmware();
 }
 else
 {
    _firmwareFilename = "";
    _error("Can not get  firmware file.");
 }
}

void FirmwarePage::_downloadFirmware()
{
    _appendStatus("Downloading firmware...");
    _appendStatus(QString("From %1").arg(_firmwareFilename));

    _networkManager = new QNetworkAccessManager(this);
    QUrl firmUrl;
    if(_firmwareFilename.startsWith("http:"))
    {
        firmUrl.setUrl(_firmwareFilename);
    }
    QNetworkRequest request(firmUrl);
    _networkReply = _networkManager->get(request);
    Q_ASSERT(_networkReply);
    connect(_networkReply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(_downloadProgress(qint64,qint64)));
    connect(_networkReply,SIGNAL(finished()),this,SLOT(_downloadFinished()));
    connect(_networkReply,SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(_downloadError(QNetworkReply::NetworkError)));
}

void FirmwarePage::_downloadFinished(void)
{
 _appendStatus("Download complete.");

 _networkManager->deleteLater();
 _networkManager = NULL;

 if(_networkReply->error()!=QNetworkReply::NoError)
 {
     return;
 }

 QString filename = QFileInfo(_firmwareFilename).fileName();
 Q_ASSERT(filename.isEmpty());

 QSettings setting;
 QDir dir = QFileInfo(setting.fileName()).dir();
 QString downloadFilename = dir.filePath(filename);
 QFile* downloadFile = new QFile(downloadFilename);

 if(!downloadFile->exists())
 {
      if(!downloadFile->open(QIODevice::WriteOnly))
      {
          _error(QString("Could not save downloaded file to %1. Error: %2").arg(downloadFilename).arg(downloadFile->errorString()));
          return;
      }
 }
 downloadFile->write(_networkReply->readAll());
 downloadFile->close();

 _image = new FirmwareImage();
 if(downloadFilename.endsWith(".px4"))
 {
     if(!_image->load(downloadFilename,_bootloaderBoardID))
     {
         _error("Image load failed");
         return;
     }
     if(_bootloaderBoardFlashSize!=0 && _image->imageSize()>_bootloaderBoardFlashSize)
     {
         _error(QString("Image size of is too large"));
         return;
     }
     _controller->flash(_image);
   }
 else{
 qDebug()<<"Unsupported file format";
 return;
 }
}


void FirmwarePage::_downloadError(QNetworkReply::NetworkError code)
{
    QString errorMsg;

    if (code == QNetworkReply::OperationCanceledError) {
        errorMsg = "Download cancelled";

    } else if (code == QNetworkReply::ContentNotFoundError) {
        errorMsg = QString("Error: File Not Found. Please check if the firmware version is available.");

    } else {
        errorMsg = QString("Error during download. Error: %1").arg(code);
    }
    _errorCancel(errorMsg);
}

void FirmwarePage::_status(const QString& statusString, bool critical)
{
    _appendStatus(statusString,critical);
}

void FirmwarePage::_error(QString errorString)
{
    _errorCancel(QString("Error: %1").arg(errorString));
}

void FirmwarePage::_appendStatus(const QString &text, bool critical)
{
    QString varText;

    if (critical) {
        varText = QString("<font color=\"blue\">%1</font>").arg(text);
    } else {
        varText = text;
    }
    _statusTextArea->append(varText);
}

void FirmwarePage::_errorCancel(QString errorString)
{
    _appendStatus(errorString);
}

void FirmwarePage::_updateProgress(int curr, int total)
{
    // Take care of cases where 0 / 0 is emitted as error return value
    if (total > 0) {
        _progressBar->setProperty("value", (float)curr*100 / (float)total);
    }
}

void FirmwarePage::_downloadProgress(qint64 curr, qint64 total)
{
    // Take care of cases where 0 / 0 is emitted as error return value
    if (total > 0) {
        _progressBar->setProperty("value", (float)curr*100 / (float)total);
    }
}
void FirmwarePage::_foundBoard(bool firstAttempt, const QString portname, QString portDescription)
{
    if(firstAttempt){
         _status(plugText1,false);
         _status(plugText2,true);
    }
    else{
        _status(QString("Found device : %1").arg(portDescription),false);
    }
}

void FirmwarePage::_noBoardFound(void)
{
  _status(plugText,true);
}

void FirmwarePage::_boardGone(void)
{
    _status(plugText,true);
}

void FirmwarePage::_foundBootloader(int bootloaderVersion,int boardID,int flashSize)
{
    _status(QString("bootloaderVersion : %1").arg(bootloaderVersion),false);
    _status(QString("boardID : %1").arg(boardID),false);
    _status(QString("flashSize : %1").arg(flashSize),false);
    _bootloaderVersion = bootloaderVersion;
    _bootloaderBoardID = boardID;
    _bootloaderBoardFlashSize = flashSize;

    _updateBtn->setEnabled(true);
}

void FirmwarePage::_eraseStarted()
{
    _eraseCount = 0;
    _eraseTimer.start(_eraseTime);
 }

void FirmwarePage::_eraseProgress()
{
  _eraseCount++;
  qDebug()<<_eraseCount;
  _progressBar->setProperty("value",(float)(_eraseTime*_eraseCount)*100 / (float)_eraseTotalTime);
}

void FirmwarePage::_eraseCompleted()
{
    _eraseTimer.stop();
    _status("Erase Complete",false);
}

void FirmwarePage::_flashCompleted()
{
    _status("Upgrade Complete",false);
    //Change to vehicle Summary interface
}
