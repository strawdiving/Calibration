#include "PowerComponent.h"
#include "PX4AutopilotPlugin.h"


PowerComponent::PowerComponent(PX4AutopilotPlugin* autopilot, QObject* parent)
    :VehicleComponent(autopilot,parent),
      _name("Power")
{

}

PowerComponent::~PowerComponent()
{

}

QStringList PowerComponent::setupCompleteChangedTriggerList(void) const
{
     return QStringList();
}

QString PowerComponent::name(void) const
{
    return _name;
}

QString PowerComponent::iconResource(void) const
{
    return "qmlImages/qmlImages/PowerComponentIcon.png";
}

QString PowerComponent::prerequisiteSetup(void) const
{
    if(!_autopilot->airframeComponent()->setupComplete()) {
        return _autopilot->airframeComponent()->name();
    }
    return QString();
}

bool PowerComponent::requiresSetup(void) const
{
    return true;
}

bool PowerComponent::setupComplete(void) const
{
    if((_autopilot->getParamFact(-1,"BAT_V_CHARGED")->rawValue().toFloat() != 0.0f) &&
            (_autopilot->getParamFact(-1,"BAT_V_EMPTY")->rawValue().toFloat() != 0.0f) &&
            (_autopilot->getParamFact(-1,"BAT_N_CELLS")->rawValue().toInt() != 0)) {
        return true;
    }
    return false;
}

