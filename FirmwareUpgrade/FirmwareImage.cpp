#include "FirmwareImage.h"

#include <QtDebug>
#include <QFileInfo>
#include <QSettings>
#include <QDir>
#include "ParameterLoader.h"

const char* FirmwareImage::_boardIdKey =            "board_id";
const char* FirmwareImage::_paramXmlSizeKey =       "parameter_xml_size";
const char* FirmwareImage::_paramXmlKey =           "parameter_xml";
const char* FirmwareImage::_airframeXmlSizeKey =    "airframe_xml_size";
const char* FirmwareImage::_airframeXmlKey =        "airframe_xml";
const char* FirmwareImage::_imageSizeKey =          "image_size";
const char* FirmwareImage::_imageKey =              "image";
const char* FirmwareImage::_MAVAutopilotKey =       "mav_autopilot";

FirmwareImage::FirmwareImage(QObject *parent) : QObject(parent)
{

}

FirmwareImage::~FirmwareImage()
{
}

/// load the image file
/// @param image Filename Image file to load
/// @param boardId Board to load image file to
bool FirmwareImage::load(const QString &imageFilename, uint32_t boardId)
{
    QFile px4File(imageFilename);
    if(!px4File.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<QString("Could not open firmware file %1, error: %2").arg(imageFilename).arg(px4File.errorString());
        return false;
    }

    QByteArray bytes = px4File.readAll();
    px4File.close();
    QJsonDocument doc = QJsonDocument::fromJson(bytes);//Parses a UTF-8 encoded JSON document and creates a QJsonDocument from it.
    if(doc.isNull())
    {
        qDebug()<<"Supplied file is not a valid JSON file.";
        return false;
    }

    qDebug()<<"Supplied file is a valid JSON file.";
    QJsonObject px4Json = doc.object();

    // Make sure we have the required keys
    QStringList requiredKeys;
    requiredKeys<<_boardIdKey<<_imageSizeKey<<_imageKey;
    for(int i = 0; i<requiredKeys.count();i++)
    {
        if(!px4Json.contains(requiredKeys.at(i)))
        {
            /// TO-DO: validate the type of requiredKeys

            qDebug()<<QString("Incorrectly formatted firmware file. No %1 key").arg(requiredKeys.at(i));
            return false;
        }
    }

    //firmware board id
    uint32_t firmBoardId = (uint32_t)px4Json.value(_boardIdKey).toInt();
    if(firmBoardId!=boardId){
        qDebug()<<QString("Downloaded firmware board id: %1 does't match hardware board"
                              " id: %2 ").arg(firmBoardId).arg(boardId);
        return false;
    }

    //firmware autopilot type
    MAV_AUTOPILOT firmwareType =(MAV_AUTOPILOT)px4Json.value(_MAVAutopilotKey).toInt();
    qDebug()<<QString("MAV_AUTOPILOT = %1").arg( firmwareType);

 // Decompress the parameter xml and save to file
    QByteArray decompressedBytes;
    bool success = _decompressJsonValue(px4Json,               // JSON object
                                        bytes,                 // Raw bytes of JSON document
                                        _paramXmlSizeKey,  // key which holds byte size
                                        _paramXmlKey,      // key which holds compressed bytes
                                        decompressedBytes);    // Returned decompressed bytes
    if (success) {
        QSettings settings;
        QDir parameterDir = QFileInfo(settings.fileName()).dir();
        QString parameterFilename = parameterDir.filePath("ParameterFactMetaData.xml");
        QFile parameterFile(parameterFilename);
        if (parameterFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            qint64 bytesWritten = parameterFile.write(decompressedBytes);
            if (bytesWritten != decompressedBytes.count()) {
                qDebug()<<QString("Write failed for parameter meta data file, error: %1").arg(parameterFile.errorString());
                parameterFile.close();
                parameterFile.remove();
            } else {
                parameterFile.close();
            }
        } else {
            qDebug()<<QString("Unable to open parameter meta data file for writing, error: %1").arg(parameterFile.errorString());
        }

        // Cache this file with the system
        ParameterLoader::cacheMetaDataFile(parameterFilename,  firmwareType);
    }

        // Decompress the airframe xml and save to file
        success = _decompressJsonValue(px4Json, bytes, _airframeXmlSizeKey, _airframeXmlKey,decompressedBytes);
        if(success)
        {
            QFile airframeFile("./AirframeFactMetaData.xml");
            if (airframeFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                qint64 bytesWritten = airframeFile.write(decompressedBytes);
                if(bytesWritten != decompressedBytes.count())
                {
                    qDebug()<<QString("Write failed for parameter meta data file, error: %1").arg(airframeFile.errorString());
                    airframeFile.close();
                    airframeFile.remove();
                }
                else {
                    airframeFile.close();
                }
            }
            else{
                qDebug()<<QString("Unable to open airframe meta datta file for writing, error: %1").arg(airframeFile.errorString());
            }
        }

 // Decompress the image and save to file
         _imageSize = px4Json.value(_imageSizeKey).toInt();
        success = _decompressJsonValue(px4Json, bytes, _imageSizeKey, _imageKey, decompressedBytes);
        if(!success)
        {
            return false;
        }
        // Pad image to 4-byte boundary
        while ((decompressedBytes.count() % 4) != 0) {
            decompressedBytes.append(static_cast<char>(static_cast<unsigned char>(0xFF)));
        }

        // Store decompressed image file in same location as original download file
        QDir imageFileDir = QFileInfo(imageFilename).dir();
        QString decompressFilename = imageFileDir.filePath("PX4FlashUpgrade.bin");

        QFile decompressFile(decompressFilename);
        if(!decompressFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            qDebug()<<QString("Unable to open decompressed file %1 for writing, error: %2").arg(decompressFilename).arg(decompressFile.errorString());
            return false;
        }

        qint64 bytesWritten = decompressFile.write(decompressedBytes);
        if(bytesWritten != decompressedBytes.count())
        {
            qDebug()<<QString("Write failed for decompressed image file, error: %1").arg(decompressFile.errorString());
            return false;
        }

        decompressFile.close();
        _binFilename = decompressFilename;
        return true;
}

/// Decompress a set of bytes stored in a Json document.
/// @param jsonObject  JSON object
/// @param jsonDocBytes Raw bytes of JSON document
/// @param sizeKey key which holds byte size
/// @param bytesKey key which holds compressed bytes
/// @param decompressedBytes Returned decompressed bytes
bool FirmwareImage::_decompressJsonValue(const QJsonObject&	jsonObject,const QByteArray&	jsonDocBytes,
                                    const QString&		sizeKey,
                                    const QString&		bytesKey,
                                    QByteArray&		decompressedBytes)
{
// Validate decompressed size key
if(!jsonObject.contains(sizeKey))
{
    qDebug()<<QString("Firmware file missing %1 key").arg(sizeKey);
}

int decompressedSize = jsonObject.value(sizeKey).toInt();
if(decompressedSize == 0)
{
    qDebug()<<QString("Firmware file has invalid decompressed size for %1").arg(sizeKey);
}

QStringList parts = QString(jsonDocBytes).split(QString("\"%1\": \"").arg(bytesKey));
if(parts.count() == 1)
{
 qDebug()<<QString("Can not find compressed bytes for %1 in firmware file").arg(bytesKey);
 return false;
}

 parts = parts.last().split("\"");
 if(parts.count() == 1)
 {
     qDebug()<<QString("Incorrectly formed compressed bytes section for %1 in Firmware file").arg(bytesKey);
     return false;
 }

// Store decompressed size as first four bytes. This is required by qUncompress routine.
QByteArray raw;
raw.append((unsigned char)((decompressedSize>>24)&0xFF));
raw.append((unsigned char)((decompressedSize>>16)&0xFF));
raw.append((unsigned char)((decompressedSize>>8)&0xFF));
raw.append((unsigned char)((decompressedSize>>0)&0xFF));

QByteArray base64 = parts.first().toUtf8();
raw.append(QByteArray::fromBase64(base64));
decompressedBytes = qUncompress(raw);

if(decompressedBytes.count() == 0)
{
    qDebug()<<QString("Firmware file has 0 length %1").arg(bytesKey);
    return false;
}

if(decompressedBytes.count() != decompressedSize)
{
    qDebug()<<QString("Size for decompressed %1 does not match stored size. Expected(%1) Actual(%2)").arg(decompressedSize).arg(decompressedBytes.count());
    return false;
}

qDebug()<<QString("Succesfully decompressed %1").arg(bytesKey);
return true;
}
