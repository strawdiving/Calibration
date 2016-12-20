#ifndef POWERCOMPONENTCONTROLLER_H
#define POWERCOMPONENTCONTROLLER_H

#include <QObject>
#include "ComponentController.h"

class PowerComponentController: public ComponentController
{
    Q_OBJECT
public:
    PowerComponentController();
    ~PowerComponentController();
    void readBatteryParam(void);
    void calibrateESC();

signals:
    void sendBatteryParams(int cells,float full,float empty);

public slots:


private:
    uint8_t _cell;
    float _full;
    float _empty;
};

#endif // POWERCOMPONENTCONTROLLER_H
