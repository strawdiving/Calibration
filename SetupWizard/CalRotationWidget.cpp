#include "CalRotationWidget.h"
#include "ui_CalRotationWidget.h"
#include <QDebug>
#include <QMap>

CalRotationWidget::CalRotationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalRotationWidget),
    _downWidget(NULL),
    _upsideDownWidget(NULL),
    _leftWidget(NULL),
    _rightWidget(NULL),
    _noseDownWidget(NULL),
    _tailDownWidget(NULL),
    _currentWidget(NULL)
{
    ui->setupUi(this);
    this->setStyleSheet("font: 14px");

    ui->label_CalHelpText->setWordWrap(true);
    ui->label_CalHelpText->setStyleSheet("color: #0000ff");

    _downWidget = new OrientationWidget("Down");
    _upsideDownWidget = new OrientationWidget("UpsideDown");
    _leftWidget = new OrientationWidget("Left");
    _rightWidget = new OrientationWidget("Right");
    _noseDownWidget = new OrientationWidget("NoseDown");
    _tailDownWidget = new OrientationWidget("TailDown");

     _downWidget->setObjectName("down");
    _upsideDownWidget->setObjectName("up");
    _leftWidget->setObjectName("left");
    _rightWidget->setObjectName("right");
    _noseDownWidget->setObjectName("front");
    _tailDownWidget->setObjectName("back");

    QGridLayout* layout = new QGridLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(_downWidget,0,0,1,1);
    layout->addWidget(_upsideDownWidget,0,1,1,1);
    layout->addWidget(_leftWidget,0,2,1,1);
    layout->addWidget(_rightWidget,1,0,1,1);
    layout->addWidget(_noseDownWidget,1,1,1,1);
    layout->addWidget(_tailDownWidget,1,2,1,1);

    ui->widget_CalOrientations->setLayout(layout);
}

CalRotationWidget::~CalRotationWidget()
{
    delete ui;
    delete _downWidget;
    delete _upsideDownWidget;
    delete _leftWidget;
    delete _rightWidget;
    delete _noseDownWidget;
    delete _tailDownWidget;
}

void CalRotationWidget::_status(QString message)
{
    ui->label_CalHelpText->setText(message);
}

void CalRotationWidget::_calStatusChanged(QString side,bool inProgress,bool rotate,bool done)
{
    //qDebug()<<"name,inProgress,rotate,done"<<side<< inProgress<<rotate<<done;
    if(_currentWidget) {
        disconnect(this,&CalRotationWidget::calStatusChanged,_currentWidget,&OrientationWidget::_statusChanged);
    }

    OrientationWidget* widget =ui->widget_CalOrientations->findChild<OrientationWidget*>(side);
    if(widget) {
        qDebug()<<"find child: "<<widget->name();
        _currentWidget = widget;
        connect(this,&CalRotationWidget::calStatusChanged,_currentWidget,&OrientationWidget::_statusChanged);
        emit calStatusChanged(inProgress,rotate,done);
    }
}

void CalRotationWidget::_calVisibleChanged(QString side)
{

}


