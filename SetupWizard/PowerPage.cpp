#include "PowerPage.h"
#include <QGridLayout>
#include "TitleLabel.h"
#include <QGroupBox>

PowerPage::PowerPage(SetupWidget *calWidget, QWidget *parent)
    : QWidget(parent),
      _powerController(NULL)
{
    _title = new TitleLabel(tr("Power Config"));

    QLabel* cellLabel = new QLabel("Num of Cells ");
    QLabel* fullLabel = new QLabel("Full Voltage (per cell) ");   
    QLabel* emptyLabel = new QLabel("Empty Voltage (per cell) ");
    QLabel* maxLabel = new QLabel("Battery Max: ");
    QLabel* minLabel = new QLabel("Battery Min: ");
    maxLabel->setAlignment(Qt::AlignHCenter);
    minLabel->setAlignment(Qt::AlignHCenter);

    _cellText = new QLineEdit;
    _fullText = new QLineEdit;
    _emptyText = new QLineEdit;
    _maxLabel = new QLabel;
    _minLabel = new QLabel;

    _cellText->setFixedWidth(100);

    _fullText->setFixedWidth(100);
    _emptyText ->setFixedWidth(100);
    _maxLabel->setFixedWidth(100);
    _minLabel->setFixedWidth(100);

    _cellText->setStyleSheet("color:blue");
    _fullText->setStyleSheet("color:blue");
    _emptyText->setStyleSheet("color:blue");
    _maxLabel->setStyleSheet("color:blue");
    _minLabel->setStyleSheet("color:blue");

   QGridLayout* batLayout = new QGridLayout;
   batLayout->addWidget(cellLabel,0,0,1,1);
   batLayout->addWidget(_cellText,0,1,1,1);
   batLayout->addWidget(fullLabel,1,0,1,1);
   batLayout->addWidget(_fullText,1,1,1,1);
   batLayout->addWidget(emptyLabel,2,0,1,1);
   batLayout->addWidget(_emptyText,2,1,1,1);
   batLayout->addWidget(maxLabel,0,2,1,1);
   batLayout->addWidget(_maxLabel,0,3,1,1);
   batLayout->addWidget(minLabel,1,2,1,1);
   batLayout->addWidget(_minLabel,1,3,1,1);
   batLayout->setColumnStretch(0,0);
   batLayout->setColumnStretch(1,2);
   batLayout->setColumnStretch(3,2);
   QGroupBox* batGroup = new QGroupBox("Battery");
   batGroup->setStyleSheet("font: 25 11pt 'Microsoft Yahei'");
   batGroup->setLayout(batLayout);

   QLabel* escTex1 = new QLabel(QString("WARNING: Propellers must be removed from vehicle prior"
                                        "to performing ESC calibration."));
   escTex1->setStyleSheet("color:red");
   escTex1->setWordWrap(true);
   escTex1->setAlignment(Qt::AlignTop);
   QLabel* escText2 = new QLabel(QString("You must use USB connection for this operation."));
   escText2->setWordWrap(true);
   escTex1->setAlignment(Qt::AlignTop);
   _escBtn = new QPushButton("Calibrate");

   QGridLayout* escLayout = new QGridLayout;
   escLayout->setMargin(10);
   escLayout->setSpacing(10);
   escLayout->addWidget(escTex1,0,0,1,4);
   escLayout->addWidget(escText2,1,0,1,4);
   escLayout->addWidget(_escBtn,2,0,1,1);
   QGroupBox* escGroup = new QGroupBox("ESC Calibration");
   escGroup->setStyleSheet("font: 25 11pt 'Microsoft Yahei'");
   escGroup->setLayout(escLayout);

   QVBoxLayout* layout = new QVBoxLayout;
   layout->addWidget(_title);
   layout->addWidget(batGroup);
   layout->setSpacing(15);
   layout->addWidget(escGroup);
   layout->setStretch(1,4);
   layout->setStretch(2,4);

   this->setLayout(layout);
}

PowerPage::~PowerPage()
{

}

void PowerPage::initPowerController()
{
    _powerController = new PowerComponentController;
    connect(_powerController,&PowerComponentController::sendBatteryParams,this,&PowerPage::_receiveBatteryParams);
    _powerController->readBatteryParam();
}

void PowerPage::_receiveBatteryParams(int cells,float full,float empty)
{
    qDebug()<<"cell full empty";
    _cellText->setText(QString::number(cells));
    _fullText->setText(QString::number(full));
    _emptyText->setText(QString::number(empty));
    _maxLabel->setText(QString::number(cells*full));
    _minLabel->setText(QString::number(cells*empty));

}
