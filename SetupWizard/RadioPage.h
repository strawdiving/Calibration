#ifndef RADIOPAGE_H
#define RADIOPAGE_H

#include <QWidget>
#include "PX4AutopioltPlugins/RadioComponentController.h"

namespace Ui {
class RadioPage;
}

class RadioPage : public QWidget
{
    Q_OBJECT

public:
    explicit RadioPage(QWidget *parent = 0);
    ~RadioPage();
    void initRadioController(void);

signals:
   void transmitterModeChanged(int transmitterMode);
   void calibrateBtnClicked();
   void cancelBtnClicked();

private slots:
    void on_pushButton_Cancel_clicked();
    void on_pushButton_Calibrate_clicked();
    void on_radioButton_Mode1_clicked();
    void on_radioButton_Mode2_clicked();

    void _rollValueChanged(int value);
    void _pitchValueChanged(int value);
    void _yawValueChanged(int value);
    void _throttleValueChanged(int value);


public slots:
    void _currentStateChanged(QString imageSource,QString statusText, QString nextBtnText);
    void _nextBtnEnableChanged(bool enabled);
    void _cancelBtnEnableChanged(bool enabled);

private:
    Ui::RadioPage *ui;
    RadioComponentController* _radioController;
    int _transmitterMode;
};

#endif // RADIOPAGE_H
