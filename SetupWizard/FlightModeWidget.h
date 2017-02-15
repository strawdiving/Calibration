#ifndef FLIGHTMODEWIDGET_H
#define FLIGHTMODEWIDGET_H

#include <QWidget>


namespace Ui {
class FlightModeWidget;
}

class FlightModeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FlightModeWidget(QString name, QString description, int channelIndex, QStringList& channelListModel,QWidget *parent = 0);
    ~FlightModeWidget();
    void setSelected(bool selected);
    bool getSelected(void) { return _selected;}

signals:
    void channelIndexChanged(int index);

public slots:
    void _modeSelectedChanged(bool selected);

private slots:
    void on_comboBox_Channel_currentIndexChanged(int index);

private:
    Ui::FlightModeWidget *ui;
    int _channelIndex;
    bool _selected;


};

#endif // FLIGHTMODEWIDGET_H
