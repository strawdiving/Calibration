/********************************************************************************
** Form generated from reading UI file 'RadioPage.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RADIOPAGE_H
#define UI_RADIOPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RadioPage
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSlider *slider_Roll;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QSlider *slider_Pitch;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSlider *slider_Yaw;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QSlider *slider_Throttle;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *radioButton_Mode1;
    QRadioButton *radioButton_Mode2;
    QLabel *image;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_Calibrate;
    QPushButton *pushButton_Cancel;
    QSpacerItem *horizontalSpacer;
    QLabel *label_statusText;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    QFrame *line;
    QLabel *label_8;
    QPushButton *pushButton_copyTrims;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QWidget *widget_Trims;

    void setupUi(QWidget *RadioPage)
    {
        if (RadioPage->objectName().isEmpty())
            RadioPage->setObjectName(QStringLiteral("RadioPage"));
        RadioPage->resize(598, 536);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RadioPage->sizePolicy().hasHeightForWidth());
        RadioPage->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(11);
        RadioPage->setFont(font);
        RadioPage->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        gridLayout_2 = new QGridLayout(RadioPage);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label = new QLabel(RadioPage);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 30));
        label->setMaximumSize(QSize(16777215, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        verticalLayout_5->addWidget(label);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(30);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(RadioPage);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(60, 25));
        label_2->setMaximumSize(QSize(60, 25));

        horizontalLayout->addWidget(label_2);

        slider_Roll = new QSlider(RadioPage);
        slider_Roll->setObjectName(QStringLiteral("slider_Roll"));
        slider_Roll->setMinimum(1000);
        slider_Roll->setMaximum(2000);
        slider_Roll->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(slider_Roll);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(RadioPage);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(60, 25));
        label_3->setMaximumSize(QSize(60, 25));

        horizontalLayout_2->addWidget(label_3);

        slider_Pitch = new QSlider(RadioPage);
        slider_Pitch->setObjectName(QStringLiteral("slider_Pitch"));
        slider_Pitch->setMinimum(1000);
        slider_Pitch->setMaximum(2000);
        slider_Pitch->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(slider_Pitch);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(RadioPage);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(60, 25));
        label_4->setMaximumSize(QSize(60, 25));

        horizontalLayout_3->addWidget(label_4);

        slider_Yaw = new QSlider(RadioPage);
        slider_Yaw->setObjectName(QStringLiteral("slider_Yaw"));
        slider_Yaw->setMinimum(1000);
        slider_Yaw->setMaximum(2000);
        slider_Yaw->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(slider_Yaw);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(RadioPage);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(60, 25));
        label_5->setMaximumSize(QSize(60, 25));

        horizontalLayout_4->addWidget(label_5);

        slider_Throttle = new QSlider(RadioPage);
        slider_Throttle->setObjectName(QStringLiteral("slider_Throttle"));
        slider_Throttle->setMinimum(1000);
        slider_Throttle->setMaximum(2000);
        slider_Throttle->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(slider_Throttle);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout_7->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        radioButton_Mode1 = new QRadioButton(RadioPage);
        radioButton_Mode1->setObjectName(QStringLiteral("radioButton_Mode1"));
        radioButton_Mode1->setChecked(true);

        horizontalLayout_5->addWidget(radioButton_Mode1);

        radioButton_Mode2 = new QRadioButton(RadioPage);
        radioButton_Mode2->setObjectName(QStringLiteral("radioButton_Mode2"));

        horizontalLayout_5->addWidget(radioButton_Mode2);


        verticalLayout_2->addLayout(horizontalLayout_5);

        image = new QLabel(RadioPage);
        image->setObjectName(QStringLiteral("image"));
        image->setMinimumSize(QSize(300, 0));
        image->setMaximumSize(QSize(300, 16777215));
        image->setBaseSize(QSize(0, 0));
        image->setStyleSheet(QStringLiteral("image: url(:/qmlImages/qmlImages/mode1/radioHome.png);"));
        image->setPixmap(QPixmap(QString::fromUtf8(":/qmlImages/qmlImages/mode1/radioHome.png")));
        image->setScaledContents(true);

        verticalLayout_2->addWidget(image);


        horizontalLayout_7->addLayout(verticalLayout_2);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(1, 1);

        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(10);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        pushButton_Calibrate = new QPushButton(RadioPage);
        pushButton_Calibrate->setObjectName(QStringLiteral("pushButton_Calibrate"));
        pushButton_Calibrate->setMinimumSize(QSize(120, 28));
        pushButton_Calibrate->setMaximumSize(QSize(120, 28));

        horizontalLayout_6->addWidget(pushButton_Calibrate);

        pushButton_Cancel = new QPushButton(RadioPage);
        pushButton_Cancel->setObjectName(QStringLiteral("pushButton_Cancel"));
        pushButton_Cancel->setMinimumSize(QSize(120, 28));
        pushButton_Cancel->setMaximumSize(QSize(120, 28));

        horizontalLayout_6->addWidget(pushButton_Cancel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(2, 3);

        verticalLayout_4->addLayout(horizontalLayout_6);

        label_statusText = new QLabel(RadioPage);
        label_statusText->setObjectName(QStringLiteral("label_statusText"));
        label_statusText->setMinimumSize(QSize(0, 60));
        label_statusText->setMaximumSize(QSize(16777215, 60));
        label_statusText->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_statusText->setWordWrap(true);

        verticalLayout_4->addWidget(label_statusText);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setVerticalSpacing(10);
        line = new QFrame(RadioPage);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 0, 0, 1, 2);

        label_8 = new QLabel(RadioPage);
        label_8->setObjectName(QStringLiteral("label_8"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        label_8->setFont(font2);
        label_8->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout->addWidget(label_8, 1, 0, 1, 1);

        pushButton_copyTrims = new QPushButton(RadioPage);
        pushButton_copyTrims->setObjectName(QStringLiteral("pushButton_copyTrims"));

        gridLayout->addWidget(pushButton_copyTrims, 3, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setRowStretch(2, 3);
        gridLayout->setRowStretch(3, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 8);

        verticalLayout_3->addLayout(gridLayout);

        widget_Trims = new QWidget(RadioPage);
        widget_Trims->setObjectName(QStringLiteral("widget_Trims"));

        verticalLayout_3->addWidget(widget_Trims);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 2);

        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_5->addLayout(verticalLayout_4);


        gridLayout_2->addLayout(verticalLayout_5, 0, 0, 1, 1);


        retranslateUi(RadioPage);

        QMetaObject::connectSlotsByName(RadioPage);
    } // setupUi

    void retranslateUi(QWidget *RadioPage)
    {
        RadioPage->setWindowTitle(QApplication::translate("RadioPage", "Form", 0));
        label->setText(QApplication::translate("RadioPage", "\351\201\245\346\216\247\345\231\250\346\240\241\345\207\206", 0));
        label_2->setText(QApplication::translate("RadioPage", "Roll", 0));
        label_3->setText(QApplication::translate("RadioPage", "Pitch", 0));
        label_4->setText(QApplication::translate("RadioPage", "Yaw", 0));
        label_5->setText(QApplication::translate("RadioPage", "Throttle", 0));
        radioButton_Mode1->setText(QApplication::translate("RadioPage", "\346\250\241\345\274\2171", 0));
        radioButton_Mode2->setText(QApplication::translate("RadioPage", "\346\250\241\345\274\2172", 0));
        image->setText(QString());
        pushButton_Calibrate->setText(QApplication::translate("RadioPage", "Calibrate", 0));
        pushButton_Cancel->setText(QApplication::translate("RadioPage", "\345\217\226\346\266\210", 0));
        label_statusText->setText(QString());
        label_8->setText(QApplication::translate("RadioPage", "\345\205\266\344\273\226\350\256\276\347\275\256", 0));
        pushButton_copyTrims->setText(QApplication::translate("RadioPage", "Copy Trims", 0));
    } // retranslateUi

};

namespace Ui {
    class RadioPage: public Ui_RadioPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RADIOPAGE_H
