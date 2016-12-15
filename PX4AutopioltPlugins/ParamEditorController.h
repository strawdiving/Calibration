#ifndef PARAMEDITORCONTROLLER_H
#define PARAMEDITORCONTROLLER_H

#include <QObject>
#include "ComponentController.h"

class ParamEditorController : public ComponentController
{
    Q_OBJECT
public:
    ParamEditorController();
    ~ParamEditorController();
};

#endif // PARAMEDITORCONTROLLER_H
