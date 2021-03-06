#include "PowerComponentController.h"
#include "Fact.h"
#include <QDebug>

PowerComponentController::PowerComponentController()
    : _cell(0),
      _full(0.0f),
      _empty(0.0f)
{

}

void PowerComponentController::readBatteryParam(void)
{
    QStringList usedParam;
    usedParam<<"BAT_V_CHARGED"<<"BAT_N_CELLS"<<"BAT_V_EMPTY";
    if(!_allParamsExist(PX4AutopilotPlugin::defaultCompId,usedParam)) {
        qDebug()<<"PowerController: not all params exist";
        return;
    }
    _cell = getParamFact(PX4AutopilotPlugin::defaultCompId,"BAT_N_CELLS")->rawValue().toInt();
    _full = getParamFact(PX4AutopilotPlugin::defaultCompId,"BAT_V_CHARGED")->rawValue().toFloat();
    _empty = getParamFact(PX4AutopilotPlugin::defaultCompId,"BAT_V_EMPTY")->rawValue().toFloat();

    emit sendBatteryParams(_cell,_full,_empty);
}

PowerComponentController::~PowerComponentController()
{

}

void PowerComponentController::calibrateESC()
{
    connect(_uas,&UAS::textMessageReceived,this,&PowerComponentController::_handleTextMessage);
    _uas->startCalibration(UAS::CalibrationESC);
}

void PowerComponentController::_handleTextMessage(int uasid, int componentid, int severity, QString text)
{
    Q_UNUSED(uasid)
    Q_UNUSED(componentid)
    Q_UNUSED(severity)
    qDebug()<<"esc cal: "<<text;
}
