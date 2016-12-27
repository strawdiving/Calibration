#include "UAS.h"
#include "Vehicle.h"
#include "linkmanager.h"
#include <QDebug>

UAS::UAS(Vehicle *vehicle)
    : _uasId(vehicle->id())
    , _status(-1)
    , _parameterLoader(NULL)
    , _vehicle(vehicle)
{

}

UAS::~UAS()
{

}

void UAS::_activeVehicleChanged(Vehicle* vehicle)
{
    Q_UNUSED(vehicle)

}

void UAS::startCalibration(CalibrationType calType)
{
    if(!_vehicle) {
        return;
    }

    int gyroCal = 0;
    int magCal = 0;
    int accelCal = 0;
    int radioCal = 0;
    int escCal = 0;

    switch(calType) {
    case CalibrationGyro:
        gyroCal = 1;
        break;
    case CalibrationMag:
        magCal = 1;
        break;
    case CalibrationAccel:
        accelCal = 1;
        break;
    case CalibrationLevel:
        accelCal = 2;
        break;
    case CalibrationRadio:
        radioCal = 1;
        break;
    case CalibrationESC:
        escCal = 1;
        break;
    }

    mavlink_message_t msg;
    mavlink_command_long_t command;
    command.target_system = _uasId;
    command.target_component = 0;
    command.command = MAV_CMD_PREFLIGHT_CALIBRATION;
    command.confirmation = 0; // 0 = first transmission of command
    command.param1 = gyroCal; //gyro cal
    command.param2 = magCal; //mag cal
    command.param3 = 0; //ground pressure
    command.param4 = radioCal; //radio cal
    command.param5 = accelCal; //accel cal
    command.param6 = 0; //airspeed cal (compass/motor interference cal)
    command.param7 = escCal; //empty?
    mavlink_msg_command_long_encode(_uasId,defaultComponentId,&msg,&command);
    _vehicle->linkManager()->sendMessage(msg);
}

void UAS::stopCalibration(void)
{
    if(!_vehicle) {
        return;
    }

    mavlink_message_t msg;
    mavlink_command_long_t command;
    command.target_system = _uasId;
    command.target_component = 0;
    command.command = MAV_CMD_PREFLIGHT_CALIBRATION;
    command.confirmation = 0; // 0 = first transmission of command
    command.param1 = 0; //gyro cal
    command.param2 = 0; //mag cal
    command.param3 = 0; //ground pressure
    command.param4 = 0; //radio cal
    command.param5 = 0; //accel cal
    command.param6 = 0; //airspeed cal (compass/motor interference cal)
    command.param7 = 0; //empty?
    mavlink_msg_command_long_encode(_uasId,defaultComponentId,&msg,&command);
    _vehicle->linkManager()->sendMessage(msg);
}

void UAS::receiveMessage(SerialLink*link, mavlink_message_t &message)
{
    Q_UNUSED(link)
    //qDebug()<<"uas:receiveMessage"<<message.sysid<<message.compid;
    if(!components.contains(message.compid)) {
        QString compName;
        switch(message.compid)
        {
        case MAV_COMP_ID_ALL:
        {
            compName = "ANONYMOUS";
            break;
        }
        case MAV_COMP_ID_IMU:
        {
            compName = "IMU #1";
            break;
        }
        default:
            break;
        }
        components.insert(message.compid,compName);
    }

    if(message.sysid == _uasId) {

        QString uasState;
        QString stateDescription;

        switch(message.msgid) {
        case MAVLINK_MSG_ID_HEARTBEAT:
        {
            mavlink_heartbeat_t heartbeat;
            mavlink_msg_heartbeat_decode(&message,&heartbeat);
            //qDebug()<<heartbeat.system_status<<this->_status;
            //if((heartbeat.system_status!=this->_status)&&(heartbeat.system_status != MAV_STATE_UNINIT)) {
            if((heartbeat.system_status!=this->_status)) {
             this->_status = heartbeat.system_status;
                getStatusForCode(heartbeat.system_status,uasState,stateDescription);
                emit statusChanged(uasState);
           }
        }
            break;

        case MAVLINK_MSG_ID_PARAM_VALUE:
        {
            qDebug()<<"Param_Value message received";
            mavlink_param_value_t param_value;
            mavlink_msg_param_value_decode(&message,&param_value);
            //QByteArray(const char *data, int size = -1)
            QByteArray bytes(param_value.param_id,MAVLINK_MSG_PARAM_VALUE_FIELD_PARAM_ID_LEN);
            QString paramName(bytes);

            mavlink_param_union_t paramUnion;
            paramUnion.param_float = param_value.param_value;
            paramUnion.type = param_value.param_type;

            processParamValueMsg(message,paramName,param_value,paramUnion);
        }
            break;

        case MAVLINK_MSG_ID_STATUSTEXT:
        {
            mavlink_statustext_t statustext;
            mavlink_msg_statustext_decode(&message,&statustext);
            //Status text message, without null termination character
            QByteArray b(statustext.text);
            b.append('\0');
            QString text = b;
            int severity = statustext.severity;

            //QGC source code
            /*
            QByteArray b;
            b.resize(MAVLINK_MSG_STATUSTEXT_FIELD_TEXT_LEN+1);
            mavlink_msg_statustext_get_text(&message, b.data());

            // Ensure NUL-termination
            b[b.length()-1] = '\0';
            QString text = QString(b);
            int severity = mavlink_msg_statustext_get_severity(&message);
            */

            // If the message is NOTIFY or higher severity, or starts with a '#',
            // then read it aloud.
            if(text.startsWith("#") || severity <= MAV_SEVERITY_NOTICE) {
                text.remove("#");
                emit textMessageReceived(_uasId,message.compid,severity,text);
            }
            else {
                emit textMessageReceived(_uasId,message.compid,severity,text);
            }
        }
            break;

        case MAVLINK_MSG_ID_EXTENDED_SYS_STATE:
        {
            mavlink_extended_sys_state_t extendedState;
            mavlink_msg_extended_sys_state_decode(&message, &extendedState);

            switch (extendedState.landed_state) {
                case MAV_LANDED_STATE_UNDEFINED:
                break;
            case MAV_LANDED_STATE_ON_GROUND:
                //setFlying(false);
                //qDebug()<<"MAV IS LANDED ON GROUND";
                break;
            case MAV_LANDED_STATE_IN_AIR:
                //setFlying(true);
                return;
            }
        }
        }
    }
}


//Get the status of the code and a description of the status.
void UAS::getStatusForCode(int statusCode, QString& uasState, QString& stateDescription)
{
    switch(statusCode) {
    case MAV_STATE_UNINIT:
        uasState =tr("UNINIT");
        stateDescription = tr("Unitialized, booting up.");
        break;
    case MAV_STATE_BOOT:
        uasState =tr("BOOT");
        stateDescription = tr("Booting system, please wait.");
        break;
    case MAV_STATE_CALIBRATING:
        uasState =tr("CALIBRATING");
        stateDescription = tr("Calibrating sensors, please wait.");
        break;
    case MAV_STATE_ACTIVE:
        uasState =tr("ACTIVE");
        stateDescription = tr("Active, normal operation.");
        break;
    case MAV_STATE_STANDBY:
        uasState =tr("STANDBY");
        stateDescription = tr("Standby mode, ready for launch.");
        break;
    case MAV_STATE_CRITICAL:
        uasState =tr("CRITICAL");
        stateDescription = tr("FAILURE: Continuing operation.");
        break;
    case MAV_STATE_EMERGENCY:
        uasState = tr("EMERGENCY");
        stateDescription = tr("EMERGENCY: Land Immediately!");
        break;
    case MAV_STATE_POWEROFF:
        uasState = tr("SHUTDOWN");
        stateDescription = tr("Powering off system.");
        break;

    default:
        uasState = tr("UNKNOWN");
        stateDescription = tr("Unknown system state");
        break;
    }

}

void UAS::processParamValueMsg(mavlink_message_t &message,const QString &paramName,const mavlink_param_value_t &rawValue,mavlink_param_union_t &paramUnion)
{
    int componentId = message.compid;
    QVariant paramValue;

    switch(rawValue.param_type)
    {
    case MAV_PARAM_TYPE_UINT8:
        paramValue = QVariant(paramUnion.param_uint8);
        break;
    case MAV_PARAM_TYPE_INT8:
        paramValue = QVariant(paramUnion.param_int8);
        break;
    case MAV_PARAM_TYPE_UINT16:
        paramValue = QVariant(paramUnion.param_uint16);
        break;
    case MAV_PARAM_TYPE_INT16:
        paramValue = QVariant(paramUnion.param_int16);
        break;
    case MAV_PARAM_TYPE_UINT32:
        paramValue = QVariant(paramUnion.param_uint32);
        break;
    case MAV_PARAM_TYPE_INT32:
        paramValue = QVariant(paramUnion.param_int32);
        break;
    case MAV_PARAM_TYPE_REAL32:
        paramValue = QVariant(paramUnion.param_float);
        break;

        //-- Note: These are not handled above:
        //   No space in message (the only storage allocation is a "float") and not present in mavlink_param_union_t

        //   MAV_PARAM_TYPE_UINT64
        //   MAV_PARAM_TYPE_INT64
        //   MAV_PARAM_TYPE_REAL64

        default:
            qCritical() << "INVALID DATA TYPE USED AS PARAMETER VALUE: " << rawValue.param_type;
    }
    qDebug() << "Received PARAM_VALUE" << paramName << paramValue << rawValue.param_type;

    emit parameterUpdate(componentId, paramName,rawValue.param_count,rawValue.param_index,rawValue.param_type,paramValue);
}

void UAS::shutdownVehicle(void)
{
    _vehicle = NULL;
}

void UAS::_readParameterRaw(int componentId, const QString& paramName, int paramIndex)
{
    Q_UNUSED(componentId)
    Q_UNUSED(paramIndex)
    mavlink_message_t msg;
    mavlink_param_request_read_t param;

    Q_UNUSED(msg)
    Q_UNUSED(param)
    char fixedParamName[MAVLINK_MSG_PARAM_REQUEST_READ_FIELD_PARAM_ID_LEN];
    strncpy_s(fixedParamName,paramName.toStdString().c_str(),sizeof(fixedParamName));

    //mavlink_msg_param_request_read_pack(255,0,&msg,TargetSystemID,componentId,fixedParamName,paramIndex);
    //sendMessage(msg);
}

void UAS::_writeParameterRaw(int componentId, const QString& paramName, const QVariant& value)
{
    mavlink_param_set_t paramSet;
    mavlink_param_union_t unionValue;

}
