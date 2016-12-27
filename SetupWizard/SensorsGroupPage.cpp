#include "SensorsGroupPage.h"
#include "ui_SensorsGroupPage.h"

#include <QGridLayout>
#include <QDebug>
#include <QMessageBox>

SensorsGroupPage::SensorsGroupPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorsGroupPage),
    _sensorsController(NULL),
    _calOrientationWidget(NULL),
    _accelCalInProgress(false),
    _magCalInProgress(false),
    _gyroCalInProgress(false),

    _calDownSideVisible(false),
    _calUpsideDownVisible(false),
    _calLeftSideVisible(false),
    _calRightSideVisible(false),
    _calNoseDownVisible(false),
    _calTailDownVisible(false),

    _calDownSideInProgress(false),
    _calUpsideDownInProgress(false),
    _calLeftSideInProgress(false),
    _calRightSideInProgress(false),
    _calNoseDownInProgress(false),
    _calTailDownInProgress(false),

    _calDownSideRotate(false),
    _calUpsideDownRotate(false),
    _calLeftSideRotate(false),
    _calRightSideRotate(false),
    _calNoseDownRotate(false),
    _calTailDownRotate(false),

    _calDownSideDone(false),
    _calUpsideDownDone(false),
    _calLeftSideDone(false),
    _calRightSideDone(false),
    _calNoseDownDone(false),
    _calTailDownDone(false),

    _waitingForCancel(false)
{
    ui->setupUi(this);
    ui->label_StatusText->setText(statusTextDefault);
    _calOrientationWidget = new CalRotationWidget;
    ui->stackedWidget_Orientations->addWidget(_calOrientationWidget);

    //connect(this,&SensorsGroupPage::statusChanged,_calRotationWidget,&CalRotationWidget::_);
    connect(this,&SensorsGroupPage::status,_calOrientationWidget,&CalRotationWidget::_status);
    connect(this,&SensorsGroupPage::calStatusChanged,_calOrientationWidget,&CalRotationWidget::_calStatusChanged);
}

SensorsGroupPage::~SensorsGroupPage()
{
    delete ui;
}

void SensorsGroupPage::initSensorsController()
{
    _sensorsController = new SensorsComponentController;

    connect(ui->pushButton_Compass,&QPushButton::clicked,this,&SensorsGroupPage::_calibrate);
    connect(ui->pushButton_Gyro,&QPushButton::clicked,this,&SensorsGroupPage::_calibrate);
    connect(ui->pushButton_Accel,&QPushButton::clicked,this,&SensorsGroupPage::_calibrate);
    connect(ui->pushButton_Level,&QPushButton::clicked,this,&SensorsGroupPage::_calibrate);

    connect(_sensorsController,&SensorsComponentController::handleUASTextMessage,this,&SensorsGroupPage::_handleUASTextMessage);
    connect(this,&SensorsGroupPage::cancelCalibration,_sensorsController,&SensorsComponentController::_cancelCalibration);
    connect(this,&SensorsGroupPage::stopCalibration,_sensorsController,&SensorsComponentController::_stopCalibration);
}

void SensorsGroupPage::_handleUASTextMessage(QString text)
{    
    qDebug()<<text;
    if(text.contains("progress <")) {
        QString p = text.split('<').last().split('>').first();
        bool ok = false;
        int num = p.toInt(&ok);
        if(ok) {
            ui->progressBar_CalProgress->setProperty("value",float(num));
        }
        return;
    }

    //append text to statusTextArea

    //All calibration messages start with [cal]
    QString calPrefix("[cal] ");
    if(!text.startsWith(calPrefix)) {
        return;
    }
    text = text.right(text.length() - calPrefix.length());

    QString calStartPrefix("calibration started: ");
    if(text.startsWith(calStartPrefix)) {
        text = text.right(text.length() - calStartPrefix.length());

        //split firmware version and cal type
        QStringList parts = text.split(" ");
        if(parts.count()!=2 && parts[0].toInt() != _supportedFirmwareCalVersion) {
            qDebug()<<"Unsupported calibration firmware version";
            return;
        }
        _startVisualCalibration(true,false);

        text = parts[1];
        if(text == "accel" || text == "mag" || text == "gyro") {
            _startVisualCalibration(false,false);
            emit status(calStartedText);

            if(text == "accel") {
                _accelCalInProgress = true;
                _startVisualCalibration(false,true);
            }
            else if(text == "gyro") {
                _gyroCalInProgress = true;
                _calDownSideVisible = true;

            }
            else if (text == "mag") {
                _magCalInProgress = true;
                int sides = _sensorsController->getMagCalSides();
                if(sides) {
                    _calTailDownVisible = ((sides & (1<<0)) >0);
                    _calNoseDownVisible = ((sides & (1<<1)) >0);
                    _calLeftSideVisible = ((sides & (1<<2)) >0);
                    _calRightSideVisible = ((sides & (1<<3)) >0);
                    _calUpsideDownVisible = ((sides & (1<<4)) >0);
                    _calDownSideVisible = ((sides & (1<<5)) >0);
                }
            }
            else {
                Q_ASSERT(false);
            }
            //emit xxxSidesxxxChanged signals

            //emit calInProgressChanged();
            //emit calRotateChanged();
           // emit calDoneChanged();

            ui->stackedWidget_Orientations->setCurrentWidget(_calOrientationWidget);
        }
        return;
    }

    if(text.endsWith("orientation detected")) {
        QString side = text.section(" ",0,0);

        if(side == "down" || side == "up" || side == "left"
                || side == "right" || side == "front" || side == "back") {
            _calInProgress = true;
           if(_magCalInProgress) {
               _calRotate = true;
           }
            emit calStatusChanged(side,_calInProgress,_calRotate,_calDone);
        }

        if(_magCalInProgress) {
           emit status(magOrientationDetectedText);
        } else {
           emit status(otherOrientationDetectedText);
        }
        return;
    }

    if(text.endsWith("side done, rotate to a different side")) {
        QString side = text.section(" ",0,0);

        if(side == "down" || side == "up" || side == "left"
                || side == "right" || side == "front" || side == "back") {
            _calInProgress = false;
            _calRotate = false;
            _calDone = true;
            emit calStatusChanged(side,_calInProgress,_calRotate,_calDone);
        }
        emit status(oneSideDoneText);
        return;
    }

    if(text.endsWith("side already completed")) {
        emit status(oneSideCompletedText);
        return;
    }

    if(text.startsWith("calibration done:")) {
        _stopCalibration(StopCalibrationSuccess);
        return;
    }
    if(text.startsWith("calibration cancelled")) {
        _stopCalibration(_waitingForCancel? StopCalibrationCancelled : StopCalibrationFailed);
        return;
    }
    if(text.startsWith("calibration failed")) {
        _stopCalibration(StopCalibrationFailed);
        return;
    }
}

void SensorsGroupPage::_stopCalibration(StopCalibrationCode code)
{
    ui->pushButton_Accel->setEnabled(true);
    ui->pushButton_Compass->setEnabled(true);
    ui->pushButton_Gyro->setEnabled(true);
    ui->pushButton_Level->setEnabled(true);
    ui->pushButton_Cancel->setEnabled(false);

    //disconnect UAS::textMessageReceived and this::_handleTextMessage
    emit stopCalibration();

    if(code == StopCalibrationSuccess) {
        _resetVisualState(true,true);
        ui->progressBar_CalProgress->setProperty("value",100);
    } else {
        ui->progressBar_CalProgress->setProperty("value",0);
    }

    if(!_waitingForCancel) {
        //emit xxxsidesxxxChanged signals
    }

    if(code == StopCalibrationSuccess) {
        emit status("Calibration complete.");
        ui->label_StatusText->setText(statusTextDefault);

    } else if(code == StopCalibrationCancelled || code == StopCalibrationFailed) {
        ui->label_StatusText->setText(statusTextDefault);
        ui->stackedWidget_Orientations->setCurrentWidget(_calOrientationWidget);
        if(code == StopCalibrationFailed) {
            //qgcApp: showMessage "Calibration failed"
            ui->label_StatusText->setVisible(true);
            ui->label_StatusText->setStyleSheet("color: red");
            ui->label_StatusText->setText("Calibration failed.");
        }
    }
}

void SensorsGroupPage::_startVisualCalibration(bool done,bool visible)
{
    ui->pushButton_Accel->setEnabled(false);
    ui->pushButton_Level->setEnabled(false);
    ui->pushButton_Compass->setEnabled(false);
    ui->pushButton_Gyro->setEnabled(false);
    ui->pushButton_Cancel->setEnabled(true);

    ui->label_StatusText->setVisible(false);

    ui->progressBar_CalProgress->setProperty("value",0);

    ///void _resetVisualState(done,inProgress,visible)
    ////// \param Done
    ////// \param inProgress
    ////// \param visible
    _resetVisualState(done,visible);
}

void SensorsGroupPage::_resetVisualState(bool done,bool visible)
{
    if(visible) {
        ui->stackedWidget_Orientations->setCurrentWidget(_calOrientationWidget);
    }
}


void SensorsGroupPage::_calibrate()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QString btnName = btn->text();

    //hide all calibration area
    //ui->label_CalAreaHelpText->setVisible(false);
    //ui->listView_Orientation->setVisible(false);
    ui->pushButton_Cancel->setEnabled(false);

    if (btnName == "Compass") {
         _sensorsController->calibrateCompass();
    }
    else if (btnName == "Gyro") {
        _sensorsController->calibrateGyro();
    }
    else if (btnName == "Accel") {
        _sensorsController->calibrateAccel();
    }
    else if (btnName == "Level") {
        _sensorsController->calibrateLevel();
    }
}

void SensorsGroupPage::on_pushButton_Cancel_clicked()
{
    qDebug()<<"cancel calibration";
    // The firmware doesn't allow us to cancel calibration. The best we can do is wait
    // for it to timeout.
    _waitingForCancel = true;
    QMessageBox::information(this,"Calibration Cancel","Waiting for Vehicle to response to Cancel. "
                                                       "This may take a few seconds.",QMessageBox::Ok);

    ui->pushButton_Cancel->setEnabled(false);
    emit cancelCalibration();
}
