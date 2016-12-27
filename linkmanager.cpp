/**
 * @file
 *   @brief Implementation of class LinkManager. This class manages serial configures and links, receive the complete mavlink packet and decode ,emit signals
 *               to MainWindow.
 *   @author QAH <qinanhong@siasun.com>
 *
 */
#include "linkmanager.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>
#include <QtDebug>
//#include <QVariant>

#include "QuadApplication.h"

#include <common/mavlink.h>

Q_DECLARE_METATYPE(mavlink_message_t)

struct Modes2Name {
    uint8_t main_mode;
    uint8_t sub_mode;
    const char* name;
    bool canBeSet;
};

static const struct Modes2Name modes2name[] ={
{ PX4_CUSTOM_MAIN_MODE_MANUAL ,       0 , "Manual" ,                true},
{ PX4_CUSTOM_MAIN_MODE_STABILIZED ,  0 , "Stabilized" ,            true},
{ PX4_CUSTOM_MAIN_MODE_ALTCTL ,          0 , "Altitude Control" ,  true},
{ PX4_CUSTOM_MAIN_MODE_POSCTL ,        0 , "Position Control" , true},
{ PX4_CUSTOM_MAIN_MODE_OFFBOARD ,  0 , "Offboard Control" ,true},
{ PX4_CUSTOM_MAIN_MODE_AUTO ,             PX4_CUSTOM_SUB_MODE_AUTO_LOITER ,     "Loiter" ,                    true},
{ PX4_CUSTOM_MAIN_MODE_AUTO ,             PX4_CUSTOM_SUB_MODE_AUTO_RTL ,           "Return To Land" ,     true},

{ PX4_CUSTOM_MAIN_MODE_AUTO,        PX4_CUSTOM_SUB_MODE_AUTO_MISSION,   "Mission",       true},
{ PX4_CUSTOM_MAIN_MODE_AUTO,        PX4_CUSTOM_SUB_MODE_AUTO_LAND,      "Landing",       false},
{ PX4_CUSTOM_MAIN_MODE_AUTO,        PX4_CUSTOM_SUB_MODE_AUTO_READY,     "Ready",         false},
{ PX4_CUSTOM_MAIN_MODE_AUTO,        PX4_CUSTOM_SUB_MODE_AUTO_TAKEOFF,   "Takeoff",       false},
{ PX4_CUSTOM_MAIN_MODE_AUTO,        PX4_CUSTOM_SUB_MODE_AUTO_RTGS,      "Return, Link Loss",          false},
};


LinkManager::LinkManager(QuadApplication *app)
 :   ToolBase(app),
   _link(NULL)
{
   qRegisterMetaType<mavlink_message_t>("mavlink_message_t");
   }

LinkManager::~LinkManager()
{

}

void LinkManager::setToolbox(Toolbox *toolbox)
{
    ToolBase::setToolbox(toolbox);
}

//config the serial link,start the thread
SerialLink* LinkManager::createConnectedLink(SerialConfiguration* config)
{
     qDebug()<<"createConnectedLink";
     Q_ASSERT(config);
     _link = new SerialLink(dynamic_cast<SerialConfiguration*>(config));
     if( _link)
    {
       setLink( _link);
       _link->_connect();
    }
     return _link;
}

 void LinkManager::setLink(SerialLink* link)
 {
     Q_ASSERT(link);
     for (int i=0; i<32; i++) {
             if (!(_mavlinkChannelsUsedBitMask && 1 << i)) {
                 mavlink_reset_channel_status(i);
                 link->_setMavlinkChannel(i);
                 _mavlinkChannelsUsedBitMask |= i << i;
                 qDebug()<<"mavlinkChannel set!";
                 break;
       }
 }
     connect(link, &SerialLink::bytesReceived, this, &LinkManager::_receiveBytes);
     connect(link, &SerialLink::connected, this, &LinkManager::_linkConnected);
     connect(link, &SerialLink::disconnected, this, &LinkManager::_linkDisconnected);
 }

SerialLink* LinkManager::getLink()
{
    return _link;
}

// Disconnect the specified link
void LinkManager::disconnectLink(SerialLink* link)
{
    Q_ASSERT(link);
    //stop the thread
    if(link->_disconnect())
    {

    //clear the link of  the config
        if(link->_config) {
           link->_config->setLink(NULL);
           emit linkDisconnected(link);
        }
    }
}

 //look through all serial ports,if it is a PX4/APM/3DR,if not existed, create a new Serial configuration,add to list  “_serialConfigurations”
void LinkManager::_updateConfigurationList(void)
{
    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    foreach (QSerialPortInfo portInfo, portList) {

        // PX4 NOT in bootloader mode
        if (portInfo.vendorIdentifier() == 9900 && !portInfo.description().contains("BL")) {
          SerialConfiguration* pSerial = _findSerialConfiguration(portInfo.portName());
           if (!pSerial) {
                pSerial = new SerialConfiguration(QString("Pixhawk on %1").arg(portInfo.portName().trimmed()));
                pSerial->setBaud(115200);
                pSerial->setPortName(portInfo.portName());
                addSerialConfiguration(pSerial);
          }
        }

        //  APM
       else if (portInfo.vendorIdentifier() == 9025 && !portInfo.description().contains("BL")) {
            SerialConfiguration* pSerial = _findSerialConfiguration(portInfo.portName());
            if (!pSerial) {
                pSerial = new SerialConfiguration(QString("APM on %1").arg(portInfo.portName().trimmed()));
                pSerial->setBaud(115200);
                pSerial->setPortName(portInfo.portName());
                addSerialConfiguration(pSerial);
            }
        }

       // FTDI Chip,a 3DR Modem
        else if(portInfo.vendorIdentifier() == 1027) {
            SerialConfiguration* pSerial = _findSerialConfiguration(portInfo.portName());
            if (!pSerial) {
                pSerial = new SerialConfiguration(QString("3DR Radio on %1").arg(portInfo.portName().trimmed()));
                pSerial->setBaud(57600);
                pSerial->setPortName(portInfo.portName());
                addSerialConfiguration(pSerial);
            }
        }
    }
  }

//look through all SerialConfiguration, if portname matches, return that SerialConfiguration pointer
 SerialConfiguration* LinkManager::_findSerialConfiguration(const QString& portName)
 {
QString searchPort = portName.trimmed();
foreach(SerialConfiguration *config,_serialConfigurations)
      {
    Q_ASSERT(config != NULL);
    //convert config to pointer of type SerialConfiguration
        SerialConfiguration* pSerial = dynamic_cast<SerialConfiguration*>(config);
        if(pSerial->portName() == searchPort) {
            return pSerial;
          }
       }
 return NULL;
 }

void LinkManager::addSerialConfiguration(SerialConfiguration *config)
{
    Q_ASSERT(config != NULL);
    //-- If not there already, add it
    int idx = _serialConfigurations.indexOf(config);
    if(idx < 0)
    {
        _serialConfigurations.append(config);
    }
}

const QList<SerialConfiguration*> LinkManager::getSerialConfigurationList()
{
     return _serialConfigurations;
}

void LinkManager:: _linkConnected(void)
{
    SerialLink* link = qobject_cast<SerialLink*>(QObject::sender());
    Q_ASSERT(link);
    emit linkConnected(link);
    linkStatusChanged(link, true);
}

void LinkManager::_linkDisconnected(void)
{
    SerialLink* link = qobject_cast<SerialLink*>(QObject::sender());
    Q_ASSERT(link);
    emit linkDisconnected(link);
    linkStatusChanged(link, false);
}

void LinkManager::linkStatusChanged(SerialLink* link, bool connected)
{
    Q_ASSERT(link);
    if (connected) {
       qDebug() << "_linkStatusChanged" << connected<<",start MAVLink";
         // Send command to start MAVLink
        // XXX hacky but safe,start NSH
       const char init[] = {0x0d, 0x0d, 0x0d};
       link->writeBytes(init, sizeof(init));
       const char* cmd = "sh /etc/init.d/rc.usb\n";
       link->writeBytes(cmd, strlen(cmd));
       link->writeBytes(init, 4);
    }
    else {
      disconnectLink(link);
    }
}

void LinkManager::sendMessage(mavlink_message_t message)
{
    if(_link)
    {
        SerialLink* link = _link;
        sendMessage(link, message);
    }
}

void LinkManager::sendMessage(SerialLink* link, mavlink_message_t message)
{
    static uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    // Rewriting header to ensure correct link ID is set
    static uint8_t messageKeys[256] = MAVLINK_MESSAGE_CRCS;
    mavlink_finalize_message_chan(&message, TargetSystemID, DEFAULT_COMPONENT_ID, link->getMavlinkChannel(), message.len, messageKeys[message.msgid]);
    // Write message into buffer, prepending start sign
    int len = mavlink_msg_to_send_buffer(buffer, &message);

    if (link->isConnected())
    {
    // Send the portion of the buffer now occupied by the message
        link->writeBytes((const char*)buffer, len);
    }
}

/**
 * This method parses all incoming bytes and constructs a MAVLink packet.
 **/
void LinkManager::_receiveBytes(SerialLink* link, QByteArray b)
{
    // Since receiveBytes signals cross threads we can end up with signals in the queue
    // that come through after the link is disconnected. For these we just drop the data since the link is closed.
    mavlink_message_t message;
    mavlink_status_t status;

    int mavlinkChannel = link->getMavlinkChannel();

    static int nonmavlinkCount = 0;
    static bool decodedFirstPacket = false;

    for (int position = 0; position < b.size(); position++) {
        unsigned int decodeState = mavlink_parse_char(mavlinkChannel, (uint8_t)(b[position]), &message, &status);

        if (decodeState == 0 && !decodedFirstPacket)
        {
            nonmavlinkCount++;
            if (nonmavlinkCount > 2000)
            {
               qDebug()<<"2000 bytes with no mavlink message. Are we connected to a mavlink capable device?";
            }
        }
        if (decodeState == 1)
        {
            //qDebug()<< message.sysid<<message.compid<<message.msgid;
            decodedFirstPacket = true;
            if (message.sysid == TargetSystemID)
            {
                switch (message.msgid)
                {
                //#0
                case MAVLINK_MSG_ID_HEARTBEAT:
                {
                    lastHeartbeat =static_cast<quint64>(QDateTime::currentMSecsSinceEpoch());
                    //qDebug()<<"first time: "<<lastHeartbeat;
                    mavlink_heartbeat_t heartbeat;
                    mavlink_msg_heartbeat_decode(&message, &heartbeat);
                    emit vehicleHeartbeatInfo(link,message.sysid,heartbeat.mavlink_version, heartbeat.autopilot, heartbeat.type);

                default:
                    break;
                }
            }
        }
       emit messageReceived(link, message);
    }
}
}
