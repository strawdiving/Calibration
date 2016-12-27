#include "SummaryViewPage.h"
#include "ui_SummaryViewPage.h"
#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>

SummaryViewPage::SummaryViewPage(SetupWidget *calWidget, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SummaryViewPage),
    _calWidget(calWidget)
{
    ui->setupUi(this);

    ui->label_helpText->setText(needSetupText);
    ui->listWidget->setVisible(false);

    _components.insert(":/qmlImages/qmlImages/1QuadRotorX.svg",       "Airframe");
    _components.insert(":/qmlImages/qmlImages/2Radio.png",                                                 "Radio");
    _components.insert(":/qmlImages/qmlImages/4AHRS.png",                                                "Sensors");
    _components.insert(":/qmlImages/qmlImages/3flightmode.png",                                         "Flight Modes");
    _components.insert(":/qmlImages/qmlImages/5battery.png",                                             "Power");
}

void SummaryViewPage::_showPanel(QModelIndex)
{
    //qDebug()<<"listwisget clicked";
    QString compName = ui->listWidget->currentIndex().data().toString();
    if(!compName.isEmpty()) {
        emit showPanel(compName);
    }
}

SummaryViewPage::~SummaryViewPage()
{
    delete ui;
}

void SummaryViewPage::_setupCompleteChanged(bool setupComplete)
{
    if(setupComplete) {
       ui->label_helpText->setStyleSheet("color:black");
       ui->label_helpText->setText(setupCompleteText);
    }
}

void SummaryViewPage::_setupCompleteStatus(QMap<QString, bool> mapSetupCompleteStatus)
{
    _mapSetupCompleteStatus = mapSetupCompleteStatus;

    ui->listWidget->setViewMode(QListView::IconMode);
    ui->listWidget->setFlow(QListView::LeftToRight);
    ui->listWidget->setSpacing(10);
    //ui->listWidget->setStyleSheet("QListWidget::item:selected{color:black; background-color: lightgreen;}");

    foreach (QString iconSource, _components.keys()) {
        QListWidgetItem* item = new QListWidgetItem(QIcon(iconSource),_components.value(iconSource));
        item->setSizeHint(QSize(160,160));
        item->setTextAlignment(Qt::AlignCenter);
        item->setFont(QFont("Microsoft Yahei",12,25));
        if(_mapSetupCompleteStatus.contains(_components.value(iconSource)))
        {
            if(_mapSetupCompleteStatus.value(_components.value(iconSource))) {
                item->setBackgroundColor(Qt::white);
            }
            else {
                item->setBackgroundColor(Qt::lightGray);
               // item->setText(QString(_components.value(iconSource)+tr(":Setup Required")));
                item->setTextColor(Qt::red);
            }
        }
         ui->listWidget->addItem(item);
    }
    ui->listWidget->setIconSize(QSize(130,130));
    ui->listWidget->setVisible(true);
    connect(ui->listWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(_showPanel(QModelIndex)));
}
