#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSerialPortInfo>
#include <QtDebug>
#include <QtCore>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFile>
#include "linkmanager.h"

#include "QuadApplication.h"
#include "VehicleManager.h"
#include "Vehicle.h"

#include "PX4AutopioltPlugins/PX4AutopilotPlugin.h"

static MainWindow* _instance = NULL;

MainWindow* MainWindow::_create()
{
    Q_ASSERT(_instance == NULL);
    _instance = new MainWindow();
    Q_ASSERT(_instance);
    return _instance;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , port_open(false)
  , connectionLost(true)
  , bool_flying(false)
  , fly_distance(0.0f)
  , systemId(TargetSystemID)
  , _vehicle(NULL)

{
    ui->setupUi(this);
    setFixedSize(1200,700);
    this->setStyleSheet("QPushButton {background: #cfe2f3}"
                        "QPushButton:pressed {background: 6699cc}");

    ui->pushButton_Connect->setFixedWidth(100);

    c_palette.setColor(QPalette::WindowText,Qt::black);
    w_palette.setColor(QPalette::WindowText,Qt::red);

    // Invalidate the timer to signal first announce
    _lowBatteryAnnounceTimer.invalidate();

    _attitude_indicator = new Attitude_Indicator();

    _calWidget = new SetupWidget(this);
    ui->stackedWidget_Summary->addWidget(_calWidget);
    ui->stackedWidget_Summary->setCurrentWidget(_calWidget);

    connect(&_portListTimer, &QTimer::timeout, this, &MainWindow::init);
    _portListTimer.start(1000);

    _linkMgr = qgcApp()->toolbox()->linkManager();
    connect(_linkMgr, &LinkManager::linkConnected,    this, &MainWindow::_linkStateChange);
    connect(_linkMgr, &LinkManager::linkDisconnected, this, &MainWindow::_linkStateChange);

    connect(qgcApp()->toolbox()->vehicleManager(),&VehicleManager::activeVehicleChanged,this,&MainWindow::_activeVehicleChanged);
    connect(qgcApp()->toolbox()->vehicleManager(),&VehicleManager::activeVehicleChanged,_calWidget,&SetupWidget::_activeVehicleChanged);
    show();
}

void MainWindow::_statusChanged(QString status)
{
    //qDebug()<<"status"<<status;
}

void MainWindow::_activeVehicleChanged(Vehicle* vehicle)
{
    if(vehicle) {
        _vehicle = vehicle;

        connect(_vehicle, &Vehicle::modeChanged,this,&MainWindow::_modeChange);
        connect(_vehicle, &Vehicle::armedChanged,this,&MainWindow::_armedChange);
        connect(_vehicle, &Vehicle::attitudeChanged,this, &MainWindow::_attitudeChange);
        connect(_vehicle, &Vehicle::telemetryChanged,this, &MainWindow::_telemetryChange);
        connect(_vehicle, &Vehicle::batteryChanged,this, &MainWindow::_batteryChange);
        connect(_vehicle, &Vehicle::GPSStatusChanged,this,&MainWindow::_GPSStatusChange);
        connect(_vehicle, &Vehicle::globalPositionChanged,this,&MainWindow::_globalPositionChange);
        connect(_vehicle, &Vehicle::localPositionChanged,this,&MainWindow::_localPositionChange);
        connect(_vehicle, &Vehicle::groundSpeedChanged,this,&MainWindow::_groundSpeedChange);
        connect(_vehicle, &Vehicle::attitudeChanged,this, &MainWindow::_attitudeChange);       
  }
}

 MainWindow* MainWindow::instance(void)
 {
     return _instance;
 }

//display config description and baudrate
void MainWindow::init()
{
    _linkMgr->_updateConfigurationList();
    QList<SerialConfiguration*> configs = _linkMgr->getSerialConfigurationList();
    foreach (SerialConfiguration* config, configs)
    {
     if(ui->label_Portname->text()!=config->description())
     {
     ui->label_Portname->setText(config->description());
     ui->label_Baudrate->setText(QString::number(config->baud()));
     qDebug()<<config->description()<<config->baud();
      }
    _portListTimer.stop();
    _config = config;
    ui->pushButton_Connect->setEnabled(true);
     }
}

//create serial link, start thread, open serial port
void MainWindow::on_pushButton_Connect_clicked()
{
     Q_ASSERT(_currentLink);
     if(port_open == false)
     {
     if(_config) {
        _linkMgr->createConnectedLink(_config);
        if(_currentLink=_linkMgr->getLink()) {
          port_open = true;
          ui->pushButton_Connect->setText("断开连接");
          enableAllDataTransmission(_currentLink);
          connect(&_statusTimer,&QTimer::timeout,this,&MainWindow::_updateState);
          _statusTimer.start(500);
         }
        else {
            qDebug()<<"can‘t create link!";
         }
       }
     }
     else{
         if (_currentLink->isConnected()) {
            _linkMgr->disconnectLink(_currentLink);
            port_open = false;
            ui->pushButton_Connect->setText("连接");
         }
      }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    Q_UNUSED(event)
    /*QMessageBox::StandardButton button;
    button = QMessageBox::question(this,tr("关闭程序"),
                           tr("确认退出程序？"),
                                   QMessageBox::Yes | QMessageBox::No);
     if(button == QMessageBox::Yes){
         event->accept();
     }
     if(button == QMessageBox::No){
         event->ignore();
     }
     */
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
}

void MainWindow::_updateState()
{
    quint64 curTime =static_cast<quint64>(QDateTime::currentMSecsSinceEpoch());

    quint64 lastHeartbeat = _linkMgr->getHeartbeatTime();
    quint64 heartbeatInterval = (curTime - lastHeartbeat)/1000.0;
    //qDebug()<<"last time"<<lastHeartbeat<<"now time: "<<curTime<<"interval"<<heartbeatInterval;

    // Check if heartbeat timed out
    if(!connectionLost && (heartbeatInterval>timeoutIntervalHeartbeat))
    {
        connectionLost = true;
        ui->label_Message->setPalette(w_palette);
        ui->label_Message->setText("链接丢失!");

        if (_currentLink->isConnected()) {
           _linkMgr->disconnectLink(_currentLink);
           port_open = false;
           ui->pushButton_Connect->setText("连接");
         }
    }

    // Update connection loss time on each iteration
        if (connectionLost && (heartbeatInterval > timeoutIntervalHeartbeat))
        {
            quint64 connectionLossTime = heartbeatInterval;
            ui->label_Message->setPalette(w_palette);
            ui->label_Message->setText("链接丢失: "+QString::number(connectionLossTime));
        }
    // Connection gained
    if(connectionLost && (heartbeatInterval<timeoutIntervalHeartbeat))
    {
        connectionLost = false;
        ui->label_Message->setPalette(c_palette);
        ui->label_Message->setText("连接成功!");
    }
}

MainWindow::~MainWindow()
{
    _instance = NULL;
    delete ui;
    if (_currentLink) {
        _linkMgr->disconnectLink(_currentLink);
      }
}

void MainWindow::enableAllDataTransmission(SerialLink* link)
{
    Q_UNUSED(link);
    mavlink_message_t msg;
    mavlink_param_request_list_t param;
    param.target_component = DEFAULT_COMPONENT_ID;
    param.target_system = TargetSystemID;

    mavlink_msg_param_request_list_encode(param.target_system,param.target_component,&msg,&param);
    _linkMgr->sendMessage(msg);
}

void MainWindow::_linkStateChange(SerialLink* link)
{
    int connectCount=0;
    qDebug()<<"_linkStateChange called";
    if(link->isConnected())    {
        connectCount=1;
    }
    else{
        connectCount=0;
    }
 }

void  MainWindow::_telemetryChange(uint8_t rssi)
{
Q_UNUSED(rssi)
}

void MainWindow::_modeChange(QString shortModeText)
{
    //qDebug()<<"_mode Change";
    ui->label_Mode->setText(shortModeText);
}

void MainWindow::_armedChange(bool armed)
{
  ui->label_Message->setText(QString("%1").arg(armed? QStringLiteral("Armed"):QStringLiteral("Disarmed")));
}

void MainWindow::_batteryChange(uint16_t voltage_battery)
{
    QString voltage =QString::number(voltage_battery/1000.0)+"   V";
    if(voltage_battery<=voltage_lowbound)
    {
        QPalette palette;
        palette.setColor(QPalette::WindowText,Qt::red);

        if (!_lowBatteryAnnounceTimer.isValid() || _lowBatteryAnnounceTimer.elapsed() > 5 * 1000) { // 5s, amount of time in between each low battery announcement
            _lowBatteryAnnounceTimer.restart();
        }
        ui->label_Message->setText(tr("警告! 电量不足, 请立即返航！"));
    }

}

void MainWindow::_attitudeChange(mavlink_attitude_t* attitude)
{
    //qDebug()<<"mainwindow: attitude";
    Helper::limitAngleToPMPIf(attitude->roll);
    Helper::limitAngleToPMPIf(attitude->yaw);
    Helper::limitAngleToPMPIf(attitude->pitch);

    _attitude_indicator->rollLP = attitude->roll;
    _attitude_indicator->pitchLP = attitude->pitch;
    _attitude_indicator->yaw = attitude->yaw;
    //_attitude_indicator->update();
    QString attitude_text;
    attitude_text = QString::number(attitude->roll*180.0/PI,'f',1)+",";
    attitude_text +=QString::number(attitude->pitch*180.0/PI,'f',1);
    attitude_text +=",";
    if((attitude->yaw*180/PI)<0){
        attitude_text +=QString::number((attitude->yaw*180.0/PI + 360),'f',1);
    }
    else{
        attitude_text +=QString::number(attitude->yaw*180.0/PI ,'f',1);
    }    
}

void MainWindow::_GPSStatusChange(mavlink_gps_raw_int_t* gps_raw_int)
{
    uint8_t fix_type = gps_raw_int->fix_type;
    QString fix;
    switch(fix_type){
    //fix 0: lost, 1: 2D local position hold, 2: 2D localization, 3: 3D localization
    case 0:
    case 1: fix = "No Fix";         break;
    case 2:fix = "2D Fix";          break;
    case 3:fix = "3D Fix";          break;
    case 4:fix = "DGPS";          break;
    case 5:fix = "RTK";             break;
    default:                              break;
    }

    double val = gps_raw_int->satellites_visible;
     //assume that a negative value or over 99 means there is no GPS
    if(val < 0.0)  val = -1.0;
    if(val > 99.0) val = -1.0;
}

void MainWindow::_globalPositionChange(mavlink_global_position_int_t *global_position_int)
{      
        global_position.lon = (global_position_int->lon)/1E7;
        global_position.lat = (global_position_int->lat)/1E7;
}

void MainWindow::_localPositionChange(mavlink_local_position_ned_t *local_position_t)
{
    local_position.x = local_position_t->x;
    local_position.y = local_position_t->y;
}

void MainWindow::_groundSpeedChange(float fly_speed)
{
Q_UNUSED(fly_speed)
}
