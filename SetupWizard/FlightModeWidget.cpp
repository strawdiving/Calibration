#include "FlightModeWidget.h"
#include "ui_FlightModeWidget.h"

FlightModeWidget::FlightModeWidget(QString name, QString description, int channelIndex, QStringList&channelListModel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlightModeWidget),
    _channelIndex(channelIndex),
    _selected(false)
{
    ui->setupUi(this);
    ui->label_FltModeName->setText(name);
    ui->label_Description->setText(description);
    ui->comboBox_Channel->addItems(channelListModel);

    if(name == "Auto" || name == "Assist" || name == "AltCtl") {
        ui->comboBox_Channel->setEnabled(false);
    }
}

FlightModeWidget::~FlightModeWidget()
{
    delete ui;
}

void FlightModeWidget::setSelected(bool selected)
{
    _selected = selected;
    if(_selected) {
        ui->label_FltModeName->setStyleSheet("border:3px solid yellow;color:yellow");
    }
}

void FlightModeWidget::on_comboBox_Channel_currentIndexChanged(int index)
{
    _channelIndex = index;
    emit channelIndexChanged(_channelIndex);

}

void FlightModeWidget::_modeSelectedChanged(bool selected)
{
    if(_selected != selected) {
        _selected = selected;
        if(_selected) {
            ui->label_FltModeName->setStyleSheet("border:3px solid yellow;color:yellow");
        }
    }

}
