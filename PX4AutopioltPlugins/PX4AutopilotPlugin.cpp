#include "PX4AutopilotPlugin.h"
#include "ParameterLoader.h"
#include "Vehicle.h"

PX4AutopilotPlugin::PX4AutopilotPlugin(Vehicle* vehicle,QObject *parent)
    : QObject(parent),
      _airframeComponent(NULL),
      _flightmodesComponent(NULL),
      _powerComponent(NULL),
      _radioComponent(NULL),
      _safetyComponent(NULL),
      _sensorsComponent(NULL),
      //_px4ParameterMetaData(NULL),
      _vehicle(vehicle),
      _parametersReady(false),
      _setupComplete(false)
{

    connect(this,&PX4AutopilotPlugin::parametersReadyChanged,this,&PX4AutopilotPlugin::_parametersReadyChanged);

    //_px4ParameterMetaData = new PX4ParameterMetaData();vehicleComponents.append(QVariant::fromValue((VehicleComponent*)_airframeComponent));
    //_px4ParameterMetaData->loadParamFactMetaDataFile();
    //connect(_px4ParameterMetaData,&PX4ParameterMetaData::factMetaData,this,&ParamsPage::showParams);
    //connect(_px4ParameterMetaData,&PX4ParameterMetaData::factMetaData,_parameterLoader,&ParameterLoader:);
}

const QVariantList& PX4AutopilotPlugin::vehicleComponents(void)
{
    if(_vehicleComponents.count() == 0) {
    _airframeComponent = new AirframeComponent(this);
    _airframeComponent->setupTriggerSignals();

    _flightmodesComponent = new FlightModesComponent(this);
    _flightmodesComponent->setupTriggerSignals();

    _powerComponent = new PowerComponent(this);
    _powerComponent->setupTriggerSignals();

    _radioComponent = new RadioComponent(this);
    _radioComponent->setupTriggerSignals();

    _safetyComponent = new SafetyComponent(this);
    _safetyComponent->setupTriggerSignals();

    _sensorsComponent = new SensorsComponent(this);
    _sensorsComponent->setupTriggerSignals();

    _vehicleComponents.append(QVariant::fromValue((VehicleComponent*)_airframeComponent));
    _vehicleComponents.append(QVariant::fromValue((VehicleComponent*)_flightmodesComponent));
    _vehicleComponents.append(QVariant::fromValue((VehicleComponent*)_powerComponent));
    _vehicleComponents.append(QVariant::fromValue((VehicleComponent*)_radioComponent));
    _vehicleComponents.append(QVariant::fromValue((VehicleComponent*)_safetyComponent));
    _vehicleComponents.append(QVariant::fromValue((VehicleComponent*)_sensorsComponent));
    }
    return _vehicleComponents;
}

PX4AutopilotPlugin::~PX4AutopilotPlugin()
{

}

void PX4AutopilotPlugin::_parametersReadyPreCheck(bool noMissingParams)
{
    qDebug()<<"PX4AutopilotPlugin::_parametersReadyPreCheck";
    Q_UNUSED(noMissingParams)

    // Check for older parameter version set
    //P.S. px4 new version has no either
    if (paramExists(defaultCompId, "SENS_GYRO_XOFF") ||
            paramExists(defaultCompId, "COM_DL_LOSS_EN")) {
        //_incorrectParameterVersion = true;
        qDebug()<<"This version of GroundControl can only perform vehicle setup on a newer version of firmware. ";

       // qgcApp()->showMessage("This version of GroundControl can only perform vehicle setup on a newer version of firmware. "
                             // "Please perform a Firmware Upgrade if you wish to use Vehicle Setup.");
    }
    _parametersReady = true;
    emit parametersReadyChanged(_parametersReady);
}

void PX4AutopilotPlugin::_parametersReadyChanged(bool parametersReady)
{
    qDebug()<<"PX4AutopilotPlugin::_parametersReadyChanged: "<<parametersReady;
    if(parametersReady) {
        _recalcSetupComplete();
    }

    if(!_setupComplete)
    {
        //qgcApp()->showMessage("One or more vehicle components require setup prior to flight.");


        // Take the user to Vehicle Summary
        //qgcApp()->showSetupView();

        emit showMessage(QString("One or more vehicle components require setup prior to flight."));
        emit showSetupView();


        //qgcApp()->processEvents(QEventLoop::ExcludeUserInputEvents);
    }


}


void PX4AutopilotPlugin::_recalcSetupComplete(void)
{
    bool newSetupComplete = true;
    foreach (QVariant componentVariant, vehicleComponents()) {
        VehicleComponent* component = qobject_cast<VehicleComponent*>(qvariant_cast<QObject *>(componentVariant));
        Q_ASSERT(component);

        if(!component->setupComplete()) {            
            newSetupComplete = false;
            break;
        }

        //For test
        emit setupCompleteChanged(_setupComplete);

        if(_setupComplete!=newSetupComplete) {
            _setupComplete = newSetupComplete;
            qDebug()<<"PX4AutopilotPlugin: setupCompleteChanged";
            emit  setupCompleteChanged(_setupComplete);
        }
    }
}

bool PX4AutopilotPlugin::paramExists(int componentId,const QString& name)
{
    return _vehicle->parameterLoader()->paramExists(componentId,name);
}

Fact* PX4AutopilotPlugin::getParamFact(int componentId, const QString& name)
{
    return _vehicle->parameterLoader()->getFact(componentId,name);
}
