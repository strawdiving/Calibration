
#ifndef LINKMANAGER_H
#define LINKMANAGER_H

#include "Toolbox.h"

#include "SerialCommunication.h"
#include <QList>
#include <QTimer>
#include <QDateTime>
#include <mavlink_types.h>

#define TargetSystemID 1
#define DEFAULT_COMPONENT_ID 0
//APM 3 Pixhawk 1

class QuadApplication;

class LinkManager : public ToolBase
{
    Q_OBJECT
public:
    LinkManager(QuadApplication* app);
     ~LinkManager();

    // Override from ToolBase
    virtual void setToolbox(Toolbox* toolbox);

    //update serial config list
    void _updateConfigurationList(void);
    //find available serial config
    SerialConfiguration* _findSerialConfiguration(const QString& portName);
    //add available serial config
    void addSerialConfiguration(SerialConfiguration* config);
    //get serial config list
    const QList<SerialConfiguration*> getSerialConfigurationList();

   /// Creates, connects a link  based on the given configuration instance
   SerialLink *createConnectedLink(SerialConfiguration* config);

   void setLink(SerialLink* link);
   SerialLink* getLink();

   /// Connect/disconnect  the specified link,start/stop the thread
   void disconnectLink(SerialLink *link);
   void linkStatusChanged(SerialLink* link, bool connected);

   quint64 getHeartbeatTime() {return lastHeartbeat;}

   void sendMessage(mavlink_message_t message);//get current link and call sendMessage(SerialLink* link, mavlink_message_t message)
   void sendMessage(SerialLink* link, mavlink_message_t message);//send message via serial link

signals:
   void linkConnected(SerialLink* link);
   void linkDisconnected(SerialLink* link);

   void vehicleHeartbeatInfo(SerialLink* link, int vehicleId, int vehicleMavlinkVersion, int vehicleFirmwareType, int vehicleType);
   void messageReceived(SerialLink*link, mavlink_message_t &message);

   void laserDistChanged(mavlink_laser_distance_t* laser_dist);
   void setpointConfirmChanged(mavlink_offboard_setpoint_confirm_t* confirm);
   void pumpStatusChanged(mavlink_pump_status_t* pump_status);

private slots:
    void _linkConnected(void);
    void _linkDisconnected(void);
    void _receiveBytes(SerialLink* link, QByteArray b);

private:
     SerialLink* _link;
     QList<SerialConfiguration*> _serialConfigurations;//to store known serial configs

     uint32_t  _mavlinkChannelsUsedBitMask;
     quint64 lastHeartbeat;//time when heartbeat received
};

#endif // LINKMANAGER_H
