#ifndef AIRFRAMECOMPONENT_H
#define AIRFRAMECOMPONENT_H

#include "VehicleComponent.h"

class AirframeComponent : public VehicleComponent
{
    Q_OBJECT
public:
    AirframeComponent(PX4AutopilotPlugin* autopilot, QObject* parent = NULL);
    ~AirframeComponent();

    // Virtuals from VehicleComponent
    virtual QStringList setupCompleteChangedTriggerList(void) const;

    virtual QString name(void) const;
    virtual QString iconResource(void) const;
    virtual QString prerequisiteSetup(void) const;
    virtual bool requiresSetup(void) const;
    virtual bool setupComplete(void) const;

private:
    QString _name;
};

#endif // AIRFRAMECOMPONENT_H
