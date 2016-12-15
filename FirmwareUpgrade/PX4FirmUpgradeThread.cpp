#include "PX4FirmUpgradeThread.h"
#include <QDebug>

PX4FirmUpgradeThreadWorker::PX4FirmUpgradeThreadWorker(QObject *parent) : QObject(parent)
  , _foundBoard(false)
  , _firstTry(true)
  , _timerRetry(NULL)
{
    _bootloader = new Bootloader();
    connect(_bootloader, SIGNAL(updateProgress(int,int)), this, SLOT(_updateProgress(int,int)));
}

PX4FirmUpgradeThreadWorker::~PX4FirmUpgradeThreadWorker()
{

}

void PX4FirmUpgradeThreadWorker::_init()
{
    _timerRetry = new QTimer(this);
    _timerRetry->setSingleShot(true);
    _timerRetry->setInterval(_retryInterval);

    connect(_timerRetry,SIGNAL(timeout()),this,SLOT(_findBoardOnce()));
}

void PX4FirmUpgradeThreadWorker::_startFindBoard()
{
    //qDebug()<<"worker:startFindBoard()";
    _foundBoard = false;
    _firstTry = true;
    _findBoardOnce();
}

void PX4FirmUpgradeThreadWorker::_findBoardOnce()
{
    if(_findBoardFromPorts())
    {
        if(!_foundBoard)
        {
            _foundBoard = true;
            emit foundBoard(_firstTry,_portname,_description);
            if(!_firstTry)
            {
                qDebug()<<"find bootloader.";
                _findBootloader(_portname);
                return;
            }
        }
    }
    else
    {
        if(_foundBoard){
            _foundBoard = false;
            //qDebug()<<"Board gone.";
            emit boardGone();
        }
        else if(_firstTry){
            qDebug()<<"No board found.";
            emit noBoardFound();
        }
     }
    _firstTry = false;
    _timerRetry->start();
    }

bool PX4FirmUpgradeThreadWorker::_findBoardFromPorts()
{
    foreach(QSerialPortInfo info,QSerialPortInfo::availablePorts())
    {
      //qDebug()<< "Serial Port -------------\tport name:"<<info.portName();
      //qDebug()<< "\tdescription:" <<info.description();

      if((!info.portName().isEmpty())&&(info.description().startsWith("PX4 FMU") || info.vendorIdentifier() == 9900/*3DR*/))
      {          
          _portname = info.portName();
          _description = info.description();
          return true;
      }
    }
return false;
}

bool PX4FirmUpgradeThreadWorker::_findBootloader(const QString portname)
{
    qDebug()<<"_findBootloader:"<<portname;
    uint32_t bootloaderVersion = 0;
    uint32_t boardID;
    uint32_t flashSize = 0;

    _bootloaderPort = new QextSerialPort(QextSerialPort::Polling);
    bool openFailed =true;
    for(int i = 0;i<10;i++)
    {
      if(_bootloader->open(_bootloaderPort,portname)){
        qDebug()<<"port open.";
        openFailed = false;
        break;
      }
      else
      {
          QThread::msleep(100);
      }
    }
    if(openFailed) {
        emit error(_bootloader->errorString());
    return false;
    }
    if (_bootloader->sync(_bootloaderPort))
    {
        bool success;
        success = _bootloader->getPX4BoardInfo(_bootloaderPort,bootloaderVersion, boardID, flashSize);
        if(success)
        {
            qDebug()<<"Found bootloader: "<<bootloaderVersion<<boardID<<flashSize;
            emit foundBootloader(bootloaderVersion,boardID,flashSize);
            return true;
        }
    }
    _bootloaderPort->close();
    _bootloaderPort->deleteLater();
    _bootloaderPort = NULL;
    qDebug() << "Bootloader error:" << _bootloader->errorString();

    emit error(_bootloader->errorString());
    return false;
}

void PX4FirmUpgradeThreadWorker::_flash(FirmwareImage* image)
{
    if(_erase())
    {
        qDebug()<<"Erase Complete";
        qDebug()<<"Programming new version...";
        if(_bootloader->program(_bootloaderPort,image))
        {
            qDebug()<<"Program Complete";
        }
        else{
            _bootloaderPort->deleteLater();
            _bootloader = NULL;
            qDebug()<<"Program Failed";
            emit error(_bootloader->errorString());
            return;
        }
        qDebug()<<"Verifying program...";

        if(_bootloader->verify(_bootloaderPort,image))
        {
            qDebug()<<"Verify Complete";
        }
        else {
            qDebug()<<"Verify Failed";
            emit error(_bootloader->errorString());
            return;
        }
/**/
    }

    //reboot
    /*if(_bootloader){
        if(_bootloaderPort->isOpen())
        {
            _bootloader->reboot(_bootloaderPort);
        }
        _bootloader->deleteLater();
        _bootloader = NULL;
        }
*/
    emit flashCompleted();
    }


bool PX4FirmUpgradeThreadWorker::_erase(void)
{
    qDebug()<<"PX4FirmUpgradeThreadWorker:_erase";
    emit eraseStarted();
    qDebug()<<"Erasing previous program...";

    if(_bootloader->erase(_bootloaderPort))
    {
        emit eraseCompleted();
        return true;
    }
    else{
        qDebug()<<"Erase Failed";
        emit error(_bootloader->errorString());
        return false;
    }


}

PX4FirmUpgradeThreadController::PX4FirmUpgradeThreadController(QObject *parent) : QObject(parent)
{
    _worker = new PX4FirmUpgradeThreadWorker();
    _workerThread = new QThread(this);
    _worker->moveToThread(_workerThread);//don't need revise run() function

    connect(_worker,SIGNAL(updateProgress(int,int)),this,SLOT(_updateProgress(int,int)));
    connect(_worker,SIGNAL(foundBoard(bool,QString,QString)),this,SLOT(_foundBoard(bool,QString,QString)));
    connect(_worker,SIGNAL(noBoardFound()),this,SLOT(_noBoardFound()));
    connect(_worker,SIGNAL(boardGone()),this,SLOT(_boardGone()));
    connect(_worker,SIGNAL(foundBootloader(int,int,int)),this,SLOT(_foundBootloader(int,int,int)));
    connect(_worker,SIGNAL(error(QString)),this,SLOT(_error(QString)));
    connect(_worker,SIGNAL(eraseStarted()),this,SLOT(_eraseStarted()));
    connect(_worker,SIGNAL(eraseCompleted()),this,SLOT(_eraseCompleted()));
    connect(_worker,SIGNAL(flashCompleted()),this,SLOT(_flashCompleted()));

    connect(this,SIGNAL(initThreadWorker()),_worker,SLOT(_init()));
    connect(this,SIGNAL(startFindBoardThread()),_worker,SLOT(_startFindBoard()));
    connect(this,SIGNAL(flashOnThread(FirmwareImage*)),_worker,SLOT(_flash(FirmwareImage*)));

    _workerThread->start();
    emit initThreadWorker();
}

PX4FirmUpgradeThreadController::~PX4FirmUpgradeThreadController()
{
    _workerThread->quit();
    _workerThread->wait();

    delete _workerThread;
}

void PX4FirmUpgradeThreadController::startFindBoard()
{
    //qDebug() << "PX4FirmwareUpgradeThreadController::findBoard";
    emit startFindBoardThread();
}

void PX4FirmUpgradeThreadController::flash(FirmwareImage* image)
{
    qDebug()<<"controller:flash started";
    _image = image;
    emit flashOnThread(image);
}
