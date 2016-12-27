#include "PX4ParameterMetaData.h"
#include <QFile>
#include <QDir>
#include <QXmlStreamReader>
#include <QDebug>
#include <QRegExp>

PX4ParameterMetaData::PX4ParameterMetaData(QObject *parent) :
    QObject(parent),
    _parameterMetaDataLoaded(false)
{

}

PX4ParameterMetaData::~PX4ParameterMetaData()
{

}

void PX4ParameterMetaData::addMetaDataToFact(Fact* fact)
{
    if(_mapParameterName2FactMetaData.contains(fact->name())) {
        fact->setMetaData(_mapParameterName2FactMetaData[fact->name()]);
    }
}

void PX4ParameterMetaData::loadParamFactMetaDataFile(QString &metaDataFile)
{
    Q_UNUSED(metaDataFile)
    _mapParameterName2FactMetaData.clear();
    //loadParameterFactMetaDataFile(metaDataFile);
    loadParameterFactMetaDataFile(QString("F:\\baseModule\\PX4ParameterFactMetaData.xml"));
    if(!_mapParameterName2FactMetaData.isEmpty()) {

        QStringList unusedParams;

        foreach (const QString paramName,_mapParameterName2FactMetaData.keys()) {
            bool paramNeeded = false;

            QStringList neededGroups;
            neededGroups<<"Radio Calibration"<<"Battery Calibration"<<"Sensor Calibration"
                      <<"Commander"<<"Radio Switches"<<"System"
                     <<"Multicopter Attitude Control"<<"Multicopter Position Control";

            for(int i = 0;i<neededGroups.count();i++) {
                QRegExp regExp(neededGroups.at(i),Qt::CaseInsensitive);
                if(regExp.indexIn(_mapParameterName2FactMetaData[paramName]->group()) != -1) {
                    //qDebug()<<"Found needed group:"<<_mapParameterName2FactMetaData[paramName]->group();
                    paramNeeded = true;
                }
            }
            if(!paramNeeded) {
                unusedParams<<paramName;
            }
        }
        qDebug()<<unusedParams.count();
        foreach (QString param, unusedParams) {
            _mapParameterName2FactMetaData.remove(param);
        }
        emit factMetaData(_mapParameterName2FactMetaData);

        ///For test
        foreach (const QString paramName,_mapParameterName2FactMetaData.keys()) {
            emit paramUpdate(_mapParameterName2FactMetaData.keys().count(),paramName,_mapParameterName2FactMetaData[paramName]->type(),_mapParameterName2FactMetaData[paramName]->rawDefaultValue());
       }
    }
}

 void PX4ParameterMetaData::loadParameterFactMetaDataFile(const QString& metaDataFile)
 {
     qDebug()<<"PX4ParameterMetaData::loadParameterFactMetaDataFile."<<metaDataFile;

     if(_parameterMetaDataLoaded){
         qWarning() << "Internal error: parameter meta data loaded more than once";
         return;
     }
     _parameterMetaDataLoaded = true;
     qDebug()<<"Loading parameter meta data......";

     QFile xmlFile(metaDataFile);
     if(!xmlFile.exists()){
         qWarning()<<"Internal error:metaDataFile missing"<<metaDataFile;
         return;
     }
     if(!xmlFile.open(QIODevice::ReadOnly)) {
         qWarning()<<"Internal error: Unable to open parameter file:"<<metaDataFile<<xmlFile.errorString();
         return;
     }

     QXmlStreamReader xml(xmlFile.readAll());
     xmlFile.close();
     if(xml.hasError()) {
         qWarning()<<"Badly formed xml"<<xml.errorString();
         return;
     }

     int xmlState = XMLStateNone;
     QString factGroup;
     FactMetaData* metaData = NULL;
     bool badMetaData = false;
     QString errorString;

     while(!xml.atEnd()) {
         if(xml.isStartElement()) {
             QString elementName = xml.name().toString();

             if(elementName == "parameters") {
                 if(xmlState!=XMLStateNone) {
                     qWarning() << "parameters: Badly formed XML";
                     return;
                 }
                 xmlState = XMLStateFoundParameters;

             } else if(elementName == "version") {
                 if(xmlState!=XMLStateFoundParameters) {
                     qWarning() << "version: Badly formed XML";
                     return;
                 }
                 xmlState = XMLStateFoundVersion;
                 bool convertOK = false;
                 int version = xml.readElementText().toInt(&convertOK);
                 if(!convertOK) {
                     qWarning() << "version1: Badly formed XML";
                     return;
                 }
                 if(version <= 2) {
                     qDebug() << "Parameter version stamp too old, skipping load. Found:" << version << "Want: 3";
                     return;
                 }
             }
             else if(elementName == "parameter_version_major") {
                 //skip
             }
             else if(elementName == "parameter_version_minor") {
                 //skip
             }
             else if(elementName == "group") {
                 if(xmlState!=XMLStateFoundVersion) {
                    qDebug()<<"Parameter version stamp not found, skipping load"<<metaDataFile ;
                     return;
                 }
                 xmlState = XMLStateFoundGroup;
                 factGroup =xml.attributes().value("name").toString();

                 if(!xml.attributes().hasAttribute("name")) {
                     qDebug() <<  "groupname: Badly formed XML";
                     return;
                 }
             }
            else if(elementName == "parameter") {
                 if(xmlState!=XMLStateFoundGroup) {
                     qDebug() <<  "parameter: Badly formed XML";
                     return;
                 }
                 xmlState = XMLStateFoundParameter;
                 if(!xml.attributes().hasAttribute("name") || !xml.attributes().hasAttribute("type")) {
                     qDebug() <<  "name & type: Badly formed XML";
                     return;
                 }

                 QString name = xml.attributes().value("name").toString();
                 QString type = xml.attributes().value("type").toString();
                 QString strDefault= xml.attributes().value("default").toString();

                 //qDebug()<<"Found parameter name:"<<name<<" type:"<<type<<" default:"<<strDefault;

                 // Convert type from string to FactMetaData::ValueType_t
                 bool unknownType;
                 FactMetaData::ValueType_t foundType = FactMetaData::stringToType(type,unknownType);
                 if(unknownType) {
                     qWarning()<<"Parameter meta data with bad type: "<<type<<" name: "<<name;
                     return;
                 }

                 metaData = new FactMetaData(foundType);

                 //add to FactMetaData
                 if(_mapParameterName2FactMetaData.contains(name)) {
                     badMetaData = true;
                     qWarning()<<"Duplicate parameter found: "<<name;
                     //reset to default meta data
                     _mapParameterName2FactMetaData[name] = metaData;
                 }
                 else {
                 _mapParameterName2FactMetaData[name] = metaData;
                 metaData->setGroup(factGroup);
                 metaData->setName(name);

                 if(xml.attributes().hasAttribute("default") && !strDefault.isEmpty()) {
                     QVariant varDefault;

                     if(metaData->convertAndValidateRaw(strDefault,false,varDefault,errorString)) {
                         metaData->setRawDefaultValue(varDefault);                         
                     }
                     else {
                         qDebug()<< "Invalid default value, name:" << name << " type:" << type << " default:" << strDefault << " error:" << errorString;
                     }
                 }
                 }
             }
             else {
                 //be getting meta data now
                 if(xmlState!=XMLStateFoundParameter) {
                     qDebug() <<  "Badly formed XML"<<xmlState;
                     return;
                 }

                  if(!badMetaData) {
                     if(elementName == "short_desc") {
                         QString text = xml.readElementText();
                         text = text.replace("\n"," ");
                         //qDebug()<<"Short Description: "<<text;
                         metaData->setShortDescription(text);
                     }
                     else if(elementName == "long_desc") {
                         QString text = xml.readElementText();
                         text = text.replace("\n"," ");
                         //qDebug()<<"Long Description: "<<text;
                         metaData->setLongDescription(text);
                     }

                     else if(elementName == "min") {
                         QString text = xml.readElementText();
                         //qDebug()<<"Min: "<<text;
                         QVariant varMin;
                         //convertOnly, i.e. only convertOk matters
                         if(metaData->convertAndValidateRaw(text,true,varMin,errorString)) {
                             metaData->setRawMin(varMin);
                         }
                         else {
                             qWarning()<< "Invalid min value, name:" << metaData->name() << " type:" << metaData->type() << " min:" << text << " error:" << errorString;
                         }
                     }
                     else if(elementName == "max") {
                         QString text = xml.readElementText();
                         //qDebug()<<"Max: "<<text;
                         QVariant varMax;
                         //convertOnly, i.e. only convertOk matters
                         if(metaData->convertAndValidateRaw(text,true,varMax,errorString)) {
                             metaData->setRawMax(varMax);
                         }
                         else {
                             qWarning()<< "Invalid max value, name:" << metaData->name() << " type:" << metaData->type() << " min:" << text << " error:" << errorString;
                         }
                     }
                     else if(elementName == "unit") {
                         QString text = xml.readElementText();
                         //qDebug()<<"Unit: "<<text;
                         metaData->setRawUnit(text);
                     }
                     else if(elementName == "decimal") {
                         QString text = xml.readElementText();
                         //qDebug()<<"Decimal: "<<text;

                         bool convertOk;
                         QVariant varDecimals = QVariant(text).toUInt(&convertOk);
                         if(convertOk) {
                             metaData->setDecimalPlaces(varDecimals.toInt());
                         }
                         else {
                             qWarning()<< "Invalid decimal value, name:" << metaData->name() << " type:" << metaData->type() << " decimal:" << text << " error: invalid number";
                         }
                     }
                     else if(elementName == "reboot_required") {
                         QString text = xml.readElementText();
                         //qDebug()<<"Reboot_required: "<<text;
                         if(text.compare("true",Qt::CaseInsensitive) == 0) {
                             metaData->setRebootRequired(true);
                         }
                     }
                     else if(elementName == "values") {
                     }
                     else if(elementName == "value") {
                         QString enumValueStr = xml.attributes().value("code").toString();
                         QString enumString = xml.readElementText();
                         //qDebug()<<"Parameter value: "<<enumString<<" code: "<<enumValueStr;

                         QVariant enumValue;
                         QString errorString;
                         if(metaData->convertAndValidateRaw(enumValueStr,false,enumValue,errorString)) {
                             metaData->addEnumInfo(enumValue,enumString);
                         }
                         else {
                             qDebug()<<"Invalid enum value, name:" << metaData->name()
                                    << " type:" << metaData->type() << " value:" << enumValueStr
                                    << " error:" << errorString;
                         }
                     }
                     else if(elementName == "increment") {
                         double increment;
                         bool ok;
                         QString text = xml.readElementText();
                         increment = text.toDouble(&ok);
                         if(ok) {
                             metaData->setIncrement(increment);
                         }
                         else {
                             qWarning()<< "Invalid value for increment, name:" << metaData->name() << " increment:" << text;
                         }
                     }
                     else {
                         //qDebug()<< "Unknown element in XML: " << elementName;
                 }
             }
         }

     }
         else if (xml.isEndElement()) {
            QString elementName = xml.name().toString();
            if(elementName == "parameter") {
                // Reset for next parameter
                metaData = NULL;
                badMetaData = false;
                xmlState = XMLStateFoundGroup;
            }
            else if(elementName == "group") {
                xmlState = XMLStateFoundVersion;
            }
         else if (elementName == "parameters") {
                xmlState = XMLStateFoundParameters;
            }
         }

         xml.readNext();
     }
 }
