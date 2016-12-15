#include "Bootloader.h"

Bootloader::Bootloader(QObject *parent) : QObject(parent)
{

}

Bootloader::~Bootloader()
{

}

 bool Bootloader::open(QextSerialPort *port, const QString portName)
 {
    port->setPortName(portName);
    port->setBaudRate(BAUD115200);
    port->setDataBits(DATA_8);
    port->setParity(PAR_NONE);
    port->setStopBits(STOP_1);
    port->setFlowControl(FLOW_OFF);

    if(!port->open(QIODevice::ReadWrite | QIODevice::Unbuffered))
    {
        _errorString = QString("Open failed on port %1 : %2 ").arg(portName).arg(port->errorString());
        return false;
    }
    return true;
 }

 bool Bootloader::sync(QextSerialPort* port)
 {
     if (_sendCommand(port, PROTO_GET_SYNC)) {
         return true;
     } else {
         _errorString.prepend("Sync: ");
         return false;
     }
 }

 bool Bootloader::_sendCommand(QextSerialPort* port, const uint8_t cmd, int responseTimeout)
 {
     uint8_t buf[2] = { cmd, PROTO_EOC };

     if (!_write(port, buf, 2)) {
         goto Error;
     }
     port->flush();
     if (!_getCommandResponse(port, responseTimeout)) {
         goto Error;
     }

     return true;

 Error:
     _errorString.prepend("Send Command: ");
     return false;
 }

 bool Bootloader::_write(QextSerialPort* port, const uint8_t* data, qint64 maxSize)
 {
     qint64 bytesWritten = port->write((const char*)data, maxSize);
     if (bytesWritten == -1) {
         _errorString = tr("Write failed: %1").arg(port->errorString());
         qWarning() << _errorString;
         return false;
     }
     if (bytesWritten != maxSize) {
         _errorString = tr("Incorrect number of bytes returned for write: actual(%1) expected(%2)").arg(bytesWritten).arg(maxSize);
         qWarning() << _errorString;
         return false;
     }
     return true;
 }

 bool Bootloader::_write(QextSerialPort* port, const uint8_t byte)
 {
     uint8_t buf[1] = { byte };
     return _write(port, buf, 1);
 }

 /// Read a PROTO_SYNC command response from the bootloader
 ///     @param responseTimeout Msecs to wait for response bytes to become available on port
 bool Bootloader::_getCommandResponse(QextSerialPort* port, int responseTimeout)
 {
     uint8_t response[2];

     if (!_read(port, response, 2, responseTimeout)) {
         _errorString.prepend("Get Command Response: ");
         return false;
     }

     // Make sure we get a good sync response
     if (response[0] != PROTO_INSYNC) {
         _errorString = tr("Invalid sync response: 0x%1 0x%2").arg(response[0], 2, 16, QLatin1Char('0')).arg(response[1], 2, 16, QLatin1Char('0'));
         return false;
     } else if (response[1] != PROTO_OK) {
         QString responseCode = tr("Unknown response code");
         if (response[1] == PROTO_FAILED) {
             responseCode = "PROTO_FAILED";
         } else if (response[1] == PROTO_INVALID) {
             responseCode = "PROTO_INVALID";
         }
         _errorString = tr("Command failed: 0x%1 (%2)").arg(response[1], 2, 16, QLatin1Char('0')).arg(responseCode);
         return false;
     }
     return true;
 }

 bool Bootloader::_read(QextSerialPort* port, uint8_t* data, qint64 maxSize, int readTimeout)
 {
     qint64 bytesAlreadyRead = 0;

     while (bytesAlreadyRead < maxSize) {
         QTime timeout;
         timeout.start();
         while (port->bytesAvailable() < 1) {
             if (timeout.elapsed() > readTimeout) {
                 _errorString = tr("Timeout waiting for bytes to be available");
                 return false;
             }
             QThread::usleep(100);
         }

         qint64 bytesRead;
         bytesRead = port->read((char*)&data[bytesAlreadyRead], maxSize);//adress of data[bytesAlreadyRead], low byte or high byte?

         if (bytesRead == -1) {
             _errorString = tr("Read failed: error: %1").arg(port->errorString());
             return false;
         } else {
             Q_ASSERT(bytesRead != 0);
             bytesAlreadyRead += bytesRead;
         }
     }

     return true;
 }

 /// Send a PROTO_GET_DEVICE command to retrieve a value from the PX4 bootloader
 ///     @param param Value to retrieve using INFO_BOARD_* enums
 ///     @param value Returned value
 bool Bootloader::_getPX4BoardInfo(QextSerialPort* port, uint8_t param, uint32_t& value)
 {
     uint8_t buf[3] = { PROTO_GET_DEVICE, param, PROTO_EOC };

     if (!_write(port, buf, sizeof(buf))) {
         goto Error;
     }
     port->flush();
     if (!_read(port, (uint8_t*)&value, sizeof(value))) {
         goto Error;
     }
     if (!_getCommandResponse(port)) {
         goto Error;
     }

     return true;

 Error:
     _errorString.prepend("Get Board Info: ");
     return false;
 }

 bool Bootloader::getPX4BoardInfo(QextSerialPort* port, uint32_t& bootloaderVersion, uint32_t& boardID, uint32_t& flashSize)
 {

     if (!_getPX4BoardInfo(port, INFO_BL_REV, _bootloaderVersion)) {
         goto Error;
     }
     if (_bootloaderVersion < BL_REV_MIN || _bootloaderVersion > BL_REV_MAX) {
         _errorString = tr("Found unsupported bootloader version: %1").arg(_bootloaderVersion);
         goto Error;
     }

     if (!_getPX4BoardInfo(port, INFO_BOARD_ID, _boardID)) {
         goto Error;
     }

     if (!_getPX4BoardInfo(port, INFO_FLASH_SIZE, _boardFlashSize)) {
         qWarning() << _errorString;
         goto Error;
     }

     bootloaderVersion = _bootloaderVersion;
     boardID = _boardID;
     flashSize = _boardFlashSize;

     return true;

 Error:
     _errorString.prepend("Get Board Info: ");
     return false;
 }

 bool Bootloader::erase(QextSerialPort* port)
 {
     if(!_sendCommand(port,PROTO_CHIP_ERASE,_eraseTimeout))
     {
         _errorString = QString("Board erase failed");
         return false;
     }
     return true;
 }

 bool Bootloader::program(QextSerialPort* port, FirmwareImage* image)
 {
      QFile firmwareFile(image->binFilename());
      if(!firmwareFile.open(QIODevice::ReadOnly))
      {
          _errorString = QString("Unable to open firmware file %1 : %2").arg(image->binFilename()).arg(firmwareFile.errorString());
          return false;
      }

      uint32_t imageSize = (uint32_t)firmwareFile.size();
      uint8_t imageBuff[PROG_MULTI_MAX];
      uint32_t bytesSent = 0;
      _imageCRC = 0;

      Q_ASSERT(PROG_MULTI_MAX <= 0x8F);
      while(bytesSent < imageSize)
      {
          int bytesToSend = imageSize - bytesSent;
          if(bytesToSend > (int)sizeof(imageBuff)){
              bytesToSend = (int)sizeof(imageBuff);
          }
          Q_ASSERT((bytesToSend %4)==0);

          int bytesRead = firmwareFile.read((char*)imageBuff, bytesToSend);
          if(bytesRead == -1 || bytesRead != bytesToSend)
          {
             qDebug()<<QString("Firmware file read failed: %1").arg(firmwareFile.errorString());
             // _errorString = QString("Firmware file read failed: %1").arg(firmwareFile.errorString());
              return false;
          }

         Q_ASSERT(bytesToSend <= 0x8F);

          bool failed = true;
          if(_write(port,PROTO_PROG_MULTI)){
              if(_write(port, (uint8_t)bytesToSend)){
                  if(_write(port,imageBuff,bytesToSend)){
                      if(_write(port,PROTO_EOC)){
                          port->flush();
                          if(_getCommandResponse(port)){
                              failed = false;
                          }
                      }
                  }
              }
          }
           if(failed){
              qDebug()<<tr("Flash failed: %1 at address 0x%2").arg(_errorString).arg(bytesSent, 8, 16, QLatin1Char('0'));
               //_errorString = tr("Flash failed: %1 at address 0x%2").arg(_errorString).arg(bytesSent, 8, 16, QLatin1Char('0'));
              return false;
          }
          bytesSent += bytesToSend;
          // Calculate the CRC now so we can test it after the board is flashed.
          _imageCRC = Helper::crc32((uint8_t *)imageBuff, bytesToSend, _imageCRC);

          emit updateProgress(bytesSent, imageSize);
      }
      firmwareFile.close();

      // We calculate the CRC using the entire flash size, filling the remainder with 0xFF.
      while (bytesSent < _boardFlashSize) {
          const uint8_t fill = 0xFF;
          _imageCRC = Helper::crc32(&fill, 1, _imageCRC);
          bytesSent++;
      }
      return true;
 }

 bool Bootloader::verify(QextSerialPort* port, FirmwareImage* image)
 {
     Q_UNUSED(image)
     bool ret;

     uint8_t buff[2] = {PROTO_GET_CRC, PROTO_EOC};
     quint32 flashCRC;

     bool failed = true;
     if(_write(port,buff,2)){
         port->flush();
         if(_read(port,(uint8_t*)&flashCRC,sizeof(flashCRC),_verifyTimeout)){
             if(_getCommandResponse(port)) {
                 failed = false;
             }
         }
     }
     if(failed) {
         ret = false;
     }

     if(_imageCRC != flashCRC) {
         _errorString = QString("CRC mismatch : board(0x%1) file(0x%2)").arg(flashCRC, 4, 16, QLatin1Char('0')).arg(_imageCRC, 4, 16, QLatin1Char('0'));
         ret =  false;
     }
     ret = true;

     reboot(port);
     return ret;
 }

 bool Bootloader::reboot(QextSerialPort* port)
 {
     return _write(port, PROTO_BOOT) && _write(port, PROTO_EOC);
 }
