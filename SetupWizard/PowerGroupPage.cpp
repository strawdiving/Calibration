#include "PowerGroupPage.h"
#include "ui_PowerGroupPage.h"

PowerGroupPage::PowerGroupPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PowerGroupPage)
{
    ui->setupUi(this);
    ui->label_escText1->setText(escTex1);
    ui->label_escText2->setText(escText2);


}

PowerGroupPage::~PowerGroupPage()
{
    delete ui;
}

void PowerGroupPage::initPowerController()
{
    _powerController = new PowerComponentController;
    connect(_powerController,&PowerComponentController::sendBatteryParams,this,&PowerGroupPage::_receiveBatteryParams);
    _powerController->readBatteryParam();
}

void PowerGroupPage::_receiveBatteryParams(int cells,float full,float empty)
{
    //qDebug()<<"cell full empty";
    ui->lineEdit_cells->setText(QString::number(cells));
    ui->lineEdit_fullPerCell->setText(QString::number(full));
    ui->lineEdit_emptyPerCell->setText(QString::number(empty));
    ui->label_batMax->setText(QString::number(cells*full));
    ui->label_batMin->setText(QString::number(cells*empty));
}

void PowerGroupPage::on_pushButton_calibrateESC_clicked()
{
    _powerController->calibrateESC();
}

void PowerGroupPage::on_lineEdit_cells_textChanged(const QString &arg1)
{
    int cell = arg1.toInt();
    float full = ui->lineEdit_fullPerCell->text().toFloat();
    float empty = ui->lineEdit_emptyPerCell->text().toFloat();
    ui->label_batMax->setText(QString::number(cell*full));
    ui->label_batMin->setText(QString::number(cell*empty));
}

void PowerGroupPage::on_lineEdit_fullPerCell_textChanged(const QString &arg1)
{
    int cell = ui->lineEdit_cells->text().toInt();
    float full = arg1.toFloat();
    float empty = ui->lineEdit_emptyPerCell->text().toFloat();
    ui->label_batMax->setText(QString::number(cell*full));
    ui->label_batMin->setText(QString::number(cell*empty));
}

void PowerGroupPage::on_lineEdit_emptyPerCell_textChanged(const QString &arg1)
{
    int cell = ui->lineEdit_cells->text().toInt();
    float full = ui->lineEdit_fullPerCell->text().toFloat();
    float empty = arg1.toFloat();
    ui->label_batMax->setText(QString::number(cell*full));
    ui->label_batMin->setText(QString::number(cell*empty));
}
