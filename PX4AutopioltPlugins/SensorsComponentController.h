#ifndef SENSORSCOMPONENTCONTROLLER_H
#define SENSORSCOMPONENTCONTROLLER_H

#include <QObject>
#include "ComponentController.h"

class SensorsComponentController  : public ComponentController
{
    Q_OBJECT
public:
    SensorsComponentController();
    ~SensorsComponentController();

    void calibrateGyro(void);
    void calibrateCompass(void);
    void calibrateAccel(void);
    void calibrateLevel(void);
    void cancelCalibration(void);

    int getMagCalSides(void);

signals:  
    void handleUASTextMessage(QString textMessage);

public slots:
    void _cancelCalibration(void);
    void _stopCalibration(void);

private slots:
    void _handleUASTextMessage(int uasId, int compId, int severity, QString text);

private:   





};

#endif // SENSORSCOMPONENTCONTROLLER_H
