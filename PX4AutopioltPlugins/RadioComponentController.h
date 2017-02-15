#ifndef RADIOCOMPONENTCONTROLLER_H
#define RADIOCOMPONENTCONTROLLER_H

#include "ComponentController.h"
#include <QTime>

class RadioComponentController: public ComponentController
{
    Q_OBJECT
public:
    RadioComponentController();
    ~RadioComponentController();
    static const int maxRCChannelsCount = 18;

public slots:
    void _rcChannelsChanged(int channelCount,int pwmValues[maxRCChannelsCount]);
    void _transmitterModeChanged(int transmitterMode);
    void _onCalibrateBtnClicked();
    void _onCancelBtnClicked();

signals:
    void currentStateChanged(QString imageSource,QString statusText, QString nextBtnText);
    void nextBtnEnableChanged(bool enabled);
    void cancelBtnEnableChanged(bool enabled);

    void rollValueChanged(int value);
    void pitchValueChanged(int value);
    void yawValueChanged(int value);
    void throttleValueChanged(int value);

private:
    void _setHelpImage(const QString imageFile);
    void _setCalValuesFromParams();
    void _resetCalValues();

    void _stopCalibration(void);

    void _loadSettings(void);
    void _storeSettings(void);

    void _setupCurrentState(void);

    enum rcCalFunctions {
        rcCalRoll,
        rcCalPitch,
        rcCalYaw,
        rcCalThrottle,
        rcCalModeSwitch,
        rcCalPosCtlSwitch,
        rcCalLoiterSwitch,
        rcCalReturnSwitch,
        rcCalMax,
    };

    void _inputStickDetect(enum rcCalFunctions calFunction,int channel,int chanValue);
    void _inputStickMin(enum rcCalFunctions calFunction,int channel,int chanValue);
    void _inputStickCenter(enum rcCalFunctions calFunction,int channel,int chanValue);
    void _inputSwitchMinMax(enum rcCalFunctions calFunction,int channel,int chanValue);

    typedef void (RadioComponentController::*inputFn) (enum rcCalFunctions calFunction,int channel,int chanValue);
    typedef void (RadioComponentController::*nextFn) (void);

    struct calState {
        enum rcCalFunctions rcFunction;
        const char* instructions;
        const char* image;
        inputFn       inputFn;
        nextFn        nextFn;
    };

    const calState* _getCurrentStateEntry(int currentStep);

    void _writeRCParams(void);
    void _validRCParams(void);

    bool _stickSettleComplete(int chanValue);

    struct calFunctionParam {
        const char* paramName;  /// Parameter name for function mapping
    };
    static const struct calFunctionParam _calFunctionParams[rcCalMax]; ///Information associated with each function

    struct channelInfo {
        enum rcCalFunctions rcFunction;
        bool reversed;
        int rcMin;
        int rcMax;
        int rcTrim; ///trim position (pei ping)
    };

    int _rcFunctionChannelMapping[rcCalMax];

    //transmitter mode
    int _transmitterMode;

    const char* _imageFileMode1Dir = ":qmlImages/qmlImages/mode1/";
    const char* _imageFileMode2Dir = ":qmlImages/qmlImages/mode2/";

    const char* _imageHome = "radioHome.png";
    const char* _imageCenter = "radioCenter.png";
    const char* _imageThrottleUp = "radioThrottleUp.png";
    const char* _imageThrottleDown = "radioThrottleDown.png";
    const char* _imageYawLeft = "radioYawLeft.png";
    const char* _imageYawRight = "radioYawRight.png";
    const char* _imageRollLeft = "radioRollLeft.png";
    const char* _imageRollRight = "radioRollRight.png";
    const char* _imagePitchUp = "radioPitchUp.png";
    const char* _imagePitchDown = "radioPitchDown.png";
    const char* _imageSwitchMinMax = "radioSwitchMinMax.png";

    static const int _maxChannel = 18; ///< Maximum number of supported rc channels, PX4 Firmware
    static const int _chanMinimum = 5;  ///< Minimum numner of channels required to run
    static const int _pwmCenterPoint = 1500;

    static const int _pwmValidMin = 1300;      ///< Largest valid minimum PWM Min range value——largest of the PWM min range ?
    static const int _pwmValidMax = 1700;      ///< Smallest valid maximum PWM Max range value——smallest of the PWM max range ?

    //used in _validateCalibration()<——called by writeCalibration()
    static const int _pwmDefaultMin = 1000;    ///< Default value for Min if not set
    static const int _pwmDefaultMax = 2000;    ///< Default value for Max if not set

    struct channelInfo _channelInfos[_maxChannel];
    int _rawValue[_maxChannel];
    int _saveValue[_maxChannel];
    int _chanCount;

    QString _imageFile;
    int _currentStep;
    bool _cancelBtnEnabled;
    bool _nextBtnEnabled;
    QString _nextBtnText;
    QString _statusText;

    int _stickDetectChannel;
    int _stickDetectValue;
    bool _stickSettleStarted;
    QTime _stickSettleStartTime;

    static const int _rcMoveDelta = 300;            ///< Amount of delta past center which is considered stick movement
    static const int _rcSettleDelta = 20;           ///< Amount of delta which is considered no stick movement
};

#endif // RADIOCOMPONENTCONTROLLER_H
