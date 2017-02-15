#include "SetupWidget.h"
#include "ui_SetupWidget.h"

#include <QModelIndex>
#include <QGridLayout>

#include "ComponentController.h"
#include "SetupWizard/FirmwarePage.h"
#include "SetupWizard/MessagePanel.h"
#include "SetupWizard/ParamsPage.h"
#include "QuadApplication.h"
#include "VehicleManager.h"
#include "SetupWizard/SummaryViewPage.h"
#include "SetupWizard/AirframePage.h"
#include "SetupWizard/SensorsGroupPage.h"
#include "SetupWizard/PowerGroupPage.h"
#include "SetupWizard/RadioPage.h"
#include "SetupWizard/FlightModesPage.h"

SetupWidget::SetupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetupWidget)
  , _firmwarePage(NULL)
  , _messagePanel(NULL)
  , _paramsPage(NULL)
  , _airframePage(NULL)
  , _sensorsPage(NULL)
  , _radioPage(NULL)
  , _fltModePage(NULL)
  , _summaryPage(NULL)
  , _powerPage(NULL)
  , _selectedBtn(NULL)
  , _vehicle(NULL)
  , _px4ParameterMetaData(NULL)
{
    ui->setupUi(this);
    this->setStyleSheet("QPushButton {background: #cfe2f3}"
                        "QPushButton:pressed {background: #6699cc}");

    _firmwarePage = new FirmwarePage();
    _messagePanel = new MessagePanel();
    _paramsPage = new ParamsPage(this);
    _summaryPage = new SummaryViewPage(this);

    ui->stackedWidget->addWidget(_summaryPage);
    ui->stackedWidget->addWidget(_firmwarePage);
    ui->stackedWidget->addWidget(_messagePanel);
    ui->stackedWidget->addWidget(_paramsPage);

    connect(ui->pushButton_Airframe,&QPushButton::clicked,this,&SetupWidget::_showPanel);

    connect(ui->pushButton_Radio,&QPushButton::clicked,this,&SetupWidget::_showPanel);
    connect(ui->pushButton_fltModes,&QPushButton::clicked,this,&SetupWidget::_showPanel);
    connect(ui->pushButton_Sensors,&QPushButton::clicked,this,&SetupWidget::_showPanel);
    connect(ui->pushButton_Radio,&QPushButton::clicked,this,&SetupWidget::_showPanel);
    connect(ui->pushButton_Power,&QPushButton::clicked,this,&SetupWidget::_showPanel);
}

SetupWidget::~SetupWidget()
{
    delete ui;
}

/*void CalWidget::addMetaDataToFact(Fact* fact)
{
    _px4ParameterMetaData->addMetaDataToFact(fact);
}
*/

void SetupWidget::_activeVehicleChanged(Vehicle* vehicle)
 {
    qDebug()<<"CalWidget::_activeVehicleChanged";
    _vehicle = vehicle;
    connect(_vehicle->autopilotPlugin(),&PX4AutopilotPlugin::setupCompleteChanged,_summaryPage,&SummaryViewPage::_setupCompleteChanged);
    connect(_vehicle->autopilotPlugin(),&PX4AutopilotPlugin::setupCompleteStatus,_summaryPage,&SummaryViewPage::_setupCompleteStatus);

    connect(_vehicle->autopilotPlugin(),&PX4AutopilotPlugin::showMessage,_messagePanel,&MessagePanel::_showMessage);
    connect(_px4ParameterMetaData,&PX4ParameterMetaData::paramUpdate,_vehicle,&Vehicle::_paramUpdate);

    //connect(_vehicle->autopilotPlugin(),&PX4AutopilotPlugin::showSetupView,this,&CalWidget::_showSetupView);

    _px4ParameterMetaData->loadParamFactMetaDataFile(QString());

    _airframePage = new AirframePage(this);
    _sensorsPage = new SensorsGroupPage(this);
    _powerPage = new PowerGroupPage(this);
    _radioPage = new RadioPage(this);
    _fltModePage = new FlightModesPage(this);

    ui->stackedWidget->addWidget(_airframePage);
    ui->stackedWidget->addWidget(_sensorsPage);
    ui->stackedWidget->addWidget(_powerPage);
    ui->stackedWidget->addWidget(_radioPage);
    ui->stackedWidget->addWidget(_fltModePage);

    ui->pushButton_Airframe->setEnabled(true);
    ui->pushButton_Sensors->setEnabled(true);
    ui->pushButton_fltModes->setEnabled(true);
    ui->pushButton_Power->setEnabled(true);
    ui->pushButton_Radio->setEnabled(true);

    connect(this,&SetupWidget::showMessage,_messagePanel,&MessagePanel::_showMessage);
    //connect(_airframePage,&AirframePage::showMessage,_messagePanel,&MessagePanel::_showMessage);
    //connect(_sensorsPage,&SensorsPage::showMessage,_messagePanel,&MessagePanel::_showMessage);
    //connect(_powerPage,&PowerGroupPage::showMessage,_messagePanel,&MessagePanel::_showMessage);

    connect(_summaryPage,&SummaryViewPage::showPanel,this,&SetupWidget::_showCompPanel);
    _airframePage->initAirframeController();
 }

void SetupWidget::loadParamFactMetaDataFile()
{
    _px4ParameterMetaData = qgcApp()->toolbox()->firmwarePlugin()->loadParamFactMetaDataFile(QString("F:\\baseModule\\PX4ParameterFactMetaData.xml"));
    connect( _px4ParameterMetaData,&PX4ParameterMetaData::factMetaData,this,&SetupWidget::_showParams);

   //PX4ParameterMetaData* metaData = new PX4ParameterMetaData;
    //connect(metaData,&PX4ParameterMetaData::factMetaData,this,&CalWidget::_showParams);

    //metaData->loadParamFactMetaDataFile(QString("F:\\baseModule\\PX4ParameterFactMetaData.xml"));
 /*
  _airframePage->initAirframeController();
  */
}

void SetupWidget::_showParams(QMap<QString, FactMetaData*> mapParameterName2FactMetaData)
{
    _paramsPage->showParams(mapParameterName2FactMetaData);
}

void SetupWidget::_showCompPanel(QString compName)
{
    _showComponentPanel(compName);
}

void SetupWidget::_showPanel()
{
    QPushButton* selectedBtn = qobject_cast<QPushButton*>(sender());
    if(!_selectedBtn) {
        _selectedBtn = selectedBtn;
        _selectedBtn->setStyleSheet("background-color:#6699cc; border-color:green");
    }
    if(_selectedBtn && _selectedBtn != selectedBtn) {
        _selectedBtn->setStyleSheet("background-color: #cfe2f3");
        _selectedBtn = selectedBtn;
        _selectedBtn->setStyleSheet("background-color:#6699cc; border-color:green");
    }

    QString btnName = _selectedBtn->text();
    if(!btnName.isEmpty()) {
        _showComponentPanel(btnName);
    }
}

void SetupWidget::_showComponentPanel(QString name)
{
    if(_vehicle->autopilotPlugin()) {
        bool allowSetupWhileArmed = true;
        QString preRequisiteSetup;
        QString componentName;

        if(name == "Airframe") {
            AirframeComponent* airframe = _vehicle->autopilotPlugin()->airframeComponent();
            allowSetupWhileArmed = airframe->allowSetupWhileArmed();
            preRequisiteSetup = airframe->prerequisiteSetup();
            componentName = airframe->name();
        }
        else if(name == "Sensors") {
            SensorsComponent* sensors = _vehicle->autopilotPlugin()->sensorsComponent();
            allowSetupWhileArmed = sensors->allowSetupWhileArmed();
            preRequisiteSetup = sensors->prerequisiteSetup();
            componentName = sensors->name();
        }
        else if (name == "Power") {
            PowerComponent* power = _vehicle->autopilotPlugin()->powerComponent();
            allowSetupWhileArmed = power->allowSetupWhileArmed();
            preRequisiteSetup = power->prerequisiteSetup();
            componentName = power->name();
        }
        else if (name == "Radio") {
            RadioComponent* radio = _vehicle->autopilotPlugin()->radioComponent();
            allowSetupWhileArmed = radio->allowSetupWhileArmed();
            preRequisiteSetup = radio->prerequisiteSetup();
            componentName = radio->name();
        }
        else if (name == "Flight Modes") {
            FlightModesComponent* fltMode = _vehicle->autopilotPlugin()->flightmodesComponent();
            allowSetupWhileArmed = fltMode->allowSetupWhileArmed();
            //preRequisiteSetup = fltMode->prerequisiteSetup();
            //for test
            preRequisiteSetup = "";
            componentName = fltMode->name();
        }

        bool showMessagePanel = true;
        QString message;
        if(_vehicle->armed() && !allowSetupWhileArmed) {
            message = _armedText;
       }
        else {
            if(!preRequisiteSetup.isEmpty()) {
                message = QString("%1 must be completed prior to %2 setup.").arg(preRequisiteSetup)
                        .arg(componentName);
            }
            else {
                showMessagePanel = false;
            }
        }
        if(showMessagePanel) {
            emit showMessage(message);
            ui->stackedWidget->setCurrentWidget(_messagePanel);
        }
        else {
            if (name == "Airframe") {
                ui->stackedWidget->setCurrentWidget(_airframePage);
            } else if(name == "Sensors") {
                _sensorsPage->initSensorsController();
                ui->stackedWidget->setCurrentWidget(_sensorsPage);
            } else if(name == "Power") {
                _powerPage->initPowerController();
                ui->stackedWidget->setCurrentWidget(_powerPage);
            } else if(name == "Radio") {
                _radioPage->initRadioController();
                ui->stackedWidget->setCurrentWidget(_radioPage);
            }
            else if(name == "Flight Modes") {
                _fltModePage->initFltModeController();
                ui->stackedWidget->setCurrentWidget(_fltModePage);
            }
        }
    }
}

void SetupWidget::on_pushButton_Summary_clicked()
{
    ui->stackedWidget->setCurrentWidget(_summaryPage);
}

void SetupWidget::on_pushButton_Firmware_clicked()
{
   ui->stackedWidget->setCurrentWidget(_firmwarePage);
}

void SetupWidget::on_pushButton_Parameters_clicked()
{
    ui->stackedWidget->setCurrentWidget(_paramsPage);
}
