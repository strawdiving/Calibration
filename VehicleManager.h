#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H

#include "Toolbox.h"
#include "Vehicle.h"

class QuadApplication;
class LinkManager;
class SerialLink;
class PX4FirmwarePlugin;

class VehicleManager : public ToolBase
{
    Q_OBJECT
public:
    VehicleManager(QuadApplication* app);
    ~VehicleManager();

    virtual void setToolbox(Toolbox* toolbox);
    Vehicle* activeVehicle(void)     {
        if(_activeVehicle) {
            return _activeVehicle;
        }
        return NULL;
    }

signals:
    void activeVehicleChanged(Vehicle* vehicle);
    void parameterReadyVehicleAvailableChanged(bool parameterReadyVehicleAvailable);

public slots:
       void _vehicleHeartbeatInfo(SerialLink* link, int vehicleId, int vehicleMavlinkVersion, int vehicleFirmwareType, int vehicleType);
       void _autopilotParametersReadyChanged(bool parametersReady);       

private slots:
       void _deleteVehicle(Vehicle* vehicle);

private:
       LinkManager* _linkMgr;
       Vehicle* _activeVehicle;
       bool _parameterReadyVehicleAvailable;
       PX4FirmwarePlugin* _firmwarePlugin;
};

#endif // VEHICLEMANAGER_H
