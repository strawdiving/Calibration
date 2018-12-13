#ifndef PX4FIRMUPGRADETHREAD_H
#define PX4FIRMUPGRADETHREAD_H

/**
 * A thread , to find board, connect the flight controller, and execute erase, flash and  reboot work
**/

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QSerialPortInfo>
#include "Bootloader.h"
#include <stdint.h>
#include "qextserialport.h"
#include "FirmwareImage.h"

/**
 * @brief The PX4FirmUpgradeThreadWorker class, to find and connect the board, controll the progress of  firmware upgrade
 */
class PX4FirmUpgradeThreadWorker : public QObject
{
    Q_OBJECT
public:
    explicit PX4FirmUpgradeThreadWorker(QObject *parent = 0);
    ~PX4FirmUpgradeThreadWorker();

signals:
    /// Signals sent to PX4FirmUpgradeThreadController
    void updateProgress(int curr, int total);
    void foundBoard(bool firstAttempt, const QString portname, QString portDescription);
    void noBoardFound(void);
    void boardGone(void);
    void foundBootloader(int bootloaderVersion,int boardID,int flashSize);
    void error(QString errorString);
    void eraseStarted(void);
    void eraseCompleted(void);
    void flashCompleted(void);

public slots:
    void _init();
    void _startFindBoard();
    void _findBoardOnce();
    void _flash(FirmwareImage* image);
    void _updateProgress(int curr, int total) {emit updateProgress(curr,total);}

private:    

    bool _findBoardFromPorts();
    bool _findBootloader(const QString portname);
    bool _erase(void);
    QTimer* _timerRetry; /// singleshot timer to find board
    bool _foundBoard;     /// Indicate whether to find the board
    bool _firstTry;              /// Indicate if it's the first time to find the board
    static const int  _retryInterval = 100; /// interval of timer

    QString _portname;
    QString _description;
    QextSerialPort* _bootloaderPort;
    Bootloader* _bootloader;
};

#endif // PX4FIRMUPGRADETHREAD_H

class PX4FirmUpgradeThreadController : public QObject
{
    Q_OBJECT
public:
    explicit PX4FirmUpgradeThreadController(QObject *parent = 0);
    ~PX4FirmUpgradeThreadController();
    /// Called by FirmwarePage to start find board
    void startFindBoard();
    /// Called by FirmwarePage when firmware file loaded successfully
    void flash(FirmwareImage* image);

signals:
    /// Signals sent to FirmwarePage
    void updateProgress(int curr, int total);
    void foundBoard(bool firstAttempt, const QString portname, QString portDescription);
    void noBoardFound(void);
    void boardGone(void);
    void foundBootloader(int bootloaderVersion,int boardID,int flashSize);
    void error(QString errorString);
    void eraseStarted(void);
    void eraseCompleted(void);
    void flashCompleted(void);

    /// Signals sent to PX4FirmUpgradeThreadWorker
    void initThreadWorker();
    void startFindBoardThread();
    void flashOnThread(FirmwareImage* image);

public slots:
    /// Forward signals to FirmwarePage
    void _updateProgress(int curr, int total) { emit updateProgress(curr,total);}
    void _foundBoard(bool firstAttempt, const QString portname, QString portDescription){emit foundBoard(firstAttempt,portname,portDescription);}
    void _noBoardFound(void) {emit noBoardFound();}
    void _boardGone(void) {emit boardGone();}
    void _foundBootloader(int bootloaderVersion,int boardID,int flashSize){emit foundBootloader(bootloaderVersion,boardID,flashSize);}
    void _error(QString errorString) {emit error(errorString); }
    void _eraseStarted(void) {emit eraseStarted();}
    void _eraseCompleted(void){emit eraseCompleted();}
    void _flashCompleted(void){emit flashCompleted();}

 private:
    PX4FirmUpgradeThreadWorker* _worker;
    /// The thread PX4FirmUpgradeThreadWorker runs on
    QThread* _workerThread;
    FirmwareImage* _image;
};
