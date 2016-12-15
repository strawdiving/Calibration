#ifndef FIRMWAREIMAGE_H
#define FIRMWAREIMAGE_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <common/mavlink.h>

class FirmwareImage : public QObject
{
    Q_OBJECT
public:
    explicit FirmwareImage(QObject *parent = 0);
    ~FirmwareImage();
    // Loads the specified image file. ,imageFilename Image file to load
    // boardId Board id that we are going to load this image onto
    bool load(const QString& imageFilename, uint32_t boardId);
    uint32_t imageSize() {return _imageSize; }
    QString binFilename() {return _binFilename; }

signals:

public slots:

private:
    bool _decompressJsonValue(const QJsonObject&	jsonObject,
                              const QByteArray&     jsonDocBytes,
                              const QString&		sizeKey,
                              const QString&		bytesKey,
                              QByteArray&			decompressedBytes);

    uint32_t _imageSize;
    QString _binFilename;
    static const char* _boardIdKey;
    static const char* _imageSizeKey;
    static const char* _imageKey;
    static const char* _airframeXmlSizeKey;
    static const char* _airframeXmlKey;
    static const char* _paramXmlSizeKey;
    static const char* _paramXmlKey;
    static const char* _MAVAutopilotKey;
};

#endif // FIRMWAREIMAGE_H
