#include "SensorsPage.h"
#include "TitleLabel.h"
#include <QHBoxLayout>
#include<QVBoxLayout>
#include <QListWidgetItem>
#include <QDebug>

SensorsPage::SensorsPage(SetupWidget *calWidget, QWidget *parent)
    :QWidget(parent)
{
    Q_UNUSED(calWidget)
    _title = new TitleLabel(tr("Sensors Config"));
    _calLabel = new QLabel("Calibrate:");

    _compassCalButton = new QPushButton("Compass");
    _gyroCalButton = new QPushButton("Gyroscope");
    _accelCalButton = new QPushButton("Accelerometer");
    _levalCalButton = new QPushButton("Level Horizon");
    _cancelButton = new QPushButton("Cancel");

    _progressBar = new QProgressBar;
    _progressBar->setValue(0);

    _statusText = new QLabel(statusTextDefault);
    _statusText->setAlignment(Qt::AlignTop);
    _statusText->setFixedHeight(50);
    _statusText->setWordWrap(true);
    _statusText->setFont(QFont("Microsoft Yahei",11,25));

    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->setSpacing(6);
    btnLayout->addWidget(_calLabel);
    btnLayout->addWidget(_compassCalButton);
    btnLayout->addWidget(_gyroCalButton);
    btnLayout->addWidget(_accelCalButton);
    btnLayout->addWidget(_levalCalButton);
    btnLayout->addWidget(_cancelButton);

    _orientationList = new QListWidget;
    _orientationList->setIconSize(QSize(180,180));
    _orientationList->setViewMode(QListView::IconMode);
    _orientationList->setFlow(QListView::TopToBottom);

    QMap<QString,QString> iconSources;
    iconSources.insert(QString(":/qmlImages/qmlImages/VehicleDown.png"),QString("Down"));
    iconSources.insert(QString(":/qmlImages/qmlImages/VehicleUpsideDown.png"),QString("UpsideDown"));
    iconSources.insert(QString(":/qmlImages/qmlImages/VehicleNoseDown.png"),QString("NoseDown"));
    iconSources.insert(QString(":/qmlImages/qmlImages/VehicleTailDown.png"),QString("TailDown"));
    iconSources.insert(QString(":/qmlImages/qmlImages/VehicleLeft.png"),QString("Left"));
    iconSources.insert(QString(":/qmlImages/qmlImages/VehicleRight.png"),QString("Right"));

    foreach (QString iconSource, iconSources.keys()) {
        QListWidgetItem* item = new QListWidgetItem(QIcon(iconSource),iconSources.value(iconSource));
         _orientationList->addItem(item);
    }

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(_title);
    layout->addLayout(btnLayout);
    layout->addWidget(_progressBar);
    layout->addWidget(_statusText);
    layout->addWidget(_orientationList);
    layout->setSpacing(10);

    this->setLayout(layout);
}

SensorsPage::~SensorsPage()
{

}

