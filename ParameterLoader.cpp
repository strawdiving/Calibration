#include "ParameterLoader.h"
#include "QuadApplication.h"
#include <QSettings>
#include <QDir>
#include <QFile>
#include <QDebug>
#include "PX4AutopioltPlugins/PX4AutopilotPlugin.h"
#include "PX4FirmwarePlugin.h"
#include <QVariant>
#include "Vehicle.h"

const char* ParameterLoader::_cachedMetaDataFilePrefix = "ParameterFactMetaData";
const QString ParameterLoader::_defaultCompIdParam = QString("SYS_AUTOSTART");
const QString ParameterLoader::_versionParam = QString("SYS_PARAM_VER");

Fact ParameterLoader::_defaultFact;

ParameterLoader::ParameterLoader(Vehicle* vehicle,QObject *parent) :
    QObject(parent),
   // _defaultCompId(PX4AutopilotPlugin::defaultCompId),
    _vehicle(vehicle),
    _defaultCompId(0),
    _paramSetMajorVersion(-1),
    _currentParamCount(0),
    _initialLoadComplete(false),
    _parametersReady(false),
    _compParamsComplete(false),
    _parameterMetaData(NULL)
{


}

ParameterLoader::~ParameterLoader()
{

}

///For test
 void ParameterLoader::_paramUpdate(int paramCount,QString paramName,FactMetaData::ValueType_t type,QVariant& value)
 {
     int compId = 0;

     if(_versionParam == paramName) {
         _paramSetMajorVersion = value.toInt();
     }
     _dataMutex.lock();

     if(!_mapParamName2Variant[compId].contains(paramName)) {
         //qDebug()<<"ParameterLoader: adding new fact.";
         _currentParamCount++;
         Fact* fact = new Fact(compId,paramName,type,this);
         _mapParamName2Variant[compId][paramName] = QVariant::fromValue(fact);
         connect(fact,&Fact::_containerRawValueChanged,this,&ParameterLoader::_valueUpdated);
     }

     _dataMutex.unlock();

    Q_ASSERT(_mapParamName2Variant[compId].contains(paramName));
     Fact* fact = _mapParamName2Variant[compId][paramName].value<Fact*>();
     Q_ASSERT(fact);

      fact->_containerSetRawValue(value);
      if(_currentParamCount == paramCount) {
          qDebug()<<QString("%1 ParameterLoader: parameters loading completed").arg(paramCount);
          _currentParamCount = 0;
          _compParamsComplete = true;

          if(compId == _defaultCompId) {
             // Add meta data to default component.
             _addMetaDataToDefaultComponent();
          }
      }
      // Don't fail initial load complete if default component isn't found yet. That will be handled in wait timeout check.
      _checkInitialLoadComplete(false /* failIfNoDefaultComponent */);
 }

 void ParameterLoader::_addMetaDataToDefaultComponent(void)
 {
     if(_defaultCompId == PX4AutopilotPlugin::defaultCompId) {
         return;
     }

     QString metaDataFile;
     int majorVersion, minorVersion;
     metaDataFile = parameterMetaDataFile(MAV_AUTOPILOT_PX4,_paramSetMajorVersion, majorVersion, minorVersion);
     //_parameterMetaData = _vehicle->firmwarePlugin()->loadParamFactMetaDataFile(metaDataFile);

     //qDebug()<<"count: "<<_mapParamName2Variant[_defaultCompId].keys().count();
      foreach (const QString&key,_mapParamName2Variant[_defaultCompId].keys()) {
         _vehicle->firmwarePlugin()->addMetaDataToFact(_mapParamName2Variant[_defaultCompId][key].value<Fact*>());
     }
 }

 /// @param failIfNoDefaultComponent true: Fails parameter load if no default component but we should have one
 void ParameterLoader::_checkInitialLoadComplete(bool failIfNoDefaultComponent)
 {    
     if(_initialLoadComplete) {
         return;
     }

     if (!failIfNoDefaultComponent && _defaultCompId == PX4AutopilotPlugin::defaultCompId) {
         // We are still waiting for default component to show up
         return;
     }
     if(!_compParamsComplete) {

       return;
     }

     // We aren't waiting for any more initial parameter updates, initial parameter loading is complete
     _initialLoadComplete = true;
     // signal good load
     qDebug()<<"parameters ready true";
    _parametersReady = true;
    emit paramsReady(true);
 }

/*
/// Called whenever a parameter is updated or first seen.
void ParameterLoader::_parameterUpdate(int componentId, QString paramName, int paramCount, int paramId, int type,QVariant value)
{
  qDebug()<<QString("_parameterUpdate (compId :%1,name:%2,count:%3,"
                    "index:%4,mavType:%5,value:%6).").arg(QString::number(componentId)).arg(paramName)
            .arg(QString::number(paramCount)).arg(QString::number(paramId)).arg(type).arg(value.toString());

  _dataMutex.lock();

  // Update our total parameter counts
  if(!_paramCountMap.contains(componentId)) {
      _paramCountMap[componentId] = paramCount;
      _totalParamCount += paramCount;
  }

  _paramId2NameMap[componentId][paramId] = paramName;

   // If never seen this component id before, setup the wait lists. Add all indices to the wait list (index is 0-based)
  if(!_waitingReadParamIndexMap.contains(componentId)) {

       // Add the new component id, as well as the the new waiting index and set the retry count for that index to 0
      for(int index = 0; index<paramCount; index++) {
          _waitingReadParamIndexMap[componentId][index] = 0;
      }
      // The read and write waiting lists for this component are initialized the empty
      _waitingReadParamNameMap[componentId] = QMap<QString,int>();
      _waitingWriteParamNameMap[componentId] = QMap<QString,int>();
      qDebug()<<"Seeing component for the first time. Id: "<<componentId<<"parametet count: "<<paramCount;
  }

  // Determine default component id
  if(paramName == _defaultCompIdParam) {
      qDebug()<<"Default component id determined: "<<componentId;
      _defaultCompId = componentId;
  }

  // We need to know when we get the last param from a component in order to complete setup
  if(_waitingReadParamIndexMap[componentId].count() == 1) {
      _compParamsComplete = true;
  }

  if(!_versionParam.isEmpty() && _versionParam == paramName) {
      _paramSetMajorVersion = value.toInt();
  }

if(!_mapParamName2Variant.contains(componentId) || !_mapParamName2Variant[componentId].contains(paramName)) {
    qDebug()<<"Adding new fact";
    FactMetaData::ValueType_t factType;
    switch(type) {
    case MAV_PARAM_TYPE_UINT8:
        factType = FactMetaData::typeUint8;
        break;
    case MAV_PARAM_TYPE_INT8:
        factType = FactMetaData::typeInt8;
        break;
    case MAV_PARAM_TYPE_UINT16:
        factType = FactMetaData::typeUint16;
        break;
    case MAV_PARAM_TYPE_INT16:
        factType = FactMetaData::typeInt16;
        break;
    case MAV_PARAM_TYPE_UINT32:
        factType = FactMetaData::typeUint32;
        break;
    case MAV_PARAM_TYPE_INT32:
        factType = FactMetaData::typeInt32;
        break;
    case MAV_PARAM_TYPE_REAL32:
        factType = FactMetaData::typeFloat;
        break;
    case MAV_PARAM_TYPE_REAL64:
        factType = FactMetaData::typeDouble;
        break;
    default:
        factType = FactMetaData::typeInt32;
        qCritical()<<"Unsupported fact type:"<<type;
        break;
    }

    Fact* fact = new Fact(componentId,paramName,factType,this);
    //Returns a QVariant containing a copy of value
    _mapParamName2Variant[componentId][paramName] = QVariant::fromValue(fact);

    // We need to know when the fact changes from QML so that we can send the new value to the parameter manager
    connect(fact, &Fact::_containerRawValueChanged, this, &ParameterLoader::_valueUpdated);
}
_dataMutex.unlock();

}
*/

void ParameterLoader::cacheMetaDataFile(const QString& metaDataFile, MAV_AUTOPILOT firmwareType)
{
    PX4FirmwarePlugin* plugin = NULL;
    plugin = qgcApp()->toolbox()->firmwarePlugin();

   /* if(firmwareType == MAV_AUTOPILOT_PX4) {
        plugin = new PX4FirmwarePlugin;
    }
    */
    int newMajorVersion, newMinorVersion;
    plugin->getParameterMetaDataVersionInfo(metaDataFile, newMajorVersion, newMinorVersion);
    qDebug() << "CacheMetaDataFile file:firmware:major;minor" << metaDataFile << firmwareType << newMajorVersion << newMinorVersion;

    // Find the cache hit closest to this new file
    int cacheMajorVersion, cacheMinorVersion;
    QString cacheHit = ParameterLoader::parameterMetaDataFile(firmwareType, newMajorVersion, cacheMajorVersion, cacheMinorVersion);
    qDebug()  << "CacheMetaDataFile cacheHit file:firmware:major;minor" << cacheHit << cacheMajorVersion << cacheMinorVersion;

    bool cacheNewFile = false;
    if (cacheHit.isEmpty()) {
        // No cache hits, store the new file
        cacheNewFile = true;
    } else if (cacheMajorVersion == newMajorVersion) {
        // Direct hit on major version in cache:
        // Cache new file if newer minor version
        // Also delete older cache file
        if (newMinorVersion > cacheMinorVersion) {
            cacheNewFile = true;
            QFile::remove(cacheHit);
        }
    } else {
        // Indirect hit in cache, store new file
        cacheNewFile = true;
    }

    if (cacheNewFile) {
        // Cached files are stored in settings location. Copy from current file to cache naming.

        QSettings settings;
        QDir cacheDir = QFileInfo(settings.fileName()).dir();
        QFile cacheFile(cacheDir.filePath(QString("%1.%2.%3.xml").arg(_cachedMetaDataFilePrefix).arg(firmwareType).arg(newMajorVersion)));
        qDebug()  << "ParameterLoader::cacheMetaDataFile caching file:" << cacheFile.fileName();
        QFile newFile(metaDataFile);
        newFile.copy(cacheFile.fileName());
    }
}

QString ParameterLoader::parameterMetaDataFile(MAV_AUTOPILOT firmwareType, int wantedMajorVersion, int& majorVersion, int& minorVersion)
{
    bool            cacheHit = false;

    PX4FirmwarePlugin* plugin = NULL;
    plugin = qgcApp()->toolbox()->firmwarePlugin();

   /* if(firmwareType == MAV_AUTOPILOT_PX4) {
        plugin = new PX4FirmwarePlugin;
    }
    */

    // Cached files are stored in settings location
    QSettings settings;
    QDir cacheDir = QFileInfo(settings.fileName()).dir();

    // First look for a direct cache hit
    int cacheMinorVersion, cacheMajorVersion;
    QFile cacheFile(cacheDir.filePath(QString("%1.%2.%3.xml").arg(_cachedMetaDataFilePrefix).arg(firmwareType).arg(wantedMajorVersion)));
    if (cacheFile.exists()) {
        plugin->getParameterMetaDataVersionInfo(cacheFile.fileName(), cacheMajorVersion, cacheMinorVersion);
        if (wantedMajorVersion != cacheMajorVersion) {
            qWarning() << "Parameter meta data cache corruption:" << cacheFile.fileName() << "major version does not match file name" << "actual:excepted" << cacheMajorVersion << wantedMajorVersion;
        } else {
            qDebug()  << "Direct cache hit on file:major:minor" << cacheFile.fileName() << cacheMajorVersion << cacheMinorVersion;
            cacheHit = true;
        }
    }


    if (!cacheHit) {
        // No direct hit, look for lower param set version
        QString wildcard = QString("%1.%2.*.xml").arg(_cachedMetaDataFilePrefix).arg(firmwareType);
        //返回此目录下的所有文件及目录的名字,根据name and attibute filters排序，并根据flag分类
        QStringList cacheHits = cacheDir.entryList(QStringList(wildcard), QDir::Files, QDir::Name);

        // Find the highest major version number which is below the vehicles major version number
        int cacheHitIndex = -1;
        cacheMajorVersion = -1;
        QRegExp regExp(QString("%1\\.%2\\.(\\d*)\\.xml").arg(_cachedMetaDataFilePrefix).arg(firmwareType));
        for (int i=0; i< cacheHits.count(); i++) {
            if (regExp.exactMatch(cacheHits[i]) && regExp.captureCount() == 1) {
                int majorVersion = regExp.capturedTexts()[0].toInt();
                if (majorVersion > cacheMajorVersion && majorVersion < wantedMajorVersion) {
                    cacheMajorVersion = majorVersion;
                    cacheHitIndex = i;
                }
            }
        }
        if (cacheHitIndex != -1) {
            // We have a cache hit on a lower major version, read minor version as well
            int majorVersion;
            cacheFile.setFileName(cacheDir.filePath(cacheHits[cacheHitIndex]));
            plugin->getParameterMetaDataVersionInfo(cacheFile.fileName(), majorVersion, cacheMinorVersion);
            if (majorVersion != cacheMajorVersion) {
                qWarning() << "Parameter meta data cache corruption:" << cacheFile.fileName() << "major version does not match file name" << "actual:excepted" << majorVersion << cacheMajorVersion;
                cacheHit = false;
            } else {
                qDebug() << "Indirect cache hit on file:major:minor:want" << cacheFile.fileName() << cacheMajorVersion << cacheMinorVersion << wantedMajorVersion;
                cacheHit = true;
            }
        }
    }



    int internalMinorVersion, internalMajorVersion;
    QString internalMetaDataFile = plugin->internalParameterMetaDataFile();
    plugin->getParameterMetaDataVersionInfo(internalMetaDataFile, internalMajorVersion, internalMinorVersion);
    qDebug()  << "Internal meta data file:major:minor" << internalMetaDataFile << internalMajorVersion << internalMinorVersion;
    if (cacheHit) {
        // Cache hit is available, we need to check if internal meta data is a better match, if so use internal version
        if (internalMajorVersion == wantedMajorVersion) {
            if (cacheMajorVersion == wantedMajorVersion) {
                // Both internal and cache are direct hit on major version, Use higher minor version number
                cacheHit = cacheMinorVersion > internalMinorVersion;
            } else {
                // Direct internal hit, but not direct hit in cache, use internal
                cacheHit = false;
            }
        } else {
            if (cacheMajorVersion == wantedMajorVersion) {
                // Direct hit on cache, no direct hit on internal, use cache
                cacheHit = true;
            } else {
                // No direct hit anywhere, use internal
                cacheHit = false;
            }
        }
    }

    qDebug()<<cacheHit<<cacheFile.fileName();
    QString metaDataFile;
    if (cacheHit) {
        majorVersion = cacheMajorVersion;
        minorVersion = cacheMinorVersion;
        metaDataFile = cacheFile.fileName();
    } else {
        majorVersion = internalMajorVersion;
        minorVersion = internalMinorVersion;
        metaDataFile = internalMetaDataFile;
    }
    qDebug()  << "ParameterLoader::parameterMetaDataFile file:major:minor" << metaDataFile << majorVersion << minorVersion;

    return metaDataFile;
}



/// Connected to Fact::valueUpdated
/// Writes the parameter to mavlink, sets up for write wait
void ParameterLoader::_valueUpdated(const QVariant& value)
{
Q_UNUSED(value)
}

bool ParameterLoader::paramExists(int componentId,const QString& name)
{
    bool exist = false;
    componentId = _actualCompId(componentId);
    if(_mapParamName2Variant.contains(componentId)) {
        if(_mapParamName2Variant[componentId].contains(name)) {
            exist = true;
        }
    }
    return exist;
}

Fact* ParameterLoader::getFact(int componentId, const QString& name)
{
    componentId = _actualCompId(componentId);
    if(!_mapParamName2Variant.contains(componentId) || !_mapParamName2Variant[componentId].contains(name)) {
        return &_defaultFact;
    }
    return _mapParamName2Variant[componentId][name].value<Fact*>();
    qDebug()<<"ParameterLoader: "<<_mapParamName2Variant[componentId][name].value<Fact*>()->name();
}

int ParameterLoader::_actualCompId(int componentId)
{
    if(componentId == PX4AutopilotPlugin::defaultCompId) {
      componentId = _defaultCompId;
        if(componentId == PX4AutopilotPlugin::defaultCompId) {
            qWarning()<<"Default component id not set";
        }
    }
    return componentId;
}
