#include "UASMessageHandler.h"
#include "VehicleManager.h"
#include "Vehicle.h"

UASMessageHandler::UASMessageHandler(QuadApplication *app)
    :ToolBase(app)
    , _vehicleManager(NULL)
    , _activeUAS(NULL)
{


}

UASMessageHandler::~UASMessageHandler()
{

}

void UASMessageHandler::setToolbox(Toolbox* toolbox)
{
    ToolBase::setToolbox(toolbox);
    _vehicleManager = _toolbox->vehicleManager();

    connect(_vehicleManager,&VehicleManager::activeVehicleChanged, this,&UASMessageHandler::_activeVehicleChanged);
}

 void UASMessageHandler::_activeVehicleChanged(Vehicle* vehicle)
 {
     if(_activeUAS) {
         _activeUAS = NULL;
     }

     if(vehicle) {
         UAS* uas = vehicle->uas();
         _activeUAS = uas;
         connect(_activeUAS,&UAS::textMessageReceived,this,&UASMessageHandler::handleTextMessage);
     }
 }

 void UASMessageHandler::handleTextMessage(int uasid, int componentid, int severity, QString text)
 {
     Q_UNUSED(uasid)
     Q_UNUSED(componentid)
     Q_UNUSED(severity)

     qDebug()<<"text: "<<text;
 }
