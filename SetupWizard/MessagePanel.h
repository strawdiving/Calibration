#ifndef MESSAGEPANEL_H
#define MESSAGEPANEL_H

#include <QWidget>
#include <QLabel>

class MessagePanel : public QWidget
{
    Q_OBJECT
public:
    explicit MessagePanel(QWidget *parent = 0);
    ~MessagePanel();

signals:

public slots:
    void _showMessage(const QString text);

private:
    QLabel* _messageText;
    const QString _armedVehicleText = "This operation cannot be performed while vehicle is armed";
    const QString _disconnectedVehicleText = "Connect your vehicle to your device and GCS will automatically"
                                             "detect it. Click Firmware on the left to upgrade your vehicle";

};

#endif // MESSAGEPANEL_H
