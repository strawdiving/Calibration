#ifndef FIRMWAREPAGE_H
#define FIRMWAREPAGE_H

#include <QtCore>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QTextBrowser>
#include <QProgressBar>
#include <QPushButton>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <QTimer>
#include "TitleLabel.h"

#include "FirmwareUpgrade/PX4FirmUpgradeThread.h"
#include "FirmwareUpgrade/FirmwareImage.h"

class TitleLabel;

class FirmwarePage : public QWidget
{
    Q_OBJECT

public:
    explicit FirmwarePage(QWidget *parent = 0);
    ~FirmwarePage();

public slots:
    void _status(const QString& statusString, bool critical);
    void _updateProgress(int curr, int total);

    void _foundBoard(bool firstAttempt, const QString portname, QString portDescription);
    void _noBoardFound(void);
    void _boardGone(void);
    void _foundBootloader(int bootloaderVersion,int boardID,int flashSize);
    void _error(QString errorString);

    void _downloadProgress(qint64 curr, qint64 total);
    void _downloadFinished(void);
    void _downloadError(QNetworkReply::NetworkError code);

    void _flash(void);
    void _eraseStarted(void);
    void _eraseProgress(void);
    void _eraseCompleted(void);
    void _flashCompleted(void);

private slots:

private:

    void _appendStatus(const QString& text, bool critical = false);
    void _errorCancel(QString errorString);
    void _getFimwareFile();
    void _downloadFirmware();
    bool _decompressJsonValue(const QJsonObject&	jsonObject,	const QByteArray&	jsonDocBytes,		//< Raw bytes of JSON document
                                             const QString&		sizeKey,			//< key which holds byte size
                                             const QString&		bytesKey,			//< key which holds compress bytes
                                             QByteArray&		decompressedBytes);	//< Returned decompressed bytes

    PX4FirmUpgradeThreadController* _controller;

    QTextBrowser* _statusTextArea;
    QProgressBar* _progressBar;
    QPushButton* _updateBtn;
    TitleLabel* _title;

    const QString plugText = "Plugin your device via USB to start firmware upgrade";
    const QString plugText1 = "All connections to vehicles must be disconnected"
                        " prior to firmware upgrade";
    const QString plugText2 = "Please unplug your flight controller and/or Radio from USB";
    static const int boardIDPX4FMUV2 = 9;   ///< PX4 V2 board
    uint32_t _bootloaderVersion;
    uint32_t _bootloaderBoardID;
    uint32_t _bootloaderBoardFlashSize;
    QString _firmwareFilename; //Image which we are going to flash to the board

    QNetworkAccessManager* _networkManager;
    QNetworkReply* _networkReply;

    FirmwareImage* _image;

    QTimer _eraseTimer;
    static const int _eraseTotalTime = 7500;//estimated erase time,before: 15000
    static const int _eraseTime = 250;//before: 500
    int _eraseCount;
};

#endif // FIRMWAREPAGE_H
