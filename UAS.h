#ifndef UAS_H
#define UAS_H

#include <QObject>
#include <QMap>
#include <common/mavlink.h>
#include <mavlink_types.h>
#include "ParameterLoader.h"
#include "Vehicle.h"

///This class represents one vehicle. It can be used like the real vehicle
/// e.g. a call to halt() will automatically send the appropriate messages to the vehicle.
/// The vehicle state will also be automatically updated by the comm architecture
class UAS : public QObject
{
    Q_OBJECT

public:
    UAS(Vehicle* vehicle);
    ~UAS();
    /** @brief Get the human-readable status message for this code */
   void getStatusForCode(int statusCode, QString& uasState, QString& stateDescription);
   void receiveMessage(SerialLink *link, mavlink_message_t &message);

protected:
    QMap<int, QString> components;///< IDs and names of all detected onboard components

signals:
    void statusChanged(QString status);

    ///component: componentId
    /// paramName-- param_value.param_id[16]
    /// paramCount--param_value.param_count
    /// paramId--param_value.param_index
    /// type--param_value.param_type
    /// value-- according to the type(MAV_PARAM_TYPE),adjust the param_union value
    void parameterUpdate(int componentId, QString paramName, int paramCount, int paramId, int type, QVariant value);

    ///brief A text message from the system has been received
    void textMessageReceived(int uasid, int componentid, int severity, QString text);

public slots:
    void _activeVehicleChanged(Vehicle* vehicle);
    /// Vehicle is about to go away
    void shutdownVehicle(void);

    void _readParameterRaw(int componentId, const QString& paramName, int paramIndex);
    void _writeParameterRaw(int componentId, const QString& paramName, const QVariant& value);

private:
    void processParamValueMsg(mavlink_message_t &message,const QString &paramName,const mavlink_param_value_t &rawValue,mavlink_param_union_t &paramValue);

    ParameterLoader * _parameterLoader;
    Vehicle *_vehicle;

    int _uasId;                    ///< Unique system ID
     /// BASIC UAS TYPE, NAME AND STATE
    int _status;                   ///< The current status of the MAV
};

#endif // UAS_H
