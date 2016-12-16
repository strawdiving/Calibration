#ifndef PX4AUTOPILOTPLUGIN_H
#define PX4AUTOPILOTPLUGIN_H

#include "AirframeComponent.h"
#include "FlightModesComponent.h"
#include "PowerComponent.h"
#include "RadioComponent.h"
#include "SafetyComponent.h"
#include "SensorsComponent.h"
#include "Fact.h"
#include "PX4ParameterMetaData.h"
//#include "Vehicle.h"

class Vehicle;

class PX4AutopilotPlugin : public QObject
{
    Q_OBJECT

public:
    PX4AutopilotPlugin(Vehicle* vehicle, QObject* parent);
    ~PX4AutopilotPlugin();

    AirframeComponent* airframeComponent() {return _airframeComponent;}
    FlightModesComponent* flightmodesComponent() { return _flightmodesComponent;}
    PowerComponent* powerComponent() { return _powerComponent;}
    RadioComponent* radioComponent() { return _radioComponent;}
    SafetyComponent* safetyComponent() { return _safetyComponent;}
    SensorsComponent* sensorsComponent() { return _sensorsComponent;}

    Fact* getParamFact(int componentId, const QString& name);
    bool paramExists(int componentId,const QString& name);

    bool parametersReady(void) { return _parametersReady;}

    const QVariantList& vehicleComponents(void);

    static const int defaultCompId = -1;

signals:
    void parametersReadyChanged(bool paramsReady);
    void setupCompleteChanged(bool setupComplete);
    void showMessage(const QString text);
    void showSetupView();

    void setupCompleteStatus(QString componentName,bool setupComplete);

public slots:
    void _parametersReadyPreCheck(bool noMissingParams);
    void _parametersReadyChanged(bool parametersReady);

private:
    void _recalcSetupComplete(void);

    AirframeComponent* _airframeComponent;
    FlightModesComponent* _flightmodesComponent;
    PowerComponent* _powerComponent;
    RadioComponent* _radioComponent;
    SafetyComponent* _safetyComponent;
    SensorsComponent* _sensorsComponent;

    //PX4ParameterMetaData * _px4ParameterMetaData;
    Vehicle* _vehicle;
    bool _parametersReady;
    bool _setupComplete;

    QVariantList _vehicleComponents;

};

#endif // PX4AUTOPILOTPLUGIN_H
