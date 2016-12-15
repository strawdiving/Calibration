#include "SetupWidget.h"
#include "ui_SetupWidget.h"

#include "SetupWizard/FirmwarePage.h"
#include "SetupWizard/MessagePanel.h"
#include "SetupWizard/ParamsPage.h"
#include "QuadApplication.h"
#include "VehicleManager.h"

#include "ComponentController.h"
#include <QModelIndex>
#include <QGridLayout>

#include "SetupWizard/AirframePage.h"
#include "SetupWizard/SensorsPage.h"
#include "SetupWizard/SummaryPage.h"
#include "SetupWizard/PowerPage.h"

SetupWidget::SetupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetupWidget)
  , _firmwarePage(NULL)
  , _messagePanel(NULL)
  , _paramsPage(NULL)
  , _airframePage(NULL)
  , _sensorsPage(NULL)
  , _summaryPage(NULL)
  , _powerPage(NULL)
  , _vehicle(NULL)
  , _px4ParameterMetaData(NULL)
{
    ui->setupUi(this);
    _firmwarePage = new FirmwarePage();
    _messagePanel = new MessagePanel();
    _paramsPage = new ParamsPage(this);
    _summaryPage = new SummaryPage(this);

    ui->stackedWidget->addWidget(_summaryPage);
    ui->stackedWidget->addWidget(_firmwarePage);
    ui->stackedWidget->addWidget(_messagePanel);
    ui->stackedWidget->addWidget(_paramsPage);
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
    connect(_vehicle->autopilotPlugin(),&PX4AutopilotPlugin::setupCompleteChanged,_summaryPage,&SummaryPage::_setupCompleteChanged);
    connect(_vehicle->autopilotPlugin(),&PX4AutopilotPlugin::showMessage,_messagePanel,&MessagePanel::_showMessage);
    connect(_px4ParameterMetaData,&PX4ParameterMetaData::paramUpdate,_vehicle,&Vehicle::_paramUpdate);

    //connect(_vehicle->autopilotPlugin(),&PX4AutopilotPlugin::showSetupView,this,&CalWidget::_showSetupView);

    _px4ParameterMetaData->loadParamFactMetaDataFile(QString());

    _airframePage = new AirframePage(this);
    _sensorsPage = new SensorsPage(this);
    _powerPage = new PowerPage(this);

    ui->stackedWidget->addWidget(_airframePage);
    ui->stackedWidget->addWidget(_sensorsPage);
    ui->stackedWidget->addWidget(_powerPage);

    ui->pushButton_Airframe->setEnabled(true);
    ui->pushButton_Sensors->setEnabled(true);
    ui->pushButton_fltModes->setEnabled(true);
    ui->pushButton_Power->setEnabled(true);
    ui->pushButton_Radio->setEnabled(true);

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

void SetupWidget::on_pushButton_Summary_clicked()
{
    ui->stackedWidget->setCurrentWidget(_summaryPage);
}

void SetupWidget::on_pushButton_Firmware_clicked()
{
   ui->stackedWidget->setCurrentWidget(_firmwarePage);
}

void SetupWidget::on_pushButton_Airframe_clicked()
{
    ui->stackedWidget->setCurrentWidget(_airframePage);
}

void SetupWidget::on_pushButton_Sensors_clicked()
{
    ui->stackedWidget->setCurrentWidget(_sensorsPage);
}

void SetupWidget::on_pushButton_Parameters_clicked()
{
    ui->stackedWidget->setCurrentWidget(_paramsPage);
}

void SetupWidget::on_pushButton_Power_clicked()
{
    ui->stackedWidget->setCurrentWidget(_powerPage);
    _powerPage->initPowerController();
}
