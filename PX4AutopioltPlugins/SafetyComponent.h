#ifndef SAFETYCOMPONENT_H
#define SAFETYCOMPONENT_H

#include "VehicleComponent.h"

class SafetyComponent: public VehicleComponent
{
    Q_OBJECT
public:
    SafetyComponent(PX4AutopilotPlugin* autopilot, QObject* parent = NULL);
    ~SafetyComponent();

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

#endif // SAFETYCOMPONENT_H
