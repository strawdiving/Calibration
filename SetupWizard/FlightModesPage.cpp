#include "FlightModesPage.h"
#include <QVBoxLayout>

FlightModesPage::FlightModesPage(QWidget *parent)
    : QWidget(parent),
      _manualMode(NULL),
      _assistMode(NULL),
      _returnMode(NULL),
      _autoMode(NULL),
      _posCtlMode(NULL),
     _altCtlMode(NULL),
     _acroMode(NULL),
     _offboardMode(NULL)
{

}

FlightModesPage::~FlightModesPage()
{

}

void FlightModesPage::initFltModeController()
{

    _descriptions <<  QString("Stabilized/Main: The pilot has full control of the aircraft, only attitude is stabilized. The Main mode switch must always be assigned to a channel in order to fly")
                   <<QString("Assist: If Position Control is placed on a seperate channel from the Main mode channel, an additional Assist mode is added to the Main switch.In order for the Attitude "
                              "Control/Position Control switch to be active, the Main switch must be in Assist mode.")
                  <<QString("Return: The vehicle returns to the home position, loiters and then lands. ")
                  <<QString("Auto: If Loiter is placed on a seperate channel from the Main mode channel, an additional 'Auto' mode is added to the Main switch. "
                            "In order for the Mission/Loiter switch to be active, the Main switch must be in Auto mode.")
                  << QString("Position Control: Roll and Pitch sticks control sideways and forward speed. Throttle stick controls climb / sink rade. ")
                  << QString("Altitude Control: Same as Stablized mode except that Throttle controls climb/sink rate. Centered Throttle holds altitude steady. ")
                  << QString("Acro: The angular rates are controlled, but not the attitude. ")
                  << QString("Offboard: All flight control aspects are controlled by an offboard system.");

    _fltModeController = new FlightModesComponentController();
    _channelListModel = _fltModeController->getChannelListModel();

    if(!_channelListModel.isEmpty()) {
            _manualMode = new FlightModeWidget("Stabilized/Main",_descriptions.at(0), _fltModeController->getModeChannel("RC_MAP_MODE_SW"),_channelListModel);
            _assistMode = new FlightModeWidget("Assist",_descriptions.at(1),_fltModeController->getModeChannel("RC_MAP_MODE_SW"),_channelListModel);
            _returnMode = new FlightModeWidget("Return",_descriptions.at(2),_fltModeController->getModeChannel("RC_MAP_RETURN_SW"),_channelListModel);
            _autoMode = new FlightModeWidget("Auto",_descriptions.at(3),_fltModeController->getModeChannel("RC_MAP_MODE_SW"),_channelListModel);
            _posCtlMode = new FlightModeWidget("Position Control",_descriptions.at(4),_fltModeController->getModeChannel("RC_MAP_POSCTL_SW"),_channelListModel);
            _altCtlMode = new FlightModeWidget("Altitude Control",_descriptions.at(5),_fltModeController->getModeChannel("RC_MAP_ALTCTL_SW"),_channelListModel);
            _acroMode = new FlightModeWidget("Acro",_descriptions.at(6),_fltModeController->getModeChannel("RC_MAP_ACRO_SW"),_channelListModel);
            _offboardMode = new FlightModeWidget("Offboard",_descriptions.at(7),_fltModeController->getModeChannel("RC_MAP_OFFB_SW"),_channelListModel);
        }

       QVBoxLayout* layout = new QVBoxLayout;
       layout->setSpacing(10);
       layout->addWidget(_manualMode);
       layout->addWidget(_assistMode);
       layout->addWidget(_returnMode);
       layout->addWidget(_autoMode);
       layout->addWidget(_posCtlMode);
       layout->addWidget(_altCtlMode);
       layout->addWidget(_acroMode);
       layout->addWidget(_offboardMode);

       this->setLayout(layout);

       connect(_fltModeController,&FlightModesComponentController::offboardModeSelectedChanged, _offboardMode,&FlightModeWidget::_modeSelectedChanged);
       connect(_fltModeController,&FlightModesComponentController::autoModeSelectedChanged,_autoMode,&FlightModeWidget::_modeSelectedChanged);
       connect(_fltModeController,&FlightModesComponentController::returnModeSelectedChanged,_returnMode,&FlightModeWidget::_modeSelectedChanged);
       connect(_fltModeController,&FlightModesComponentController::posCtlModeSelectedChanged,_posCtlMode,&FlightModeWidget::_modeSelectedChanged);
       connect(_fltModeController,&FlightModesComponentController::altCtlModeSelectedChanged,_altCtlMode,&FlightModeWidget::_modeSelectedChanged);
       connect(_fltModeController,&FlightModesComponentController::assistModeSelectedChanged,_assistMode,&FlightModeWidget::_modeSelectedChanged);
       connect(_fltModeController,&FlightModesComponentController::acroModeSelectedChanged,_acroMode,&FlightModeWidget::_modeSelectedChanged);
       connect(_fltModeController,&FlightModesComponentController::manualModeSelectedChanged,_manualMode,&FlightModeWidget::_modeSelectedChanged);

       connect(_offboardMode,&FlightModeWidget::channelIndexChanged,_fltModeController,&FlightModesComponentController::_setOffboardChannelIndex);
       connect(_returnMode,&FlightModeWidget::channelIndexChanged,_fltModeController,&FlightModesComponentController::_setReturnChannelIndex);
       connect(_posCtlMode,&FlightModeWidget::channelIndexChanged,_fltModeController,&FlightModesComponentController::_setPosCtlChannelIndex);
       connect(_acroMode,&FlightModeWidget::channelIndexChanged,_fltModeController,&FlightModesComponentController::_setAcroChannelIndex);
       connect(_manualMode,&FlightModeWidget::channelIndexChanged,_fltModeController,&FlightModesComponentController::_setManualChannelIndex);
    }


