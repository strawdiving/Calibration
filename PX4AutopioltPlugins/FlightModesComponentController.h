#ifndef FLIGHTMODESCOMPONENTCONTROLLER_H
#define FLIGHTMODESCOMPONENTCONTROLLER_H

#include "ComponentController.h"

class FlightModesComponentController:public ComponentController
{
    Q_OBJECT
public:
    FlightModesComponentController();
    ~FlightModesComponentController();
   QStringList getChannelListModel() {return _channelListModel;}

   int getModeChannel(QString param);

public slots:
    void _rcChannelsChanged(int channelCount,int pwmValues[Vehicle::maxRCChannelsCount]);

    void _setOffboardChannelIndex(int index);
    void _setReturnChannelIndex(int index);
    void _setPosCtlChannelIndex(int index);
    void _setAcroChannelIndex(int index);
    void _setManualChannelIndex(int index);

signals:
    void offboardModeSelectedChanged(bool selected);
    void autoModeSelectedChanged(bool selected);
    void returnModeSelectedChanged(bool selected);
    void posCtlModeSelectedChanged(bool selected);
    void altCtlModeSelectedChanged(bool selected);
    void assistModeSelectedChanged(bool selected);
    void acroModeSelectedChanged(bool selected);
    void manualModeSelectedChanged(bool selected);

private:
    void _init();
    void _recalcModeSelections();

    int _channelCount;
    static const int _maxChannel = 18;
    int _rcMinValues[_maxChannel];
    int _rcMaxValues[_maxChannel];
    bool _rcReversed[_maxChannel];
    float _rcValues[_maxChannel];

    bool _offboardModeSelected;
    bool _autoModeSelected;
    bool _returnModeSelected;
    //bool _loiterModeSelected;
    //bool _missionModeSelected;
    bool _posCtlModeSelected;
    bool _altCtlModeSelected;
    bool _assistModeSelected;
    bool _acroModeSelected;
    bool _manualModeSelected;

    QList<int> _channelList;
    QStringList _channelListModel;
};

#endif // FLIGHTMODESCOMPONENTCONTROLLER_H
