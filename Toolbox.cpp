#include "Toolbox.h"
#include "linkmanager.h"
#include "VehicleManager.h"
#include "UASMessageHandler.h"

Toolbox::Toolbox(QuadApplication *app)
    :_linkMgr(NULL)
    , _vehicleMgr(NULL)
    , _uasMessageHandler(NULL)
    ,_firmwarePlugin(NULL)
{
    _linkMgr = new LinkManager(app);
    _vehicleMgr = new VehicleManager(app);
    _uasMessageHandler = new UASMessageHandler(app);
    _firmwarePlugin = new PX4FirmwarePlugin(app);

    _linkMgr->setToolbox(this);
    _vehicleMgr->setToolbox(this);
    _uasMessageHandler->setToolbox(this);
    _firmwarePlugin->setToolbox(this);

}

Toolbox::~Toolbox()
{
    delete _linkMgr;
    delete _vehicleMgr;
    delete _uasMessageHandler;
    delete _firmwarePlugin;
}

ToolBase::ToolBase(QuadApplication* app)
    :QObject((QObject*) app)
    , _app(app)
    , _toolbox(NULL)
{

}

void ToolBase::setToolbox(Toolbox* toolbox)
{
    _toolbox = toolbox;
}
