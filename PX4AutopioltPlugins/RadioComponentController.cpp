#include "RadioComponentController.h"
#include <QDebug>
#include <QSettings>

const struct RadioComponentController::calFunctionParam RadioComponentController::_calFunctionParams[RadioComponentController::rcCalMax] = {
{"RC_MAP_ROLL"},
{"RC_MAP_PITCH"},
{"RC_MAP_YAW"},
{"RC_MAP_THROTTLE"},
{"RC_MAP_MODE_SW"},
{"RC_MAP_POSCTL_SW"},
{"RC_MAP_LOITER_SW"},
{"RC_MAP_RETURN_SW"},
};

RadioComponentController::RadioComponentController()
    : _transmitterMode(2),
      _currentStep(-1),
      _chanCount(0)
{
    _setCalValuesFromParams();

    connect(_vehicle,&Vehicle::rcChannelsChanged,this,&RadioComponentController::_rcChannelsChanged);
    _loadSettings();
    _resetCalValues();
}

RadioComponentController::~RadioComponentController()
{
    _storeSettings();
}

void RadioComponentController::_onCalibrateBtnClicked()
{
    if(_currentStep == -1) {
       //start calibration
        _currentStep = 0;
        _resetCalValues();
        _uas->startCalibration(UAS::CalibrationRadio);
        _nextBtnText = "Next";
        _cancelBtnEnabled = true;
        _setupCurrentState();
    }
    else {
        const calState* state = _getCurrentStateEntry(_currentStep);
        (this->*(state->nextFn))();
    }
}

void RadioComponentController::_onCancelBtnClicked()
{
    _stopCalibration();
}

void RadioComponentController::_stopCalibration(void)
{
    _currentStep = -1;
    if(_uas) {
        _uas->stopCalibration();
        _setCalValuesFromParams();
    } else {
        _resetCalValues();
    }
    _statusText = " ";
    _nextBtnText = "Calibrate";
    _nextBtnEnabled = true;
    _cancelBtnEnabled = false;
    _setHelpImage(_imageCenter);

    emit currentStateChanged(_imageFile,_statusText,_nextBtnText);
    emit nextBtnEnableChanged(_nextBtnEnabled);
    emit cancelBtnEnableChanged(_cancelBtnEnabled);
}

void RadioComponentController::_setupCurrentState(void)
{
    //get current calState entry
    const calState* state = _getCurrentStateEntry(_currentStep);
    _statusText = state->instructions;
    _setHelpImage(state->image);

    emit currentStateChanged(_imageFile,_statusText,_nextBtnText);

    emit nextBtnEnableChanged(state->nextFn != NULL);

    _stickDetectChannel = _maxChannel;
    _stickSettleStarted = false;

    qDebug() << "_setupCurrentState: save values";
    for(int i=0;i<_maxChannel;i++) {
        _saveValue[i] = _rawValue[i];
    }
}

void RadioComponentController::_rcChannelsChanged(int channelCount,int pwmValues[maxRCChannelsCount])
{
    qDebug()<<"Radio: _rcChannelsChanged.";
    int maxChannel = std::min(channelCount,_maxChannel);

    for(int channel=0; channel<maxChannel;channel++) {
        int channelValue = pwmValues[channel];

        if(channelValue!= -1) {
            qDebug()<<"raw value: "<<channelValue;
            _rawValue[channel] = channelValue;

            if(_channelInfos[channel].rcFunction != rcCalMax) {
                switch(_channelInfos[channel].rcFunction) {
                case rcCalPitch:
                    emit pitchValueChanged(channelValue);
                    break;
                case rcCalRoll:
                    emit rollValueChanged(channelValue);
                    break;
                case rcCalYaw:
                    emit yawValueChanged(channelValue);
                    break;
                case rcCalThrottle:
                    emit throttleValueChanged(channelValue);
                    break;
                default:
                    break;
                }
            }
        }

        if(_currentStep == -1) {
            if(_chanCount != channelCount) {
                _chanCount = channelCount;
            }
        } else {
            const calState* state = _getCurrentStateEntry(_currentStep);
            if(state->inputFn) {
                (this->*(state->inputFn))(state->rcFunction,channel,channelValue);
            }
        }
    }
}

const RadioComponentController::calState* RadioComponentController::_getCurrentStateEntry(int currentStep)
{
    const char* _msgBeginPX4 =        "Lower the Throttle stick all the way down.\nReset all transmitter trims to center.\n\n"
                                                                   "Click Next to continue";
    const char* _msgThrottleUp =      "Move the Throttle stick all the way up and hold it there...";
    const char* _msgThrottleDown =    "Move the Throttle stick all the way down and leave it there...";
    const char* _msgYawLeft =         "Move the Yaw stick all the way to the left and hold it there...";
    const char* _msgYawRight =        "Move the Yaw stick all the way to the right and hold it there...";
    const char* _msgRollLeft =        "Move the Roll stick all the way to the left and hold it there...";
    const char* _msgRollRight =       "Move the Roll stick all the way to the right and hold it there...";
    const char* _msgPitchDown =       "Move the Pitch stick all the way down and hold it there...";
    const char* _msgPitchUp =         "Move the Pitch stick all the way up and hold it there...";
    const char* _msgPitchCenter =     "Allow the Pitch stick to move back to center...";
    const char* _msgSwitchMinMax =    "Move all the transmitter switches and/or dials back and forth to their extreme positions.";
    const char* _msgComplete =        "All settings have been captured. Click Next to write the new parameters to your board.";

    static const calState _calStates[] = {
        {rcCalMax,       _msgBeginPX4,       _imageHome,              &RadioComponentController::_inputStickDetect,       NULL},
        {rcCalThrottle, _msgThrottleUp,        _imageThrottleUp,      &RadioComponentController::_inputStickDetect,        NULL},
        {rcCalThrottle, _msgThrottleDown,   _imageThrottleDown, &RadioComponentController::_inputStickMin,        NULL},
        {rcCalYaw,       _msgYawRight,          _imageYawRight,        &RadioComponentController::_inputStickDetect,        NULL},
        {rcCalYaw,       _msgYawLeft,            _imageYawLeft,           &RadioComponentController::_inputStickMin,        NULL},
        {rcCalRoll,       _msgRollRight,          _imageRollRight,         &RadioComponentController::_inputStickDetect,        NULL},
        {rcCalRoll,       _msgRollLeft,             _imageRollLeft,           &RadioComponentController::_inputStickMin,        NULL},
        {rcCalPitch,     _msgPitchUp,            _imagePitchUp,          &RadioComponentController::_inputStickDetect,       NULL},
        {rcCalPitch,     _msgPitchDown,       _imagePitchDown,     &RadioComponentController::_inputStickMin,       NULL},
        {rcCalPitch,     _msgPitchCenter,     _imageHome,               &RadioComponentController::_inputStickCenter,      NULL},
        {rcCalMax,      _msgSwitchMinMax, _imageSwitchMinMax, &RadioComponentController::_inputSwitchMinMax,     NULL},
        {rcCalMax,      _msgComplete,         _imageThrottleDown,   &RadioComponentController::_inputStickCenter,     NULL}
    };

    if(_currentStep < 0 || _currentStep >= (int)(sizeof(_calStates)/sizeof(_calStates[0]))) {
        qDebug()<<"bad step: "<<currentStep;
        currentStep = 0;
    }
    const calState* state = &_calStates[currentStep];
    return state;
}

void RadioComponentController::_inputStickDetect(enum rcCalFunctions calFunction,int channel,int chanValue)
{
    //check whether this channel is used in mapping, we can't use it
    if(_channelInfos[channel].rcFunction != rcCalMax) {
        return;
    }
    //no enough stick movement detected on this channel
    if(_stickDetectChannel == _maxChannel) {
        //stick movement is large enough (>300) that this channel can be considered mapping to some rcFunction

        if(abs(_saveValue[channel] - chanValue) > _rcMoveDelta) {
            qDebug()<<"_inputStickDetect starting settle wait function : channel : value" <<calFunction<<channel<<chanValue;
            _stickDetectChannel = channel;
            _stickDetectValue = chanValue;
        }
    } else if(_stickDetectChannel == channel) {
       // We are waiting for the selected channel to settle out to max

        if(_stickSettleComplete(chanValue)) {            
            qDebug()<<"_inputStickDetect stick settle is complete";
            channelInfo* info = &_channelInfos[channel];

            _rcFunctionChannelMapping[calFunction] = channel;

            //set up channel info (rcFunction, rcMax,rcMin,reversed)
            info->rcFunction = calFunction;

            // Stick detection is complete. Stick should be at max position.
            if(_saveValue[channel] > chanValue) {
                info->reversed = true;
                info->rcMin = chanValue;
            } else {
                info->reversed = false;
                info->rcMax = chanValue;
            }
        }
    }
    // signalAttitudeChanges();
    _currentStep++;
    _setupCurrentState();
}

bool RadioComponentController::_stickSettleComplete(int chanValue)
{
     //waiting for the stick to move to a max position
    if(abs(_stickDetectValue - chanValue) > _rcSettleDelta) {
        // movement is too large (>20) to be considered stopped at a position
         qDebug() <<"_stickSettleComplete : stick is still moving. Difference between _stickDetectValue and value is larger than"<<_stickDetectValue
                 <<chanValue<<_rcSettleDelta;
         _stickSettleStarted = false;
    } else {
        // Stick is still positioned within the specified small range
        if(!_stickSettleStarted) {
            // Start waiting for the stick to stay settled for 500 ms
            qDebug() << "_stickSettleComplete starting settle timer, _stickDetectValue:value" << _stickDetectValue << chanValue;
            _stickSettleStarted = true;
            _stickSettleStartTime.start();
        }
        else { // We have already started waiting
            if(_stickSettleStartTime.elapsed() > 500) {
                // Stick has stayed positioned in one place long enough(500), detection is complete.
                return true;
            }
        }
    }
    return false;
}

void RadioComponentController::_inputStickMin(enum rcCalFunctions calFunction,int channel,int chanValue)
{    
    // We only care about the channel mapped to the function we are working on
    if(_rcFunctionChannelMapping[calFunction] != channel) {
        return;
    }
    if(_stickDetectChannel == _maxChannel) {
          // Detect stick being pegged to extreme position
        if(_channelInfos[channel].reversed) {
            //stick moving to the opposite extreme position( left / bottom,difference larger than 300)
            if(chanValue > _pwmCenterPoint + _rcMoveDelta) {
                _stickDetectChannel = channel;
                _stickDetectValue = chanValue;
            }
        } else {
            if(chanValue < _pwmCenterPoint - _rcMoveDelta) {
                _stickDetectChannel = channel;
                _stickDetectValue = chanValue;
            }
        }
    } else {
        if(_stickDetectChannel == channel) {
             // Waiting for the selected channel to settle out
            if(_stickSettleComplete(chanValue)) {
            // Stick detection is complete. Stick should be at min position.
                channelInfo* info = &_channelInfos[channel];

                if(info->reversed) {
                    info->rcMax = chanValue;
                } else {
                    info->rcMin = chanValue;
                }
                // Check if this is throttle and set trim accordingly
                if(calFunction == rcCalThrottle) {
                    info->rcTrim = chanValue;
                }
                _currentStep++;
                _setupCurrentState();
            }
        }
    }
}

void RadioComponentController::_inputStickCenter(rcCalFunctions calFunction, int channel, int chanValue)
{

}

void RadioComponentController::_inputSwitchMinMax(rcCalFunctions calFunction, int channel, int chanValue)
{

}


void RadioComponentController::_setCalValuesFromParams()
{
    //First: set all functions mapping to _maxChannel
    for(int i =0;i<rcCalMax;i++) {
        _rcFunctionChannelMapping[i] = _maxChannel;
    }

    /// Caution! param channel is 1_based

    QString min("RC%1_MIN");
    QString max("RC%1_MAX");
    QString trim("RC%1_TRIM");
    QString rev("RC%1_REV");

    for(int i=0;i<_maxChannel;i++) {
        channelInfo* info = &_channelInfos[i];
        info->rcFunction = rcCalMax;

        //get default params, FLOAT ,need change to int.
        Fact* paramFact = getParamFact(PX4AutopilotPlugin::defaultCompId,trim.arg(i+1));
        if(paramFact) {
            info->rcTrim = paramFact->rawValue().toInt();
        }
        paramFact = getParamFact(PX4AutopilotPlugin::defaultCompId,min.arg(i+1));
        if(paramFact) {
            info->rcMin = paramFact->rawValue().toInt();
        }
        paramFact = getParamFact(PX4AutopilotPlugin::defaultCompId,max.arg(i+1));
        if(paramFact) {
            info->rcMax = paramFact->rawValue().toInt();
        }
        paramFact = getParamFact(PX4AutopilotPlugin::defaultCompId,rev.arg(i+1));
        if(paramFact) {
            float reversed = paramFact->rawValue().toFloat();
            info->reversed = (reversed == -1.0f);
        }
    }

    for(int i =0;i<rcCalMax;i++) {
        int paramChannel;
        const char* paramName = _calFunctionParams[i].paramName;
        Fact* paramFact = getParamFact(PX4AutopilotPlugin::defaultCompId,paramName);
        if(paramFact) {
            paramChannel = paramFact->rawValue().toInt();

            //= 0: channel not assigned
            if(paramChannel != 0) {
                _rcFunctionChannelMapping[i] = paramChannel - 1;
                _channelInfos[paramChannel - 1].rcFunction = (enum rcCalFunctions)(i);
            }
        }
    }
    //emit attitudeValuesChanged()
}

void RadioComponentController::_writeRCParams(void)
{
    if(!_uas)  { return; }
    _uas->stopCalibration();

    _validRCParams();

    QString min("RC%1_MIN");
    QString max("RC%1_MAX");
    QString trim("RC%1_TRIM");
    QString rev("RC%1_REV");

    for(int channel = 0;channel < _maxChannel; channel++) {
        channelInfo* info = &_channelInfos[channel];

        // setup min, max, trim, reversed values for each channel
        Fact* paramFact = getParamFact(PX4AutopilotPlugin::defaultCompId,min.arg(channel+1));
        if(paramFact) {
          paramFact->setRawValue((float)info->rcMin);
        }
        paramFact = getParamFact(PX4AutopilotPlugin::defaultCompId,max.arg(channel+1));
        if(paramFact) {
            paramFact->setRawValue((float)info->rcMax);
        }
        paramFact = getParamFact(PX4AutopilotPlugin::defaultCompId,trim.arg(channel+1));
        if(paramFact) {
            paramFact->setRawValue((float)info->rcTrim);
        }
        paramFact = getParamFact(PX4AutopilotPlugin::defaultCompId,rev.arg(channel+1));
        if(paramFact) {
            paramFact->setRawValue(info->reversed);
        }

         // setup channel mapping ,assigned function to channel
        for(int i = 0; i < rcCalMax;i++) {
           int paramChannel;
           if(_rcFunctionChannelMapping[i] == _maxChannel) {
               // 0 , no mapping
               paramChannel = 0;
           } else {
               paramChannel = _rcFunctionChannelMapping[i] + 1;
           }
           const char* paramName = _calFunctionParams[i].paramName;
           if(paramName) {
               Fact* paramFact = getParamFact(PX4AutopilotPlugin::defaultCompId,paramName);
               if(paramFact) {
                   paramFact->setRawValue(paramChannel);
               }
           }
        }

        //setup channel count param
         paramFact = getParamFact(PX4AutopilotPlugin::defaultCompId,"RC_CHAN_CNT");
        if(paramFact) {
            paramFact->setRawValue(_chanCount);
        }

        _stopCalibration();
        _setCalValuesFromParams();
    }
}

void RadioComponentController::_validRCParams(void)
{
    for(int channel = 0;channel<_maxChannel;channel++) {
        channelInfo* info = &_channelInfos[channel];
        if(channel<_chanCount) {
            //Although the channel appears as available we still may not have good min/max/trim values for it. Set to defaults if needed.
            if(info->rcMax >  _pwmValidMax || info->rcMin <_pwmValidMin) {
                info->rcMax = _pwmDefaultMax;
                info->rcMin = _pwmDefaultMin;
                info->rcTrim = info->rcMin +(info->rcMax - info->rcMin) / 2;
            } else {
                switch(info->rcFunction) {
                case rcCalRoll:
                case rcCalPitch:
                case rcCalYaw:
                case rcCalThrottle:
                {
                    // Make sure trim is within min/max
                    if(info->rcTrim<info->rcMin) {
                        info->rcTrim = info->rcMin;
                    }
                    if(info->rcTrim > info->rcMax) {
                        info->rcTrim = info->rcMax;
                    }
                }
                    break;
                default:
                    info->rcTrim =  info->rcMin +(info->rcMax - info->rcMin) / 2;
                    break;
                }
            }
        } else {
            //chan > _chanCount
            qDebug() << "_validateCalibration resetting unavailable channel"<<channel;
            info->rcMin = _pwmDefaultMin;
            info->rcMax = _pwmDefaultMax;
            info->rcTrim = info->rcMin +(info->rcMax - info->rcMin) / 2;
            info->reversed = false;
        }
    }
}

void RadioComponentController::_resetCalValues()
{
    //First: set all functions mapping to _maxChannel
    for(int i =0;i<rcCalMax;i++) {
        _rcFunctionChannelMapping[i] = _maxChannel;
    }

    /// Caution! param channel is 1_based

    for(int i=0;i<_maxChannel;i++) {
        channelInfo* info = &_channelInfos[i];
        info->rcFunction = rcCalMax;

        info->rcTrim = _pwmCenterPoint;
        info->rcMin = _pwmCenterPoint;
        info->rcMax = _pwmCenterPoint;
        info->reversed = false;
        }

    // just consider mode switches ,ModeSwitch~ReturnSwitch
    for(int i =rcCalModeSwitch;i<rcCalMax;i++) {
        int paramChannel;
        const char* paramName = _calFunctionParams[i].paramName;
        Fact* paramFact = getParamFact(PX4AutopilotPlugin::defaultCompId,paramName);
        if(paramFact) {
            paramChannel = paramFact->rawValue().toInt();

            //= 0: channel not assigned
            if(paramChannel != 0) {
                _rcFunctionChannelMapping[i] = paramChannel - 1;
                _channelInfos[paramChannel - 1].rcFunction = (rcCalFunctions)(i);
            }
        }
    }
    //emit attitudeValuesChanged()
}

void RadioComponentController::_transmitterModeChanged(int transmitterMode)
{
    _transmitterMode = transmitterMode;
}

void RadioComponentController::_loadSettings(void)
{
    QSettings settings;
    settings.beginGroup("RadioCalibration");
    settings.setValue("Transmitter Mode",_transmitterMode);
    settings.endGroup();
}

void RadioComponentController::_storeSettings(void)
{
    QSettings settings;
    settings.beginGroup("RadioCalibration");
    _transmitterMode = settings.value("TransmitterMode").toInt();
    settings.endGroup();

    if(_transmitterMode!=1&& _transmitterMode!=2) {
        _transmitterMode = 2;
    }
}

void RadioComponentController::_setHelpImage(const QString imageFile)
{
    QString fileName;
    if(_transmitterMode ==1) {
        fileName = _imageFileMode1Dir;
    }  else if(_transmitterMode == 2) {
        fileName = _imageFileMode2Dir;
    }else {
        Q_ASSERT(false);
    }

    fileName += imageFile;
    qDebug()<<"_setHelpImage: "<<fileName;

    _imageFile = fileName;
}

