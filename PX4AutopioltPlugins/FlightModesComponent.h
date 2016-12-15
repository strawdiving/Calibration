#ifndef FLIGHTMODESCOMPONENT_H
#define FLIGHTMODESCOMPONENT_H

#include "VehicleComponent.h"

class FlightModesComponent: public VehicleComponent
{
    Q_OBJECT

public:
    FlightModesComponent(PX4AutopilotPlugin* autopilot, QObject* parent = NULL);
    ~FlightModesComponent();

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

#endif // FLIGHTMODESCOMPONENT_H
