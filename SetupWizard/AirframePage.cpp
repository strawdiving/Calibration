#include "AirframePage.h"
#include <QDebug>
#include <QFile>
#include <QPixmap>
#include <QHeaderView>
#include <QMessageBox>
#include <QVBoxLayout>

#include "TitleLabel.h"

const AirframePage::AirframeType AirframePage::_airframeTypes[] = {
    { "QuadRotor X",        ":/qmlImages/qmlImages/Airframe/QuadRotorX.svg",   4011 },
    { "HexaRotor X",        ":/qmlImages/qmlImages/Airframe/HexaRotorX.svg",   6001},
    { "OctoRotor X",        ":/qmlImages/qmlImages/Airframe/OctoRotorX.svg",   8001},
};

AirframePage::AirframePage(SetupWidget *calWidget, QWidget *parent) :
    QWidget(parent)
  , _airframeController(NULL)
{
    Q_UNUSED(calWidget)
    _title = new TitleLabel(tr("Airframe Selection"));

    QPushButton *applyButton = new QPushButton();
    applyButton->setText(tr("Apply and Restart"));

    _helpText = new QLabel(helptext1);
    _helpText->setAlignment(Qt::AlignTop);
    _helpText->setFixedHeight(80);
    _helpText->setWordWrap(true);
    _helpText->setStyleSheet("font: 25 11pt 'Microsoft Yahei'");

    int count = sizeof(_airframeTypes)/sizeof(_airframeTypes[0]);
    QTableWidget *table = new QTableWidget(1,count);

    table->setFrameShape(QFrame::NoFrame);
    table->setShowGrid(false);
    table->setIconSize(QSize(150,150));
    table->setRowHeight(0,180);
    for(int i = 0;i< count;i++) {
         //table->setColumnWidth(0,300);
    }
    //table->resizeColumnsToContents();

    table->setFocusPolicy(Qt::NoFocus);
    table->verticalHeader()->hide();

    QStringList headers;

    for(int i = 0; i <count ;i++) {
        AirframeType airframe = _airframeTypes[i];

        QString iconName;
         if(QFile::exists(airframe.imageResource)) {
            iconName = QString(airframe.imageResource);
        }
         else {
             qDebug()<<"File not exists";
              iconName = QString(":/qmlImages/qmlImages/Airframe/AirframeUnknown.svg");
         }
         headers<<airframe.name;
         table->setColumnWidth(i,180);
         QTableWidgetItem* newItem = new QTableWidgetItem(QIcon(iconName),airframe.name);
         newItem->setTextAlignment(Qt::AlignCenter);
         table->setItem(0,i,newItem);
    }
    table->setHorizontalHeaderLabels(headers);

    connect(table,&QTableWidget::cellClicked,this,&AirframePage::_airframeTypeChanged);
    //connect(applyButton,&QPushButton::clicked,this,&AirframePage::);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(30);
    layout->setSpacing(20);
    layout->setAlignment(Qt::AlignHCenter);
    layout->addWidget(_title);
    layout->addWidget(_helpText);
    layout->addWidget(table);
    layout->setStretch(1,1);
    layout->setStretch(2,2);

    layout->addWidget(applyButton);

    this->setLayout(layout);
    this->layout()->setSizeConstraint(QLayout::SetMaximumSize);
}

void AirframePage::initAirframeController()
{
    _airframeController = new AirframeComponentController();
    connect(_airframeController,SIGNAL(status(QString)),this,SLOT(_status(QString)));
    connect(this,&AirframePage::autostartIdChange,_airframeController,&AirframeComponentController::autostartIdChanged);
}

void AirframePage::_airframeTypeChanged(int row,int column)
{
    Q_UNUSED(row)
    int autostartId = _airframeTypes[column].autostartId;
    QString airframeType = _airframeTypes[column].name;
    if(!airframeType.isEmpty()) {
        _status(helptext2);
    }
    emit autostartIdChange(autostartId);
}

void AirframePage::_status(const QString helpText)
{
    _helpText->setText(helpText);
    //QMessageBox::warning(this,tr("Warning"),helpText,QMessageBox::Ok |QMessageBox::Cancel);
}

AirframePage::~AirframePage()
{

}
