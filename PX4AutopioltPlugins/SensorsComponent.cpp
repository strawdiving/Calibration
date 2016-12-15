#include "SensorsComponent.h"
#include "PX4AutopilotPlugin.h"

SensorsComponent::SensorsComponent(PX4AutopilotPlugin *autopilot, QObject *parent)
    :VehicleComponent(autopilot,parent),
      _name("Sensors")
{

}

SensorsComponent::~SensorsComponent()
{

}

QStringList SensorsComponent::setupCompleteChangedTriggerList(void) const
{
    QStringList list;
    list<<QStringLiteral("CAL_MAG0_ID")<<QStringLiteral("CAL_GYRO0_ID")
       <<QStringLiteral("CAL_ACC0_ID");
    return list;
}

QString SensorsComponent::name(void) const
{
    return _name;
}

QString SensorsComponent::iconResource(void) const
{
    return "qmlImages/qmlImages/SensorsComponentIcon";
}

QString SensorsComponent::prerequisiteSetup(void) const
{
    if(!_autopilot->airframeComponent()->setupComplete()) {
        return _autopilot->airframeComponent()->name();
    }
    return QString();
}

bool SensorsComponent::requiresSetup(void) const
{
    return true;
}

bool SensorsComponent::setupComplete(void) const
{
    if((_autopilot->getParamFact(-1,"CAL_MAG0_ID")->rawValue().toFloat() != 0.0f) &&
            (_autopilot->getParamFact(-1,"CAL_GYRO0_ID")->rawValue().toFloat() != 0.0f)&&
            (_autopilot->getParamFact(-1,"CAL_ACC0_ID")->rawValue().toFloat() != 0.0f)) {
        return true;
    }
    return false;
}
