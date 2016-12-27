/********************************************************************************
** Form generated from reading UI file 'SetupWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUPWIDGET_H
#define UI_SETUPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetupWidget
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_Summary;
    QPushButton *pushButton_Firmware;
    QPushButton *pushButton_Airframe;
    QPushButton *pushButton_Radio;
    QPushButton *pushButton_fltModes;
    QPushButton *pushButton_Sensors;
    QPushButton *pushButton_Power;
    QPushButton *pushButton_Parameters;
    QStackedWidget *stackedWidget;

    void setupUi(QWidget *SetupWidget)
    {
        if (SetupWidget->objectName().isEmpty())
            SetupWidget->setObjectName(QStringLiteral("SetupWidget"));
        SetupWidget->resize(691, 501);
        gridLayout_2 = new QGridLayout(SetupWidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(SetupWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        groupBox->setFont(font);
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_Summary = new QPushButton(groupBox);
        pushButton_Summary->setObjectName(QStringLiteral("pushButton_Summary"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(pushButton_Summary->sizePolicy().hasHeightForWidth());
        pushButton_Summary->setSizePolicy(sizePolicy);
        pushButton_Summary->setBaseSize(QSize(1, 50));
        QPalette palette;
        QBrush brush(QColor(0, 170, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        pushButton_Summary->setPalette(palette);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        pushButton_Summary->setFont(font1);
        pushButton_Summary->setStyleSheet(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/qmlImages/qmlImages/Airframe/AirframeComponentIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Summary->setIcon(icon);
        pushButton_Summary->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_Summary);

        pushButton_Firmware = new QPushButton(groupBox);
        pushButton_Firmware->setObjectName(QStringLiteral("pushButton_Firmware"));
        sizePolicy.setHeightForWidth(pushButton_Firmware->sizePolicy().hasHeightForWidth());
        pushButton_Firmware->setSizePolicy(sizePolicy);
        pushButton_Firmware->setBaseSize(QSize(1, 50));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Button, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
        pushButton_Firmware->setPalette(palette1);
        pushButton_Firmware->setFont(font1);
        pushButton_Firmware->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_Firmware);

        pushButton_Airframe = new QPushButton(groupBox);
        pushButton_Airframe->setObjectName(QStringLiteral("pushButton_Airframe"));
        pushButton_Airframe->setEnabled(false);
        sizePolicy.setHeightForWidth(pushButton_Airframe->sizePolicy().hasHeightForWidth());
        pushButton_Airframe->setSizePolicy(sizePolicy);
        pushButton_Airframe->setBaseSize(QSize(1, 50));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Button, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush);
        pushButton_Airframe->setPalette(palette2);
        pushButton_Airframe->setFont(font1);
        pushButton_Airframe->setIcon(icon);
        pushButton_Airframe->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_Airframe);

        pushButton_Radio = new QPushButton(groupBox);
        pushButton_Radio->setObjectName(QStringLiteral("pushButton_Radio"));
        pushButton_Radio->setEnabled(false);
        sizePolicy.setHeightForWidth(pushButton_Radio->sizePolicy().hasHeightForWidth());
        pushButton_Radio->setSizePolicy(sizePolicy);
        pushButton_Radio->setBaseSize(QSize(1, 50));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Button, brush);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush);
        pushButton_Radio->setPalette(palette3);
        pushButton_Radio->setFont(font1);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/qmlImages/qmlImages/RadioComponentIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Radio->setIcon(icon1);
        pushButton_Radio->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_Radio);

        pushButton_fltModes = new QPushButton(groupBox);
        pushButton_fltModes->setObjectName(QStringLiteral("pushButton_fltModes"));
        pushButton_fltModes->setEnabled(false);
        sizePolicy.setHeightForWidth(pushButton_fltModes->sizePolicy().hasHeightForWidth());
        pushButton_fltModes->setSizePolicy(sizePolicy);
        pushButton_fltModes->setBaseSize(QSize(1, 50));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Button, brush);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush);
        pushButton_fltModes->setPalette(palette4);
        pushButton_fltModes->setFont(font1);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/qmlImages/qmlImages/TuningComponentIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_fltModes->setIcon(icon2);
        pushButton_fltModes->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_fltModes);

        pushButton_Sensors = new QPushButton(groupBox);
        pushButton_Sensors->setObjectName(QStringLiteral("pushButton_Sensors"));
        pushButton_Sensors->setEnabled(false);
        sizePolicy.setHeightForWidth(pushButton_Sensors->sizePolicy().hasHeightForWidth());
        pushButton_Sensors->setSizePolicy(sizePolicy);
        pushButton_Sensors->setBaseSize(QSize(1, 50));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Button, brush);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush);
        pushButton_Sensors->setPalette(palette5);
        pushButton_Sensors->setFont(font1);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/qmlImages/qmlImages/SensorsComponentIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Sensors->setIcon(icon3);
        pushButton_Sensors->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_Sensors);

        pushButton_Power = new QPushButton(groupBox);
        pushButton_Power->setObjectName(QStringLiteral("pushButton_Power"));
        pushButton_Power->setEnabled(false);
        sizePolicy.setHeightForWidth(pushButton_Power->sizePolicy().hasHeightForWidth());
        pushButton_Power->setSizePolicy(sizePolicy);
        pushButton_Power->setBaseSize(QSize(1, 50));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::Button, brush);
        palette6.setBrush(QPalette::Active, QPalette::Base, brush);
        palette6.setBrush(QPalette::Active, QPalette::Window, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Window, brush);
        pushButton_Power->setPalette(palette6);
        pushButton_Power->setFont(font1);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/qmlImages/qmlImages/PowerComponentIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Power->setIcon(icon4);
        pushButton_Power->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_Power);

        pushButton_Parameters = new QPushButton(groupBox);
        pushButton_Parameters->setObjectName(QStringLiteral("pushButton_Parameters"));
        sizePolicy.setHeightForWidth(pushButton_Parameters->sizePolicy().hasHeightForWidth());
        pushButton_Parameters->setSizePolicy(sizePolicy);
        pushButton_Parameters->setBaseSize(QSize(1, 50));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::Button, brush);
        palette7.setBrush(QPalette::Active, QPalette::Base, brush);
        palette7.setBrush(QPalette::Active, QPalette::Window, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Window, brush);
        pushButton_Parameters->setPalette(palette7);
        pushButton_Parameters->setFont(font1);
        pushButton_Parameters->setAutoExclusive(true);

        verticalLayout->addWidget(pushButton_Parameters);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(SetupWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(11);
        stackedWidget->setFont(font2);

        gridLayout->addWidget(stackedWidget, 0, 1, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 5);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(SetupWidget);

        stackedWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(SetupWidget);
    } // setupUi

    void retranslateUi(QWidget *SetupWidget)
    {
        SetupWidget->setWindowTitle(QApplication::translate("SetupWidget", "Form", 0));
        groupBox->setTitle(QApplication::translate("SetupWidget", "Setup", 0));
        pushButton_Summary->setText(QApplication::translate("SetupWidget", "Summary", 0));
        pushButton_Firmware->setText(QApplication::translate("SetupWidget", "Firmware", 0));
        pushButton_Airframe->setText(QApplication::translate("SetupWidget", "Airframe", 0));
        pushButton_Radio->setText(QApplication::translate("SetupWidget", "Radio", 0));
        pushButton_fltModes->setText(QApplication::translate("SetupWidget", "Flight Modes", 0));
        pushButton_Sensors->setText(QApplication::translate("SetupWidget", "Sensors", 0));
        pushButton_Power->setText(QApplication::translate("SetupWidget", "Power", 0));
        pushButton_Parameters->setText(QApplication::translate("SetupWidget", "Parameters", 0));
    } // retranslateUi

};

namespace Ui {
    class SetupWidget: public Ui_SetupWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUPWIDGET_H
