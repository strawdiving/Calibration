#ifndef COMPONENTCONTROLLER_H
#define COMPONENTCONTROLLER_H

#include <QObject>

#include "Fact.h"
#include "PX4AutopioltPlugins/PX4AutopilotPlugin.h"
#include "UAS.h"

class ComponentController : public QObject
{
    Q_OBJECT
public:
    explicit ComponentController(QObject *parent = 0);
    ~ComponentController();

signals:

public slots:

protected:
    Fact* getParamFact(int compId,const QString paramName,bool reportMissing = true);
    bool _allParamsExist(int compId,QStringList params);

private:
    Vehicle* _vehicle;
    PX4AutopilotPlugin *_autopilot;
    UAS* _uas;

    //PX4ParameterMetaData* _px4ParameterMetaData;
};

#endif // COMPONENTCONTROLLER_H
