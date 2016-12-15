#include "AirframeComponent.h"
#include "PX4AutopilotPlugin.h"

AirframeComponent::AirframeComponent(PX4AutopilotPlugin *autopilot, QObject *parent)
    :VehicleComponent(autopilot,parent),
      _name("Airframe")
{

}

AirframeComponent::~AirframeComponent()
{

}

QString AirframeComponent::name(void) const
{
    return _name;
}

QString AirframeComponent::iconResource(void) const
{
    return "/qmlImages/qmlImages/Airframe/AirframeComponentIcon.png";

}

QString AirframeComponent::prerequisiteSetup(void) const
{
    return QString();
}

bool AirframeComponent::requiresSetup(void) const
{
    return true;
}

QStringList AirframeComponent::setupCompleteChangedTriggerList(void) const
{
    return QStringList("SYS_AUTOSTART");
}

bool AirframeComponent::setupComplete(void) const
{
  return _autopilot->getParamFact(-1, "SYS_AUTOSTART")->rawValue().toInt()!=0;
}
