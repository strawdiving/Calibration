#ifndef POWERGROUPPAGE_H
#define POWERGROUPPAGE_H

#include <QWidget>
#include "PX4AutopioltPlugins/PowerComponentController.h"

namespace Ui {
class PowerGroupPage;
}

class SetupWidget;
class TitleLabel;

class PowerGroupPage : public QWidget
{
    Q_OBJECT

public:
    explicit PowerGroupPage(QWidget *parent = 0);
    ~PowerGroupPage();
     void initPowerController();

signals:
     void showMessage(const QString text);

public slots:
    void _receiveBatteryParams(int cells,float full,float empty);

private slots:
    void on_pushButton_calibrateESC_clicked();

    void on_lineEdit_cells_textChanged(const QString &arg1);

    void on_lineEdit_fullPerCell_textChanged(const QString &arg1);

    void on_lineEdit_emptyPerCell_textChanged(const QString &arg1);

private:
    Ui::PowerGroupPage *ui;
    TitleLabel* _title;
    const QString escTex1 = QString("WARNING: Propellers must be removed from vehicle prior"
                              "to performing ESC calibration.");
    const QString escText2 = QString("You must use USB connection for this operation.");

    PowerComponentController* _powerController;
};

#endif // POWERGROUPPAGE_H
