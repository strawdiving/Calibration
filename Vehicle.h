#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include <common/mavlink.h>
#include "SerialCommunication.h"
#include <QVariant>
#include <mavlink_types.h>
#include <QDebug>
#include "FactMetaData.h"

class PX4FirmwarePlugin;
class PX4AutopilotPlugin;
class Vehicle;
class LinkManager;
class UAS;
class ParameterLoader;

class Vehicle : public QObject
{
    Q_OBJECT
public:
    explicit Vehicle(SerialLink* link, int vehicleId, MAV_TYPE vehicleType,PX4FirmwarePlugin* firmwarePlugin);
    ~Vehicle();

    /// Provides access to uas from vehicle. Temporary workaround until AutoPilotPlugin is fully phased out.
    PX4AutopilotPlugin* autopilotPlugin(void) {return _autopilotPlugin;}
    UAS* uas(void) {return _uas;}
    ParameterLoader* parameterLoader(void) {return _parameterLoader;}
    PX4FirmwarePlugin* firmwarePlugin(void) {return _firmwarePlugin;}
    LinkManager* linkManager(void) { return _linkMgr;}

    int id(void) { return _vehicleId;}

    void setActive(bool active);    

    QString flightMode(uint8_t baseMode, uint32_t customMode);

    /// Returns the list of available flight modes
    QStringList flightModes();

    bool armed(void) {return _armed;}
    bool active(void) {return _active;}

signals:
    void linkDeleted(Vehicle* vehicle);
    void vehicleAdded(Vehicle* vehicle);

    void modeChanged(QString shortModeText);
    void armedChanged(bool armed);
    void telemetryChanged(uint8_t rssi);
    void attitudeChanged(mavlink_attitude_t* attitude);
    void altitudeChanged(float pressure_alt);
    void batteryChanged(uint16_t voltage_battery);
    void GPSStatusChanged(mavlink_gps_raw_int_t* gps_raw_int);
    void globalPositionChanged(mavlink_global_position_int_t* global_position_int);
    void localPositionChanged(mavlink_local_position_ned_t* local_position);
    void groundSpeedChanged(float);

    void parameterReadyVehicleAvailableChanged(bool parameterReadyVehicleAvailable);
    //void activeVehicleChanged(Vehicle* activeVehicle);

    ///For test
    void paramUpdate(int paramCount,QString paramName,FactMetaData::ValueType_t type,QVariant& value);

public slots:
    void _linkDeleted(SerialLink* link);
    void _mavlinkMessageReceived(SerialLink*link, mavlink_message_t &message);
    ///For test
    void _paramUpdate(int paramCount,QString paramName,FactMetaData::ValueType_t type,QVariant& value);

private:
    void _addLink(SerialLink* link);
    void _handleHeartbeat(mavlink_message_t& message);

    PX4FirmwarePlugin* _firmwarePlugin;
    PX4AutopilotPlugin* _autopilotPlugin;
    SerialLink* _link;
    int _vehicleId;
    MAV_TYPE _vehicleType;
    LinkManager * _linkMgr;
    UAS* _uas;

    ParameterLoader* _parameterLoader;

    uint8_t             _compID;
    bool                _heardFrom;
    bool _active;

    //flight modes
    uint8_t     _base_mode;
    uint32_t   _custom_mode;
    bool         _armed;

    static const char* manualFMode;
    static const char* stabilizedFMode;
    static const char* altCtlFMode;                                       //ALT_CTRL
    static const char* posCtlFMode;                                    //POS_CTRL
    static const char* offboardFMode;                                 //OFFBOARD
    static const char* rtlFMode;                                            //AUTO_RTL
    static const char* loiterFMode;                                       //AUTO_LOITER    
};

#endif // VEHICLE_H
