#ifndef SENSORSGROUPPAGE_H
#define SENSORSGROUPPAGE_H

#include <QWidget>
#include "PX4AutopioltPlugins/SensorsComponentController.h"
#include "CalRotationWidget.h"

class SetupWidget;
class TitleLabel;

namespace Ui {
class SensorsGroupPage;
}

class SensorsGroupPage : public QWidget
{
    Q_OBJECT

public:
    explicit SensorsGroupPage(QWidget *parent = 0);
    ~SensorsGroupPage();
    void initSensorsController();

signals:
    void showMessage(const QString text);
    void stopCalibration(void);
    void cancelCalibration(void);

    void calStatusChanged(QString side,bool inProgress,bool rotate,bool done);

    void calVisibleChanged(QString side);

    void status(QString message);

private slots:
    void _calibrate(void);
    void on_pushButton_Cancel_clicked();
    void _handleUASTextMessage(QString text);

private:

    Ui::SensorsGroupPage *ui;

    enum StopCalibrationCode {
        StopCalibrationSuccess,
        StopCalibrationFailed,
        StopCalibrationCancelled
    };
    void _resetVisualState(bool done, bool visible);
    void _startVisualCalibration(bool done,bool visible);

    void _stopCalibration(StopCalibrationCode code);

    bool _accelCalInProgress;
    bool _magCalInProgress;
    bool _gyroCalInProgress;

    bool _calDownSideVisible;
    bool _calUpsideDownVisible;
    bool _calLeftSideVisible;
    bool _calRightSideVisible;
    bool _calNoseDownVisible;
    bool _calTailDownVisible;

    bool _calDownSideInProgress;
    bool _calUpsideDownInProgress;
    bool _calLeftSideInProgress;
    bool _calRightSideInProgress;
    bool _calNoseDownInProgress;
    bool _calTailDownInProgress;

    bool _calDownSideRotate;
    bool _calUpsideDownRotate;
    bool _calLeftSideRotate;
    bool _calRightSideRotate;
    bool _calNoseDownRotate;
    bool _calTailDownRotate;

    bool _calDownSideDone;
    bool _calUpsideDownDone;
    bool _calLeftSideDone;
    bool _calRightSideDone;
    bool _calNoseDownDone;
    bool _calTailDownDone;

    bool _waitingForCancel;

    static const int _supportedFirmwareCalVersion = 2;

    const QString compassHelp = "For Compass calibration you will need to rotate your vehicle through a number of positions. Most users prefer to do this wirelessly with the telemetry link.";
    const QString gyroHelp = "For Gyroscope calibration you will need to place your vehicle on a surface and leave it still.";
    const QString accelHelp = "For Accelerometer calibration you will need to place your vehicle on all six sides on a perfectly level surface and hold it still in each orientation for a few seconds.";
    const QString levelHelp = "To level the horizon you need to place the vehicle in its level flight position and press OK.";
    const QString  boardRotationText = "If the autopilot is mounted in flight direction, leave the default value (ROTATION_NONE)";
    const QString  compassRotationText = "If the compass or GPS module is mounted in flight direction, leave the default value (ROTATION_NONE)";


    const QString  statusTextDefault = "Start the individual calibration steps by clicking one of the buttons above.";

    const QString calStartedText = "Place your vehicle into one of the incomplete orientations below and hold it still.";
    const QString otherOrientationDetectedText = "Hold still in the current orientation";
    const QString magOrientationDetectedText = "Place the vehicle continuously shown in the diagram until marked as completed.";
    const QString oneSideDoneText = "Place your vehicle into one of the orientations shown below and hold it still";
    const QString oneSideCompletedText = "Orientation already completed. Place your vehicle into one of the incompleted orientations "
                                         "shown below and hold it still.";

    SensorsComponentController* _sensorsController ;
    CalRotationWidget* _calOrientationWidget;

    bool _calInProgress;
    bool _calRotate;
    bool _calDone;
};
#endif // SENSORSGROUPPAGE_H
