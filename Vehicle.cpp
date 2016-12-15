#include "Vehicle.h"
#include "PX4FirmwarePlugin.h"
#include "PX4AutopioltPlugins/PX4AutopilotPlugin.h"

#include "ParameterLoader.h"
#include "QuadApplication.h"
#include "linkmanager.h"
#include "UAS.h"
#include <QDebug>

struct Modes2Name {
    uint8_t main_mode;
    uint8_t sub_mode;
    const char* name;
    bool canBeSet;
};

static const struct Modes2Name modes2name[] ={
{ PX4_CUSTOM_MAIN_MODE_MANUAL ,       0 , "Manual" ,                true},
{ PX4_CUSTOM_MAIN_MODE_STABILIZED ,  0 , "Stabilized" ,            true},
{ PX4_CUSTOM_MAIN_MODE_ALTCTL ,          0 , "Altitude Control" ,  true},
{ PX4_CUSTOM_MAIN_MODE_POSCTL ,        0 , "Position Control" , true},
{ PX4_CUSTOM_MAIN_MODE_OFFBOARD ,  0 , "Offboard Control" ,true},
{ PX4_CUSTOM_MAIN_MODE_AUTO ,             PX4_CUSTOM_SUB_MODE_AUTO_LOITER ,     "Loiter" ,                    true},
{ PX4_CUSTOM_MAIN_MODE_AUTO ,             PX4_CUSTOM_SUB_MODE_AUTO_RTL ,           "Return To Land" ,     true},

{ PX4_CUSTOM_MAIN_MODE_AUTO,        PX4_CUSTOM_SUB_MODE_AUTO_MISSION,   "Mission",       true},
{ PX4_CUSTOM_MAIN_MODE_AUTO,        PX4_CUSTOM_SUB_MODE_AUTO_LAND,      "Landing",       false},
{ PX4_CUSTOM_MAIN_MODE_AUTO,        PX4_CUSTOM_SUB_MODE_AUTO_READY,     "Ready",         false},
{ PX4_CUSTOM_MAIN_MODE_AUTO,        PX4_CUSTOM_SUB_MODE_AUTO_TAKEOFF,   "Takeoff",       false},
{ PX4_CUSTOM_MAIN_MODE_AUTO,        PX4_CUSTOM_SUB_MODE_AUTO_RTGS,      "Return, Link Loss",          false},
};


Vehicle::Vehicle(SerialLink* link, int vehicleId, MAV_TYPE vehicleType, PX4FirmwarePlugin *firmwarePlugin)
    : _autopilotPlugin(NULL)
    , _vehicleId(vehicleId)
    , _vehicleType(vehicleType)
    , _link(NULL)
    , _active(false)
    , _uas(NULL)
    , _parameterLoader(NULL)
    ,  _armed(false)
    , _base_mode(0)
    , _custom_mode(0)
    , _firmwarePlugin(firmwarePlugin)
{
    //qDebug()<<"vehicle";
    _addLink(link);

    _autopilotPlugin = new PX4AutopilotPlugin(this,this);

    _linkMgr = qgcApp()->toolbox()->linkManager();
    connect(_linkMgr,&LinkManager::messageReceived,this,&Vehicle::_mavlinkMessageReceived);

    _uas = new UAS(this);
    connect (_uas,&UAS::statusChanged,qgcApp()->mainWindow(),&MainWindow::_statusChanged);

    _parameterLoader = new ParameterLoader(this,this);
    connect(_parameterLoader,&ParameterLoader::paramsReady,_autopilotPlugin,&PX4AutopilotPlugin::_parametersReadyPreCheck);


    //connect (_uas,&UAS::parameterUpdate,_parameterLoader,&ParameterLoader::_parameterUpdate);
    //connect(_parameterLoader,&ParameterLoader::readParameterRaw,this,&UAS::_readParameterRaw);
}

///For test
void Vehicle::_paramUpdate(int paramCount,QString paramName, FactMetaData::ValueType_t type, QVariant &value)
{
    //qDebug()<<"Vehicle: _paramUpdate";
    if(_parameterLoader) {
        connect(this,&Vehicle::paramUpdate,_parameterLoader,&ParameterLoader::_paramUpdate);
        emit paramUpdate(paramCount,paramName,type,value);
    }
}

Vehicle::~Vehicle()
{

}

 void Vehicle::_addLink(SerialLink* link)
 {
     if(!_link) {
         _link = link;
         connect(qgcApp()->toolbox()->linkManager(),&LinkManager::linkDisconnected,this,&Vehicle::_linkDeleted);
     }
 }

void Vehicle::_linkDeleted(SerialLink* link)
{
    Q_UNUSED(link)
    _link = NULL;
    qDebug()<<"Vehicle : link deleted";
    emit linkDeleted(this);
}

void Vehicle::setActive(bool active)
{
    _active = active;
}

void Vehicle::_mavlinkMessageReceived(SerialLink*link, mavlink_message_t &message)
{
    //qDebug()<<"vehicle: mavlinkMessageReceived";
    if(_link != link){
        _addLink(link);
    }

    if(!_heardFrom) {
        if(message.msgid == MAVLINK_MSG_ID_HEARTBEAT) {
            _heardFrom = true;
            _compID = message.compid;
        }
    }

    switch(message.msgid) {
    case MAVLINK_MSG_ID_HEARTBEAT:
        _handleHeartbeat(message);
        break;
    //#1
    case MAVLINK_MSG_ID_SYS_STATUS:
    {
        mavlink_sys_status_t sys_status;
        mavlink_msg_sys_status_decode(&message,&sys_status);
        emit batteryChanged(sys_status.voltage_battery);
    }
        break;

    //#24
     case MAVLINK_MSG_ID_GPS_RAW_INT:
    {
        mavlink_gps_raw_int_t gps_raw_int;
        mavlink_msg_gps_raw_int_decode(&message,&gps_raw_int);
        emit GPSStatusChanged(&gps_raw_int);
    }
        break;

    //#30
    case MAVLINK_MSG_ID_ATTITUDE:
    {
        mavlink_attitude_t attitude;
        mavlink_msg_attitude_decode(&message, &attitude);

        emit attitudeChanged(&attitude);
     }
        break;

    //#32
    case MAVLINK_MSG_ID_LOCAL_POSITION_NED:
    {
        mavlink_local_position_ned_t local_position;
        mavlink_msg_local_position_ned_decode(&message, &local_position);

        emit localPositionChanged(&local_position);
     }
        break;

    //#33
    case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
    {
        mavlink_global_position_int_t global_position_int;
        mavlink_msg_global_position_int_decode(&message, &global_position_int);

        emit globalPositionChanged(&global_position_int);
     }
        break;

    //#35
    case MAVLINK_MSG_ID_RC_CHANNELS_RAW:
    {
        mavlink_rc_channels_raw_t rc_channels_raw;
        mavlink_msg_rc_channels_raw_decode(&message,&rc_channels_raw);
        emit telemetryChanged(rc_channels_raw.rssi);
    }
        break;

        //#65 We handle both RC_CHANNLES and RC_CHANNELS_RAW since different firmware will only
            // send one or the other.
      case MAVLINK_MSG_ID_RC_CHANNELS:
      {
         mavlink_rc_channels_t rc_channels;
         mavlink_msg_rc_channels_decode(&message,&rc_channels);
         emit telemetryChanged(rc_channels.rssi);
      }
         break;

    //#74
    case MAVLINK_MSG_ID_VFR_HUD:
    {
        mavlink_vfr_hud_t vfr_hud;
        mavlink_msg_vfr_hud_decode(&message,&vfr_hud);
        emit groundSpeedChanged(vfr_hud.groundspeed);
    }
        break;

    //#105,just for PX4
   /* case MAVLINK_MSG_ID_HIGHRES_IMU:
    {
        mavlink_highres_imu_t pressure;
        mavlink_msg_highres_imu_decode(&message,&pressure);
        emit AltitudeChanged(pressure.pressure_alt);
    }
        break;
   */
    default:
        break;
    }

    _uas->receiveMessage(link,message);
}

void Vehicle::_handleHeartbeat(mavlink_message_t& message)
{
    mavlink_heartbeat_t heartbeat;
    mavlink_msg_heartbeat_decode(&message, &heartbeat);

    bool modechanged = false;

    bool armed = heartbeat.base_mode&MAV_MODE_FLAG_SAFETY_ARMED;
    if(_armed != armed)
    {
        _armed = armed;
        emit armedChanged(_armed);
    }

    if (_base_mode != heartbeat.base_mode || _custom_mode != heartbeat.custom_mode)
    {
        modechanged = true;
        _base_mode = heartbeat.base_mode;
        _custom_mode = heartbeat.custom_mode;
        QString shortModeText = flightMode(_base_mode,_custom_mode);
        //qDebug()<<shortModeText;
        emit modeChanged(shortModeText);
    }
}

QString Vehicle::flightMode(uint8_t baseMode, uint32_t customMode)
{
    QString flightMode = "Unknown";
    if(baseMode & MAV_MODE_FLAG_CUSTOM_MODE_ENABLED){
        union px4_custom_mode px4_mode;
        px4_mode.data = customMode;

        bool found = false;
        for(size_t i = 0;i<sizeof(modes2name)/sizeof(modes2name[0]);i++)
        {
            const struct Modes2Name* pModes2Name = &modes2name[i];
            if(pModes2Name->main_mode == px4_mode.main_mode && pModes2Name->sub_mode == px4_mode.sub_mode){
                flightMode = pModes2Name->name;
                found = true;
                break;
            }
        }
        if(!found){
            qDebug()<<"Unknown flight mode:"<<customMode;
        }
    }else{
        qDebug()<<"PX4 Flight Stack flight mode without custom mode enabled?";
    }
   return flightMode;
}

QStringList Vehicle::flightModes()
{
    QStringList flightModes;
    for(size_t i = 0; i < sizeof(modes2name)/sizeof(modes2name[0]); i++)
    {
        const struct Modes2Name* pModes2Name = &modes2name[i];

        if(pModes2Name->canBeSet) {
            flightModes += pModes2Name->name;
        }
    }
    return flightModes;
}
