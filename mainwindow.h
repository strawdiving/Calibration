#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSerialPort>
#include<QTimer>
#include <QElapsedTimer>
#include "SerialCommunication.h"
#include "common/mavlink.h"
//#include "linkManager.h"
#include "attitude_indicator.h"
#include "helper.h"
#include "ParameterLoader.h"
#include "SetupWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    static MainWindow*  _create();
    ~MainWindow();

    MainWindow* MainWindow::instance(void);
    //MessagePanel* messagePanel(void) {return _messagePanel;}

    void paintEvent(QPaintEvent* event);
    void closeEvent(QCloseEvent* event);
    void init();
    void enableAllDataTransmission(SerialLink *link);//pack message, and send message to FC to request param list

    int    getSystemId() {return systemId;}

    struct Global_Position{
          qreal lat;
          qreal lon;
       }global_position;

    struct Local_Position{
        float x;
        float y;
        float z;
        float yaw;
    }local_position;

private slots:

public slots:


    void _statusChanged(QString status);

    void _updateState();
    /// Signals from LinkManager
    void _linkStateChange(SerialLink* link);
    void _telemetryChange(uint8_t rssi);
    void _modeChange(QString shortModeText);
    void _armedChange(bool armed);
    void _attitudeChange(mavlink_attitude_t *attitude);
    void _batteryChange(uint16_t voltage_battery);
    void _GPSStatusChange(mavlink_gps_raw_int_t* gps_raw_int);
    void _globalPositionChange(mavlink_global_position_int_t* global_position_int);
    void _localPositionChange(mavlink_local_position_ned_t* local_position);
    void _groundSpeedChange(float fly_speed);
    void on_pushButton_Connect_clicked();

    void _activeVehicleChanged(Vehicle* vehicle);

protected:
    // TIMEOUT CONSTANTS
    static const unsigned int timeoutIntervalHeartbeat = 3.5; ///< Heartbeat timeout is 3.5 seconds

private:
    void _showFlytime(void);

    Ui::MainWindow *ui;
    QPalette w_palette; //warning
    QPalette c_palette; //common
    bool                   port_open;
    bool                   link_connected;
    bool                   connectionLost;
    bool                   bool_flying;
    static const uint16_t   voltage_lowbound = 19800;//19.5*1000 = 19500mV
    float                   fly_distance;

    SerialConfiguration* _config;
    LinkManager* _linkMgr;//manage serial links
    SerialLink* _currentLink;//currently connected link
    Vehicle* _vehicle;

    SetupWidget* _calWidget;

    QTimer             _portListTimer;//time to search for valid port
    QTimer             _statusTimer;
    quint64             _lastTakeoffTime;

    int systemId;
    QString             _mode;

    Attitude_Indicator *_attitude_indicator;//display gauge instruments
    QElapsedTimer _lowBatteryAnnounceTimer;
};

#endif // MAINWINDOW_H
