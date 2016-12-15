#ifndef PARAMETERLOADER_H
#define PARAMETERLOADER_H

#include <QObject>
#include <QVariant>
#include <common/mavlink.h>
#include "PX4FirmwarePlugin.h"
#include <QMutex>
#include <QMap>
#include "Fact.h"
#include "PX4ParameterMetaData.h"

class Vehicle;

class ParameterLoader : public QObject
{
    Q_OBJECT
public:
    explicit ParameterLoader(Vehicle *vehicle, QObject *parent = 0);
    ~ParameterLoader();

    /// If this file is newer than anything in the cache, cache it as the latest version
    static void cacheMetaDataFile(const QString& metaDataFile, MAV_AUTOPILOT firmwareType);

    /// Returns the newest available parameter meta data file (from internal) for the specified information.
    ///     @param wantedMajorVersion Major version you are looking for
    ///     @param[out] majorVersion Major version for found meta data
    ///     @param[out] minorVersion Minor version for found meta data
    /// @return Meta data file name of best match, emptyString is none found
    static QString parameterMetaDataFile(MAV_AUTOPILOT firmwareType, int wantedMajorVersion, int& majorVersion, int& minorVersion);

    bool paramExists(int componentId,const QString& name);

    Fact* getFact(int componentId, const QString& name);
    int _actualCompId(int componentId);



signals:
    void readParameterRaw(int componentId, const QString& paramName, int paramIndex);
    void writeParameterRaw(int componentId, const QString& paramName, const QVariant& value);
    void paramsReady(bool noMissingParams);

public slots:
    //void _parameterUpdate(int componentId, QString paramName, int paramCount, int paramId, int type, QVariant value);
    void _valueUpdated(const QVariant& value);
    ///For test
    void _paramUpdate(int paramCount,QString paramName,FactMetaData::ValueType_t type,QVariant& value);

private:

    void _addMetaDataToDefaultComponent(void);
    /// @param failIfNoDefaultComponent true: Fails parameter load if no default component but we should have one
    void _checkInitialLoadComplete(bool failIfNoDefaultComponent);

    Vehicle* _vehicle;
    PX4FirmwarePlugin *_px4FirmwarePlugin;
    static const char* _cachedMetaDataFilePrefix;
    QMutex _dataMutex;

    QMap<int,int> _paramCountMap;  /// Key: Component id, Value: count of parameters in this component
    QMap<int,QMap<int,QString>> _paramId2NameMap;
    QMap<int,QMap<int,int>> _waitingReadParamIndexMap;
    QMap<int,QMap<QString,int>> _waitingReadParamNameMap;
    QMap<int,QMap<QString,int>> _waitingWriteParamNameMap;

    QMap<int,QMap<QString,QVariant>> _mapParamName2Variant;

    ///< Parameter which identifies default component
    static const QString  _defaultCompIdParam;
   ///< Parameter which contains parameter set version
    static const QString     _versionParam;
    int _paramSetMajorVersion;

    PX4ParameterMetaData* _parameterMetaData;


    int _defaultCompId;

    bool _compParamsComplete;
    bool _initialLoadComplete;
    bool        _parametersReady;               ///< true: full set of parameters correctly loaded

    //received param count
    int _currentParamCount;
    static Fact _defaultFact;   ///< Used to return default fact, when parameter not found
};

#endif // PARAMETERLOADER_H
