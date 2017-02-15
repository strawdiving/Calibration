#include "RadioPage.h"
#include "ui_RadioPage.h"

RadioPage::RadioPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RadioPage),
    _radioController(NULL),
    _transmitterMode(2)
{
    ui->setupUi(this);
}

RadioPage::~RadioPage()
{
    delete ui;
}

void RadioPage::initRadioController(void)
{
    _radioController = new RadioComponentController;
    connect(_radioController,&RadioComponentController::currentStateChanged,this,&RadioPage::_currentStateChanged);
    connect(_radioController,&RadioComponentController::nextBtnEnableChanged,this,&RadioPage::_nextBtnEnableChanged);
    connect(_radioController,&RadioComponentController::cancelBtnEnableChanged,this,&RadioPage::_cancelBtnEnableChanged);
    connect(_radioController,&RadioComponentController::rollValueChanged,this,&RadioPage::_rollValueChanged);
    connect(_radioController,&RadioComponentController::pitchValueChanged,this,&RadioPage::_pitchValueChanged);
    connect(_radioController,&RadioComponentController::yawValueChanged,this,&RadioPage::_yawValueChanged);
    connect(_radioController,&RadioComponentController::throttleValueChanged,this,&RadioPage::_throttleValueChanged);
    connect(this,&RadioPage::transmitterModeChanged,_radioController,&RadioComponentController::_transmitterModeChanged);
    connect(this,&RadioPage::cancelBtnClicked ,_radioController,&RadioComponentController::_onCancelBtnClicked);
    connect(this,&RadioPage::calibrateBtnClicked,_radioController,&RadioComponentController::_onCalibrateBtnClicked);

}

void RadioPage::on_pushButton_Cancel_clicked()
{
    emit cancelBtnClicked();

}

void RadioPage::on_pushButton_Calibrate_clicked()
{
    emit calibrateBtnClicked();
}

void RadioPage::on_radioButton_Mode1_clicked()
{
    _transmitterMode = 1;
    emit transmitterModeChanged(_transmitterMode);
}

void RadioPage::on_radioButton_Mode2_clicked()
{
    _transmitterMode = 1;
    emit transmitterModeChanged(_transmitterMode);
}

void RadioPage::_rollValueChanged(int value)
{
    ui->slider_Roll->setValue(value);
}

void RadioPage::_pitchValueChanged(int value)
{
    ui->slider_Pitch->setValue(value);
}

void RadioPage::_yawValueChanged(int value)
{
    ui->slider_Yaw->setValue(value);
}

void RadioPage::_throttleValueChanged(int value)
{
    ui->slider_Throttle->setValue(value);
}

void RadioPage::_currentStateChanged(QString imageSource,QString statusText, QString nextBtnText)
{
    ui->image->setPixmap(QPixmap(imageSource));
    ui->label_statusText->setText(statusText);
    ui->pushButton_Calibrate->setText(nextBtnText);
}

void RadioPage::_nextBtnEnableChanged(bool enabled)
{
    ui->pushButton_Calibrate->setEnabled(enabled);
}

void RadioPage::_cancelBtnEnableChanged(bool enabled)
{
    ui->pushButton_Cancel->setEnabled(enabled);
}
