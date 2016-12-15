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
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        pushButton_Summary->setFont(font);

        verticalLayout->addWidget(pushButton_Summary);

        pushButton_Firmware = new QPushButton(groupBox);
        pushButton_Firmware->setObjectName(QStringLiteral("pushButton_Firmware"));
        sizePolicy.setHeightForWidth(pushButton_Firmware->sizePolicy().hasHeightForWidth());
        pushButton_Firmware->setSizePolicy(sizePolicy);
        pushButton_Firmware->setBaseSize(QSize(1, 50));
        pushButton_Firmware->setFont(font);

        verticalLayout->addWidget(pushButton_Firmware);

        pushButton_Airframe = new QPushButton(groupBox);
        pushButton_Airframe->setObjectName(QStringLiteral("pushButton_Airframe"));
        pushButton_Airframe->setEnabled(false);
        sizePolicy.setHeightForWidth(pushButton_Airframe->sizePolicy().hasHeightForWidth());
        pushButton_Airframe->setSizePolicy(sizePolicy);
        pushButton_Airframe->setBaseSize(QSize(1, 50));
        pushButton_Airframe->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/qmlImages/qmlImages/Airframe/AirframeComponentIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Airframe->setIcon(icon);

        verticalLayout->addWidget(pushButton_Airframe);

        pushButton_Radio = new QPushButton(groupBox);
        pushButton_Radio->setObjectName(QStringLiteral("pushButton_Radio"));
        pushButton_Radio->setEnabled(false);
        sizePolicy.setHeightForWidth(pushButton_Radio->sizePolicy().hasHeightForWidth());
        pushButton_Radio->setSizePolicy(sizePolicy);
        pushButton_Radio->setBaseSize(QSize(1, 50));
        pushButton_Radio->setFont(font);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/qmlImages/qmlImages/RadioComponentIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Radio->setIcon(icon1);

        verticalLayout->addWidget(pushButton_Radio);

        pushButton_fltModes = new QPushButton(groupBox);
        pushButton_fltModes->setObjectName(QStringLiteral("pushButton_fltModes"));
        pushButton_fltModes->setEnabled(false);
        sizePolicy.setHeightForWidth(pushButton_fltModes->sizePolicy().hasHeightForWidth());
        pushButton_fltModes->setSizePolicy(sizePolicy);
        pushButton_fltModes->setBaseSize(QSize(1, 50));
        pushButton_fltModes->setFont(font);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/qmlImages/qmlImages/TuningComponentIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_fltModes->setIcon(icon2);

        verticalLayout->addWidget(pushButton_fltModes);

        pushButton_Sensors = new QPushButton(groupBox);
        pushButton_Sensors->setObjectName(QStringLiteral("pushButton_Sensors"));
        pushButton_Sensors->setEnabled(false);
        sizePolicy.setHeightForWidth(pushButton_Sensors->sizePolicy().hasHeightForWidth());
        pushButton_Sensors->setSizePolicy(sizePolicy);
        pushButton_Sensors->setBaseSize(QSize(1, 50));
        pushButton_Sensors->setFont(font);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/qmlImages/qmlImages/SensorsComponentIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Sensors->setIcon(icon3);

        verticalLayout->addWidget(pushButton_Sensors);

        pushButton_Power = new QPushButton(groupBox);
        pushButton_Power->setObjectName(QStringLiteral("pushButton_Power"));
        pushButton_Power->setEnabled(false);
        sizePolicy.setHeightForWidth(pushButton_Power->sizePolicy().hasHeightForWidth());
        pushButton_Power->setSizePolicy(sizePolicy);
        pushButton_Power->setBaseSize(QSize(1, 50));
        pushButton_Power->setFont(font);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/qmlImages/qmlImages/PowerComponentIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Power->setIcon(icon4);

        verticalLayout->addWidget(pushButton_Power);

        pushButton_Parameters = new QPushButton(groupBox);
        pushButton_Parameters->setObjectName(QStringLiteral("pushButton_Parameters"));
        sizePolicy.setHeightForWidth(pushButton_Parameters->sizePolicy().hasHeightForWidth());
        pushButton_Parameters->setSizePolicy(sizePolicy);
        pushButton_Parameters->setBaseSize(QSize(1, 50));
        pushButton_Parameters->setFont(font);

        verticalLayout->addWidget(pushButton_Parameters);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(SetupWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(11);
        stackedWidget->setFont(font1);

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
