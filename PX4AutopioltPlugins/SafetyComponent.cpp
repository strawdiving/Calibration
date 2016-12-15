#include "SafetyComponent.h"
#include "PX4AutopilotPlugin.h"

SafetyComponent::SafetyComponent(PX4AutopilotPlugin *autopilot, QObject *parent)
    :VehicleComponent(autopilot,parent),
      _name("Safety")
{

}

SafetyComponent::~SafetyComponent()
{

}

QStringList SafetyComponent::setupCompleteChangedTriggerList(void) const
{
     return QStringList();
}

QString SafetyComponent::name(void) const
{
    return _name;
}

QString SafetyComponent::iconResource(void) const
{
    return "qmlImages/qmlImages/SafetyComponentIcon";
}

QString SafetyComponent::prerequisiteSetup(void) const
{
    if(!_autopilot->airframeComponent()->setupComplete()) {
        return _autopilot->airframeComponent()->name();
    }
    return QString();
}

bool SafetyComponent::requiresSetup(void) const
{
    return false;
}

bool SafetyComponent::setupComplete(void) const
{
    return true;
}
