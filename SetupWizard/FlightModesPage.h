#ifndef FLIGHTMODESPAGE_H
#define FLIGHTMODESPAGE_H

#include <QWidget>
#include "FlightModeWidget.h"
#include "PX4AutopioltPlugins/FlightModesComponentController.h"

class FlightModesPage : public QWidget
{
    Q_OBJECT
public:
    explicit FlightModesPage(QWidget *parent = 0);
    ~FlightModesPage();

    void initFltModeController();


signals:

public slots:


private:
    QStringList _descriptions;
    FlightModesComponentController* _fltModeController;
    QStringList _channelListModel;

    FlightModeWidget* _manualMode;
    FlightModeWidget* _assistMode;
    FlightModeWidget* _returnMode;
    FlightModeWidget* _autoMode;
    FlightModeWidget* _posCtlMode;
    FlightModeWidget* _altCtlMode;
    FlightModeWidget* _acroMode;
    FlightModeWidget* _offboardMode;
};

#endif // FLIGHTMODESPAGE_H
