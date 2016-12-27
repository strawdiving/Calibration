#include "OrientationWidget.h"
#include <QDebug>
#include <QVBoxLayout>

struct Name2Resorce {
    const char* name;
    bool rotate;
    const char* imageResource;
};

static const struct Name2Resorce name2Resource[] = {
{"Down",              false,      ":/qmlImages/qmlImages/Vehicle1Down.png"},
{"UpsideDown", false,      ":/qmlImages/qmlImages/Vehicle2UpsideDown.png"},
{"Left",                 false,      ":/qmlImages/qmlImages/Vehicle3Left.png"},
{"Right",               false,      ":/qmlImages/qmlImages/Vehicle4Right.png"},
{"NoseDown",     false,      ":/qmlImages/qmlImages/Vehicle5NoseDown.png"},
{"TailDown",        false,      ":/qmlImages/qmlImages/Vehicle6TailDown.png"},

{"Down",              true,      ":/qmlImages/qmlImages/VehicleDownRotate.png"},
{"UpsideDown", true,      ":/qmlImages/qmlImages/VehicleUpsideDownRotate.png"},
{"Left",                 true,      ":/qmlImages/qmlImages/VehicleLeftRotate.png"},
{"Right",               true,      ":/qmlImages/qmlImages/VehicleRightRotate.png"},
{"NoseDown",     true,      ":/qmlImages/qmlImages/VehicleNoseDownRotate.png"},
{"TailDown",        true,      ":/qmlImages/qmlImages/VehicleTailDownRotate.png"},
};

OrientationWidget::OrientationWidget(QString name)
    : _name(name)
{
    _image = new QLabel;
    _image->setFixedSize(200,160);
    _statusText = new QLabel("Incompleted");
    _statusText->setAlignment(Qt::AlignHCenter);
    _statusText->setFixedWidth(_image->width());

    for(int i = 0; i < sizeof(name2Resource)/sizeof(name2Resource[0]); i++ ) {
        if(_name == name2Resource[i].name && name2Resource[i].rotate == false) {
            QPixmap pix(name2Resource[i].imageResource);
            pix = pix.scaled(_image->size());
            _image->setPixmap(pix);
        }
    }

    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addWidget(_image,4);
    vLayout->addWidget(_statusText,1);

    this->setLayout(vLayout);
    this->setStyleSheet("border:3px solid red;color:red");
}

OrientationWidget::~OrientationWidget()
{

}

void OrientationWidget::_statusChanged(bool inProgress, bool rotate, bool done)
{
    qDebug()<<"name,inProgress,rotate,done"<<_name<< inProgress<<rotate<<done;
    if(inProgress) {
        this->setStyleSheet("border:3px solid yellow");
        for(int i = 0; i < sizeof(name2Resource)/sizeof(name2Resource[0]); i++ ) {
            if(_name == name2Resource[i].name && rotate == name2Resource[i].rotate) {
                QPixmap pix(name2Resource[i].imageResource);
                pix = pix.scaled(_image->size());
                _image->setPixmap(pix);
                if(rotate) {
                    _statusText->setText("Rotate");
                } else {
                    _statusText->setText("Hold still");
                }
                break;
            }
        }
    }  else {
        if(done) {
            this->setStyleSheet("border:3px solid #27c927;color:green");
            for(int i = 0; i < sizeof(name2Resource)/sizeof(name2Resource[0]); i++ ) {
                if(_name == name2Resource[i].name && rotate == name2Resource[i].rotate) {
                    QPixmap pix(name2Resource[i].imageResource);
                    pix = pix.scaled(_image->size());
                    _image->setPixmap(pix);
                    _statusText->setText("Completed");
                    break;
                }
            }
        } else {
            this->setStyleSheet("border:3px solid red; color:red");
            _statusText->setText("Incompleted");
        }
    }
}

void OrientationWidget::_calVisibleChanged(void)
{

}
