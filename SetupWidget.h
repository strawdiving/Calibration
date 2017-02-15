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
class SensorsGroupPage;
class SummaryViewPage;
class PowerGroupPage;
class RadioPage;
class FlightModesPage;
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
     void showMessage(const QString text);

public slots:
     void _activeVehicleChanged(Vehicle* vehicle);
     void _showParams(QMap<QString, FactMetaData*> mapParameterName2FactMetaData);
     void loadParamFactMetaDataFile();
     void _showPanel();
     void _showCompPanel(QString compName);


private slots:
     void on_pushButton_Summary_clicked();
     void on_pushButton_Firmware_clicked();
    /* void on_pushButton_Airframe_clicked();
     void on_pushButton_Sensors_clicked();
     void on_pushButton_Power_clicked();
     */
     void on_pushButton_Parameters_clicked();

private:
     void _showComponentPanel(QString name);

      Ui::SetupWidget *ui;
      Vehicle* _vehicle;

      AirframePage* _airframePage;
      SensorsGroupPage* _sensorsPage;
      SummaryViewPage* _summaryPage;
      PowerGroupPage* _powerPage;
      RadioPage* _radioPage;
      FlightModesPage* _fltModePage;

      FirmwarePage* _firmwarePage;

    MessagePanel*  _messagePanel;
    ParamsPage* _paramsPage;

    QPushButton* _selectedBtn;

     PX4ParameterMetaData* _px4ParameterMetaData;
     const QString _armedText = "This operation cannot be performed while vehicle is armed.";
};

#endif // SETUPWIDGET_H
