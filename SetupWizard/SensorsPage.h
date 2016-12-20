#ifndef SENSORSPAGE_H
#define SENSORSPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QListWidget>

class SetupWidget;
class TitleLabel;

class SensorsPage : public QWidget
{
    Q_OBJECT
public:
    SensorsPage(SetupWidget *calWidget, QWidget *parent = 0);
    ~SensorsPage();

signals:
    void showMessage(const QString text);

private:
    QPushButton* _compassCalButton;
    QPushButton* _gyroCalButton;
    QPushButton* _accelCalButton;
    QPushButton* _levalCalButton;
    QPushButton* _cancelButton;

    TitleLabel* _title;
    QLabel* _calLabel;
    QProgressBar* _progressBar;
    QLabel* _statusText;
    QListWidget* _orientationList;

    const QString compassHelp = "For Compass calibration you will need to rotate your vehicle through a number of positions. Most users prefer to do this wirelessly with the telemetry link.";
    const QString gyroHelp = "For Gyroscope calibration you will need to place your vehicle on a surface and leave it still.";
    const QString accelHelp = "For Accelerometer calibration you will need to place your vehicle on all six sides on a perfectly level surface and hold it still in each orientation for a few seconds.";
    const QString levelHelp = "To level the horizon you need to place the vehicle in its level flight position and press OK.";

    const QString  statusTextDefault = "Start the individual calibration steps by clicking one of the buttons above.";
    const QString  boardRotationText = "If the autopilot is mounted in flight direction, leave the default value (ROTATION_NONE)";
    const QString  compassRotationText = "If the compass or GPS module is mounted in flight direction, leave the default value (ROTATION_NONE)";
};

#endif // SENSORSPAGE_H
