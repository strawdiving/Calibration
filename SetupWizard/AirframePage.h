#ifndef AIRFRAMEPAGE_H
#define AIRFRAMEPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QTableWidget>
#include "PX4AutopioltPlugins/AirframeComponentController.h"

class SetupWidget;
class TitleLabel;

class AirframePage : public QWidget
{
    Q_OBJECT

public:
    explicit AirframePage(SetupWidget *calWidget, QWidget *parent = 0);
    ~AirframePage();

    typedef struct {
        QString name;
        QString imageResource;
        int autostartId;
    }AirframeType;

    ///For test
    void initAirframeController();

signals:
    void autostartIdChange(int id);

private slots:
    void _airframeTypeChanged(int row, int column);
    void _status(const QString helpText);

private:
    TitleLabel* _title;
    const QString helptext1 = "Please select your airframe type.Click \"Apply and Restart\" to reboot the autopilot.";
    const QString helptext2 = "Click \"Apply\" will save the changes you have made to your airframe configuration."
                              "Your vehicle will also be restarted in order to complete the process.";
    QLabel *_helpText;
    //PX4AirframeLoader *_airframeLoader;
    AirframeComponentController* _airframeController;

     static const AirframeType _airframeTypes[];
};

#endif // AIRFRAMEPAGE_H
