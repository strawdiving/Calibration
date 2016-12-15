#ifndef RADIOCOMPONENT_H
#define RADIOCOMPONENT_H

#include "VehicleComponent.h"

class RadioComponent: public VehicleComponent
{
    Q_OBJECT
public:
    RadioComponent(PX4AutopilotPlugin* autopilot, QObject* parent = NULL);
    ~RadioComponent();

    // Virtuals from VehicleComponent
    virtual QStringList setupCompleteChangedTriggerList(void) const;

    // Virtuals from VehicleComponent
    virtual QString name(void) const;
    virtual QString iconResource(void) const;
    virtual QString prerequisiteSetup(void) const;
    virtual bool requiresSetup(void) const;
    virtual bool setupComplete(void) const;


private:
    const QString   _name;
};

#endif // RADIOCOMPONENT_H
