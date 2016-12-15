#ifndef POWERCOMPONENT_H
#define POWERCOMPONENT_H

#include "VehicleComponent.h"

class PowerComponent : public VehicleComponent
{
    Q_OBJECT

public:
    PowerComponent(PX4AutopilotPlugin* autopilot, QObject* parent = NULL);
    ~PowerComponent();
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

#endif // POWERCOMPONENT_H
