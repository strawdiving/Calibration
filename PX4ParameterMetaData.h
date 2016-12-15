#ifndef PX4PARAMETERMETADATA_H
#define PX4PARAMETERMETADATA_H

#include <QObject>
#include "FactMetaData.h"
#include "Fact.h"

class PX4ParameterMetaData : public QObject
{
    Q_OBJECT
public:
    explicit PX4ParameterMetaData(QObject *parent = 0);
    ~PX4ParameterMetaData();

    enum{
        XMLStateNone,
        XMLStateFoundParameters,
        XMLStateFoundVersion,
        XMLStateFoundGroup,
        XMLStateFoundParameter,
        XMLStateDone
    };
    void loadParameterFactMetaDataFile(const QString& metaDataFile);
    void loadParamFactMetaDataFile(QString &metaDataFile);
    void addMetaDataToFact(Fact* fact);

signals:
    ///To show params in paramPage
    void factMetaData(QMap<QString, FactMetaData*> mapParameterName2FactMetaData);    
    ///For test. Store param value in FactGroup
    void paramUpdate(int paramCount,QString paramName,FactMetaData::ValueType_t type,QVariant& value);

public slots:


private:
    bool _parameterMetaDataLoaded;
    QMap<QString, FactMetaData*> _mapParameterName2FactMetaData;
};

#endif // PX4PARAMETERMETADATA_H
