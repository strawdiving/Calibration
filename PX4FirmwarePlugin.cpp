#include "PX4FirmwarePlugin.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>
#include "PX4ParameterMetaData.h"
#include "Toolbox.h"


PX4FirmwarePlugin::PX4FirmwarePlugin(QuadApplication *app)
     :ToolBase(app)
{

}

void PX4FirmwarePlugin::setToolbox(Toolbox* toolbox)
{
    ToolBase::setToolbox(toolbox);

}

PX4FirmwarePlugin::~PX4FirmwarePlugin()
{

}

PX4ParameterMetaData* PX4FirmwarePlugin::loadParamFactMetaDataFile(QString &metaDataFile)
{
    Q_UNUSED(metaDataFile)
   _px4metaData = new PX4ParameterMetaData;

   qDebug()<<"PX4FirmwarePlugin::loadParamFactMetaDataFile";
    //_px4metaData->loadParamFactMetaDataFile(metaDataFile);
    return _px4metaData;
}

void PX4FirmwarePlugin::addMetaDataToFact(Fact* fact)
{
    if(_px4metaData)
    {
       // qDebug()<<"PX4FirmwarePlugin::addMetaDataToFact,px4metaData exists";
        _px4metaData->addMetaDataToFact(fact);
    }
}

void PX4FirmwarePlugin::getParameterMetaDataVersionInfo (const QString& metaDataFile, int& majorVersion, int& minorVersion)
{
    QFile xmlFile(metaDataFile);

    if (!xmlFile.exists()) {
        qWarning() << "Internal error: metaDataFile mission" << metaDataFile;
        return;
    }

    if (!xmlFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Internal error: Unable to open parameter file:" << metaDataFile << xmlFile.errorString();
        return;
    }

    QXmlStreamReader xml(xmlFile.readAll());
    xmlFile.close();
    if (xml.hasError()) {
        qWarning() << "Badly formed XML" << xml.errorString();
        return;
    }
    majorVersion = -1;
    minorVersion = -1;

    while (!xml.atEnd() && (majorVersion == -1 || minorVersion == -1)) {
        if (xml.isStartElement()) {
            QString elementName = xml.name().toString();

            if (elementName == "parameter_version_major") {
                bool convertOk;
                QString strVersion = xml.readElementText();
                majorVersion = strVersion.toInt(&convertOk);
                if (!convertOk) {
                    qWarning() << "Badly formed XML";
                    return;
                }
            } else if (elementName == "parameter_version_minor") {
                bool convertOk;
                QString strVersion = xml.readElementText();
                minorVersion = strVersion.toInt(&convertOk);
                if (!convertOk) {
                    qWarning() << "Badly formed XML";
                    return;
                }
            }
        }
        xml.readNext();
    }

    // Assume defaults if not found
    if (majorVersion == -1) {
        majorVersion = 1;
    }
    if (minorVersion == -1) {
        minorVersion = 1;
    }
}

