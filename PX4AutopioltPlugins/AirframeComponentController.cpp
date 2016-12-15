#include "AirframeComponentController.h"
#include <QFile>
#include <QDebug>
#include <QTimer>
#include "Fact.h"

AirframeComponentController::AirframeComponentController(void) :
    _autostartId(0)
{
    QStringList usedParams;
    usedParams<<"SYS_AUTOSTART"<<"SYS_AUTOCONFIG";
    if(!_allParamsExist(PX4AutopilotPlugin::defaultCompId,usedParams)) {
        qDebug()<<"AirframeController: not all params exist";
        return;
    }

   // Load up member variables
   _autostartId = getParamFact(PX4AutopilotPlugin::defaultCompId,"SYS_AUTOSTART")->rawValue().toInt();
   //qDebug()<<"AirframeComponentController: _autostartId"<<_autostartId;
}

AirframeComponentController::~AirframeComponentController()
{

}

void AirframeComponentController::autostartIdChanged(int autostartId)
{
    bool autostartFound = false;
    if(_autostartId == autostartId) {
       autostartFound = true;
   }
    else {
        _autostartId = autostartId;
    }
    qDebug()<<"_autostartId later"<<_autostartId;
   /*if(_autostartId !=0 && !autostartFound)  {
        // found autostartId, but not match the given ones
        _autostartId = 0;
        emit status(customConfigText);
    }
*/
    // We need to wait for the vehicleUpdated signals to come back before we reboot
    _waitParamWriteSignalCount = 0;
    Fact* sysAutoStartFact = getParamFact(-1,"SYS_AUTOSTART");
    Fact* sysAutoConfigFact = getParamFact(-1,"SYS_AUTOCONFIG");

    connect(sysAutoStartFact,&Fact::vehicleUpdated,this,&AirframeComponentController::_waitParamWriteSignal);
    connect(sysAutoConfigFact,&Fact::vehicleUpdated,this,&AirframeComponentController::_waitParamWriteSignal);

    sysAutoStartFact->forceSetRawValue(_autostartId);
    sysAutoConfigFact->forceSetRawValue(1);
}

void AirframeComponentController::_waitParamWriteSignal(QVariant value)
{
    Q_UNUSED(value);
    qDebug()<<"AirframeComponentController:_waitParamWriteSignal ";

    _waitParamWriteSignalCount++;
    if (_waitParamWriteSignalCount == 2) {
        // Now that both params have made it to the vehicle we can reboot it. All these signals are flying
        // around on the main thread, so we need to allow the stack to unwind back to the event loop before
        // we reboot.
        QTimer::singleShot(800, this, &AirframeComponentController::_rebootAfterStackUnwind);
    }
}

void AirframeComponentController::_rebootAfterStackUnwind(void)
{
    qDebug()<<"AirframeComponentController:_rebootAfterStackUnwind ";
    //_uas->executeCommand(MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN, 1, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    //qgcApp()->processEvents(QEventLoop::ExcludeUserInputEvents);
    for (unsigned i = 0; i < 2000; i++) {
        QThread::usleep(500);
        //qgcApp()->processEvents(QEventLoop::ExcludeUserInputEvents);
    }
    //qgcApp()->toolbox()->linkManager()->disconnectAll();
    //qgcApp()->restoreOverrideCursor();
}
