#ifndef FACT_H
#define FACT_H

#include <QObject>
#include <QVariant>
#include "FactMetaData.h"

class Fact : public QObject
{
    Q_OBJECT
public:
    explicit Fact(QObject *parent = 0);
    Fact(int componentId,QString name, FactMetaData::ValueType_t type,QObject *parent);
    ~Fact();

    void setMetaData(FactMetaData* metadata);

    QVariant rawValue() const {return _rawValue;}    
    void setRawValue(const QVariant &value);

    /// Sets and sends new value to vehicle even if value is the same
    void forceSetRawValue(const QVariant &value);

    void _containerSetRawValue(const QVariant& value);

    int compId() const { return _compId;}
    QString group() const;
    QString name() const { return _name;}
    FactMetaData::ValueType_t type() const {return _type;}
    QString shortDescription() const;
    QString longDescription() const;

    QVariant rawDefaultValue() const;

    QVariant rawMin() const;
    QVariant rawMax() const;
    QString rawUnit() const;

    int decimalPlaces() const;
    double increment() const;
    bool rebootRequired() const;

    QStringList enumStrings() const;
    QVariantList enumValues() const;

signals:
    /// QObject Property System signal for value property changes
    /// This signal is only meant for use by the QT property system. It should not be connected to by client code.
    void valueChanged(QVariant value);

    /// Signalled when property has been changed by a call to the property write accessor
    /// This signal is meant for use by Fact container implementations.
    void _containerRawValueChanged(const QVariant& value);

    /// Signalled when the param write ack comes back from the vehicle
    void vehicleUpdated(QVariant value);

public slots:

private:
    QVariant _rawValue;
    FactMetaData* _metaData;
    int _compId;
    QString _name;
    FactMetaData::ValueType_t _type;
};

#endif // FACT_H
