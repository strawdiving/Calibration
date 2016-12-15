#ifndef AIRFRAMECOMPONENTCONTROLLER_H
#define AIRFRAMECOMPONENTCONTROLLER_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QTableWidget>
#include "ComponentController.h"

class AirframeComponentController: public ComponentController
{
    Q_OBJECT
public:
    explicit AirframeComponentController(void);
    ~AirframeComponentController();

    typedef struct {
        QString name;
        QString imageResource;
        int autostartId;
    }AirframeType;

    const QString customConfigText = "Your vehivle is using a custom airframe configuration.\n\nIf you want to "
                                     "reset your airframe configuration and select a standard configuration, click \"OK\" button";

protected:

signals:
    void status(QString);


public slots:
    void autostartIdChanged(int autostartId);
    void _waitParamWriteSignal(QVariant value);

private slots:
    void _rebootAfterStackUnwind(void);

private:
    int _autostartId;
    int _waitParamWriteSignalCount;



};

#endif // AIRFRAMECOMPONENTCONTROLLER_H
