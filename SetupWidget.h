#ifndef SETUPWIDGET_H
#define SETUPWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QListWidget>
#include <QPushButton>

#include "TitleLabel.h"
#include "FactMetaData.h"
#include "PX4ParameterMetaData.h"

class AirframePage;
class SensorsPage;
class SummaryPage;
class PowerPage;
class Vehicle;
class ComponentController;

class FirmwarePage;
class MessagePanel;
class ParamsPage;

namespace Ui {
class SetupWidget;
}

class SetupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SetupWidget(QWidget *parent = 0);
    ~SetupWidget();
    void addMetaDataToFact(Fact* fact);

signals:
     void showParams(QMap<QString, FactMetaData*> mapParameterName2FactMetaData);

public slots:
     void _activeVehicleChanged(Vehicle* vehicle);
     void _showParams(QMap<QString, FactMetaData*> mapParameterName2FactMetaData);
     void loadParamFactMetaDataFile();
     //void _showSetupView();

private slots:
     void on_pushButton_Summary_clicked();
     void on_pushButton_Firmware_clicked();
     void on_pushButton_Airframe_clicked();
     void on_pushButton_Sensors_clicked();
     void on_pushButton_Parameters_clicked();

     void on_pushButton_Power_clicked();

private:
      Ui::SetupWidget *ui;
      Vehicle* _vehicle;

      AirframePage* _airframePage;
      SensorsPage* _sensorsPage;
      SummaryPage* _summaryPage;
      PowerPage* _powerPage;

      FirmwarePage* _firmwarePage;

    MessagePanel*  _messagePanel;
    ParamsPage* _paramsPage;

     PX4ParameterMetaData* _px4ParameterMetaData;

};

#endif // SETUPWIDGET_H
