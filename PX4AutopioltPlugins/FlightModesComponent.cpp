#include "FlightModesComponent.h"
#include "PX4AutopilotPlugin.h"


FlightModesComponent::FlightModesComponent(PX4AutopilotPlugin* autopilot, QObject* parent)
    :VehicleComponent(autopilot,parent),
      _name("Flight Modes")
{

}

FlightModesComponent::~FlightModesComponent()
{

}

QStringList FlightModesComponent::setupCompleteChangedTriggerList(void) const
{
   QStringList list;
   list<<QStringLiteral("RC_MAP_MODE_SW")<<QStringLiteral("RC_MAP_FLMODE");
   return list;
}

QString FlightModesComponent::name(void) const
{
    return _name;
}

QString FlightModesComponent::iconResource(void) const
{
    return "qmlImages/qmlImages/FlightModesComponentIcon.png";
}

QString FlightModesComponent::prerequisiteSetup(void) const
{
    if(_autopilot->getParamFact(-1,"COM_RC_IN_MODE")->rawValue().toInt() ==1) {
        //No RC input
        return QString();
    }
    else {
        if(!_autopilot->airframeComponent()->setupComplete()) {
            return _autopilot->airframeComponent()->name();
        } else if(!_autopilot->radioComponent()->setupComplete()) {
            return _autopilot->radioComponent()->name();
        } else if(!_autopilot->sensorsComponent()->setupComplete()) {
            return _autopilot->sensorsComponent()->name();
        }
    }
    return QString();
}

bool FlightModesComponent::requiresSetup(void) const
{
    return _autopilot->getParamFact(-1,"COM_RC_IN_MODE")->rawValue().toInt()==1? false:true;

}

bool FlightModesComponent::setupComplete(void) const
{
    if(_autopilot->getParamFact(-1,"COM_RC_IN_MODE")->rawValue().toInt()==1) {
        return true;
    }
    if(_autopilot->getParamFact(-1,"RC_MAP_SW")->rawValue().toInt() !=0 ||
            (_autopilot->paramExists(-1,"RC_MAP_FLTMODE")&&_autopilot->getParamFact(-1,"RC_MAP_FLTMODE")!=0)) {
        return true;
    }
    return false;
}
