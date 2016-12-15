#ifndef UASMESSAGEHANDLER_H
#define UASMESSAGEHANDLER_H

#include "Toolbox.h"
#include "UAS.h"

class QuadApplication;
class VehicleManager;
class Vehicle;

class UASMessageHandler : public ToolBase
{
    Q_OBJECT
public:
    UASMessageHandler(QuadApplication* app);
    ~UASMessageHandler();

    virtual void setToolbox(Toolbox* toolbox);


public slots:
    void _activeVehicleChanged(Vehicle* vehicle);
    void handleTextMessage(int uasid, int componentid, int severity, QString text);

private:
    VehicleManager* _vehicleManager;
    UAS* _activeUAS;
};

#endif // UASMESSAGEHANDLER_H
