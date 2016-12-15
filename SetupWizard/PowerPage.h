#ifndef POWERPAGE_H
#define POWERPAGE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "PX4AutopioltPlugins/PowerComponentController.h"

class SetupWidget;
class TitleLabel;

class PowerPage : public QWidget
{
    Q_OBJECT
public:
    explicit PowerPage(SetupWidget *calWidget, QWidget *parent = 0);
    ~PowerPage();
    void initPowerController();

signals:

public slots:
    void _receiveBatteryParams(int cells,float full,float empty);

private:

    TitleLabel* _title;
    QLineEdit* _cellText;
    QLineEdit* _fullText;
    QLineEdit* _emptyText;
    QLabel* _maxLabel;
    QLabel* _minLabel;

    QPushButton* _escBtn;

    PowerComponentController* _powerController;

};

#endif // POWERPAGE_H
