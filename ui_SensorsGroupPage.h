/********************************************************************************
** Form generated from reading UI file 'SensorsGroupPage.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSORSGROUPPAGE_H
#define UI_SENSORSGROUPPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SensorsGroupPage
{
public:
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget_Orientations;
    QWidget *page;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QPushButton *pushButton_Compass;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_Gyro;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_Accel;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_Level;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_Cancel;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QProgressBar *progressBar_CalProgress;
    QLabel *label_StatusText;

    void setupUi(QWidget *SensorsGroupPage)
    {
        if (SensorsGroupPage->objectName().isEmpty())
            SensorsGroupPage->setObjectName(QStringLiteral("SensorsGroupPage"));
        SensorsGroupPage->resize(599, 541);
        gridLayout = new QGridLayout(SensorsGroupPage);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setVerticalSpacing(10);
        stackedWidget_Orientations = new QStackedWidget(SensorsGroupPage);
        stackedWidget_Orientations->setObjectName(QStringLiteral("stackedWidget_Orientations"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        stackedWidget_Orientations->addWidget(page);

        gridLayout->addWidget(stackedWidget_Orientations, 4, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(SensorsGroupPage);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(11);
        label_2->setFont(font);

        horizontalLayout->addWidget(label_2);

        pushButton_Compass = new QPushButton(SensorsGroupPage);
        pushButton_Compass->setObjectName(QStringLiteral("pushButton_Compass"));
        pushButton_Compass->setFont(font);

        horizontalLayout->addWidget(pushButton_Compass);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton_Gyro = new QPushButton(SensorsGroupPage);
        pushButton_Gyro->setObjectName(QStringLiteral("pushButton_Gyro"));
        pushButton_Gyro->setFont(font);

        horizontalLayout->addWidget(pushButton_Gyro);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        pushButton_Accel = new QPushButton(SensorsGroupPage);
        pushButton_Accel->setObjectName(QStringLiteral("pushButton_Accel"));
        pushButton_Accel->setFont(font);

        horizontalLayout->addWidget(pushButton_Accel);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        pushButton_Level = new QPushButton(SensorsGroupPage);
        pushButton_Level->setObjectName(QStringLiteral("pushButton_Level"));
        pushButton_Level->setFont(font);

        horizontalLayout->addWidget(pushButton_Level);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_Cancel = new QPushButton(SensorsGroupPage);
        pushButton_Cancel->setObjectName(QStringLiteral("pushButton_Cancel"));
        pushButton_Cancel->setFont(font);

        horizontalLayout->addWidget(pushButton_Cancel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(3, 1);
        horizontalLayout->setStretch(5, 1);
        horizontalLayout->setStretch(7, 1);
        horizontalLayout->setStretch(8, 1);
        horizontalLayout->setStretch(9, 1);
        horizontalLayout->setStretch(10, 1);

        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        label = new QLabel(SensorsGroupPage);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(14);
        label->setFont(font1);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        progressBar_CalProgress = new QProgressBar(SensorsGroupPage);
        progressBar_CalProgress->setObjectName(QStringLiteral("progressBar_CalProgress"));
        progressBar_CalProgress->setFont(font);
        progressBar_CalProgress->setValue(0);

        gridLayout->addWidget(progressBar_CalProgress, 2, 0, 1, 1);

        label_StatusText = new QLabel(SensorsGroupPage);
        label_StatusText->setObjectName(QStringLiteral("label_StatusText"));
        label_StatusText->setFont(font);
        label_StatusText->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_StatusText->setWordWrap(true);

        gridLayout->addWidget(label_StatusText, 3, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);

        retranslateUi(SensorsGroupPage);

        QMetaObject::connectSlotsByName(SensorsGroupPage);
    } // setupUi

    void retranslateUi(QWidget *SensorsGroupPage)
    {
        SensorsGroupPage->setWindowTitle(QApplication::translate("SensorsGroupPage", "Form", 0));
        label_2->setText(QApplication::translate("SensorsGroupPage", "\346\240\241\345\207\206\357\274\232", 0));
        pushButton_Compass->setText(QApplication::translate("SensorsGroupPage", "Compass", 0));
        pushButton_Gyro->setText(QApplication::translate("SensorsGroupPage", "Gyro", 0));
        pushButton_Accel->setText(QApplication::translate("SensorsGroupPage", "Accel", 0));
        pushButton_Level->setText(QApplication::translate("SensorsGroupPage", "Level", 0));
        pushButton_Cancel->setText(QApplication::translate("SensorsGroupPage", "Cancel", 0));
        label->setText(QApplication::translate("SensorsGroupPage", "Sensors Config", 0));
        label_StatusText->setText(QApplication::translate("SensorsGroupPage", "Start the individual calibration steps by clicking one of the buttons above.", 0));
    } // retranslateUi

};

namespace Ui {
    class SensorsGroupPage: public Ui_SensorsGroupPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORSGROUPPAGE_H
