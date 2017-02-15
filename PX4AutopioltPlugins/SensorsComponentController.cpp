#include "SensorsComponentController.h"
#include "UAS.h"
#include "QuadApplication.h"

#include <QVariant>
#include <QDebug>

SensorsComponentController::SensorsComponentController()
  //  :
{

}

SensorsComponentController::~SensorsComponentController()
{

}

void SensorsComponentController::calibrateGyro(void)
{
    connect(_uas,&UAS::textMessageReceived,this,&SensorsComponentController::_handleUASTextMessage);
    _uas->startCalibration(UAS::CalibrationGyro);
}

void SensorsComponentController::calibrateCompass(void)
{
    connect(_uas,&UAS::textMessageReceived,this,&SensorsComponentController::_handleUASTextMessage);
    _uas->startCalibration(UAS::CalibrationMag);
}

void SensorsComponentController::calibrateAccel(void)
{
    connect(_uas,&UAS::textMessageReceived,this,&SensorsComponentController::_handleUASTextMessage);
    _uas->startCalibration(UAS::CalibrationAccel);
}

void SensorsComponentController::calibrateLevel(void)
{
    connect(_uas,&UAS::textMessageReceived,this,&SensorsComponentController::_handleUASTextMessage);
    _uas->startCalibration(UAS::CalibrationLevel);
}

void SensorsComponentController::_handleUASTextMessage(int uasId, int compId, int severity, QString text)
{
    Q_UNUSED(uasId)
    Q_UNUSED(compId)
    Q_UNUSED(severity)

    emit handleUASTextMessage(text);
}

void SensorsComponentController::_cancelCalibration(void)
{
    _uas->stopCalibration();
}

void SensorsComponentController::_stopCalibration(void)
{
    disconnect(_uas,&UAS::textMessageReceived,this,&SensorsComponentController::_handleUASTextMessage);
    //refreshParam
    //refreshParamsPrefix
}

int SensorsComponentController::getMagCalSides(void)
{
    int sides = 0;
    if(_autopilot->paramExists(PX4AutopilotPlugin::defaultCompId,"CAL_MAG_SIDES")) {
        sides = _autopilot->getParamFact(PX4AutopilotPlugin::defaultCompId,"CAL_MAG_SIDES")->rawValue().toInt();
    }
    else {
        sides = (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1) | (1<<0);
    }
    return sides;
}


