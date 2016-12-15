#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <QObject>
#include <QSerialPort>
#include <QtDebug>
#include "qextserialport.h"
#include <stdint.h>
#include <QTime>
#include <QThread>
#include "FirmwareImage.h"
#include "helper.h"

class Bootloader : public QObject
{
    Q_OBJECT
public:
    explicit Bootloader(QObject *parent = 0);
    ~Bootloader();
    bool open(QextSerialPort* port, const QString portName);
    QString errorString() {return _errorString;}

    /// @brief Read a PROTO_SYNC response from the bootloader
    /// @return true: Valid sync response was received
    bool sync(QextSerialPort* port);

    bool erase(QextSerialPort* port);
    bool program(QextSerialPort* port, FirmwareImage* image);
    bool verify(QextSerialPort* port, FirmwareImage* image);
    bool reboot(QextSerialPort* port);

    /// @brief Retrieve a set of board info from the bootloader of PX4 FMU and PX4 Flow boards
    ///     @param bootloaderVersion Returned INFO_BL_REV
    ///     @param boardID Returned INFO_BOARD_ID
    ///     @param flashSize Returned INFO_FLASH_SIZE
    bool getPX4BoardInfo(QextSerialPort* port, uint32_t& bootloaderVersion, uint32_t& boardID, uint32_t& flashSize);

signals:
    void updateProgress(int curr, int total);

public slots:

private:
     bool _sendCommand(QextSerialPort* port, uint8_t cmd, int responseTimeout = _responseTimeout);
     bool _getCommandResponse(QextSerialPort* port, const int responseTimeout = _responseTimeout);

     bool _write(QextSerialPort* port, const uint8_t* data, qint64 maxSize);
     bool _write(QextSerialPort* port, const uint8_t byte);
     bool _read(QextSerialPort* port, uint8_t* data, qint64 maxSize, int readTimeout = _readTimout);

     bool _getPX4BoardInfo(QextSerialPort* port, uint8_t param, uint32_t& value);

     enum {
         // protocol bytes
         PROTO_EOC =             0x20,   ///< end of command

         PROTO_INSYNC =          0x12,   ///< 'in sync' byte sent before status
         // Reply bytes
         PROTO_OK =              0x10,   ///< INSYNC/OK      - 'ok' response
         PROTO_FAILED =          0x11,   ///< INSYNC/FAILED  - 'fail' response
         PROTO_INVALID =         0x13,	///< INSYNC/INVALID - 'invalid' response for bad commands

         // Command bytes
         PROTO_GET_SYNC =        0x21,   ///< NOP for re-establishing sync
         PROTO_GET_DEVICE =      0x22,   ///< get device ID bytes
         PROTO_CHIP_ERASE =      0x23,   ///< erase program area and reset program address
         PROTO_LOAD_ADDRESS =    0x24,	///< set next programming address
         PROTO_PROG_MULTI =      0x27,   ///< write bytes at program address and increment
         PROTO_GET_CRC =         0x29,	///< compute & return a CRC
         PROTO_BOOT =            0x30,   ///< boot the application

         // Command bytes - Rev 2 boootloader only
         PROTO_CHIP_VERIFY	=   0x24, ///< begin verify mode
         PROTO_READ_MULTI	=   0x28, ///< read bytes at programm address and increment

         INFO_BL_REV         =   1,    ///< bootloader protocol revision
         INFO_BOARD_ID		=   2,    ///< board id
         INFO_BOARD_REV		=   3,    ///< board revision
         INFO_FLASH_SIZE		=   4,    ///< size of flashable area

         BL_REV_MIN          =   2,    ///< Minimum supported bootlader protocol
         BL_REV_MAX			=   5,    ///< Maximum supported bootloader protocol

         PROG_MULTI_MAX		=   64,     ///< write size for PROTO_PROG_MULTI, must be multiple of 4
         READ_MULTI_MAX		=   0x28    ///< read size for PROTO_READ_MULTI, must be multiple of 4. Sik Radio max size is 0x28
     };

     uint32_t    _boardID;           ///< board id for currently connected board
     uint32_t    _boardFlashSize;    ///< flash size for currently connected board
     uint32_t    _bootloaderVersion; ///< Bootloader version
     uint32_t    _imageCRC;          ///< CRC for image in currently selected firmware file

     QString _errorString;
     static const int _responseTimeout = 2000;   ///< Msecs to wait for command response bytes
     static const int _readTimout = 2000;        ///< Msecs to wait for read bytes to become available
     static const int _eraseTimeout = 20000;     ///< Msecs to wait for response from erase command
     static const int _rebootTimeout = 10000;    ///< Msecs to wait for reboot command to cause serial port to disconnect
     static const int _verifyTimeout = 5000;     ///< Msecs to wait for response to PROTO_GET_CRC command

};

#endif // BOOTLOADER_H
