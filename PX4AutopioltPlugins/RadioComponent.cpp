#include "RadioComponent.h"
#include "PX4AutopilotPlugin.h"

RadioComponent::RadioComponent(PX4AutopilotPlugin* autopilot,QObject* parent)
    :VehicleComponent(autopilot,parent),
      _name("Radio")
{

}

RadioComponent::~RadioComponent()
{

}

QStringList RadioComponent::setupCompleteChangedTriggerList(void) const
{
    QStringList list;
    list<<QStringLiteral("COM_RC_IN_MODE")<<QStringLiteral("RC_MAP_ROLL")
       <<QStringLiteral("RC_MAP_PITCH")<<QStringLiteral("RC_MAP_YAW")<<QStringLiteral("RC_MAP_THROTTLE");
    return list;

}

QString RadioComponent::name(void) const
{
    return _name;
}

QString RadioComponent::iconResource(void) const
{
    return "qmlImages/qmlImages/RadioComponentIcon.png";
}

QString RadioComponent::prerequisiteSetup(void) const
{
    if(_autopilot->getParamFact(-1,"COM_RC_IN_MODE")->rawValue().toInt() !=1) {
        if(!_autopilot->airframeComponent()->setupComplete()) {
            return _autopilot->airframeComponent()->name();
        }
    }
    return QString();
}

bool RadioComponent::requiresSetup(void) const
{
    return _autopilot->getParamFact(-1,"COM_RC_IN_MODE")->rawValue().toInt() == 1? false:true;
}

bool RadioComponent::setupComplete(void) const
{
    if(_autopilot->getParamFact(-1,"COM_RC_IN_MODE")->rawValue().toInt() == 1) {
        return true;
    }
    else {
        // look for attitude controls to be mapped to detect the need for a radio calibration
        QStringList attitudeMaps;
        attitudeMaps << "RC_MAP_ROLL"<<"RC_MAP_PITCH"<<"RC_MAP_YAW"<<"RC_MAP_THRTTLE";
        foreach (QString attitudeMap, attitudeMaps) {
            if(_autopilot->getParamFact(-1,attitudeMap)->rawValue().toInt() == 0) {
                return false;
            }
        }
        return true;
    }
}
