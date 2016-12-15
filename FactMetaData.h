#ifndef FACTMETADATA_H
#define FACTMETADATA_H

#include <QObject>
#include <QMap>
#include <QVariant>

#include <QDebug>

class FactMetaData : public QObject
{
    Q_OBJECT
public:

    ~FactMetaData();

    typedef enum{
        typeUint8,
        typeInt8,
        typeUint16,
        typeInt16,
        typeUint32,
        typeInt32,
        typeFloat,
        typeDouble
    } ValueType_t;

    explicit FactMetaData(ValueType_t type, QObject *parent = 0);
    static ValueType_t stringToType(const QString &typeString, bool &unknownType);

    bool convertAndValidateRaw(const QVariant &rawValue, bool convertOnly, QVariant &convertValue, QString &errorString);

    ValueType_t type() const    {return _type;}
    void setGroup(const QString &group) { _group = group;}
    void setName(const QString &name) { _name = name;}

    void setShortDescription(const QString &shortDescription) {_shortDescription = shortDescription;}
    void setLongDescription(const QString &longDescription) {_longDescription = longDescription;}

    void setRawDefaultValue(const QVariant &rawDefaultValue);
    void setRawUnit(const QString &rawUnit);
    void setRawMin(const QVariant &rawMin);
    void setRawMax(const QVariant &rawMax);

    void setDecimalPlaces(int decimalPlaces) { _decimalPlaces = decimalPlaces;}
    void setIncrement(double increment) { _increment = increment;}
    void setRebootRequired(bool rebootRequired) { _rebootRequired = rebootRequired;}

     /// Used to add new values to the enum lists after the meta data has been loaded
    void addEnumInfo(const QVariant &enumValue,const QString &enumString);

    QString group() const {return _group;}
    QString name() const {return _name;}
    QString shortDescription() const {return _shortDescription;}
    QString longDescription() const {return _longDescription;}

    QVariant rawDefaultValue() const;
    bool defaultValueAvailable() const {return _defaultValueAvailable;}

    QVariant rawMin() const {return _rawMin;}
    QVariant rawMax() const {return _rawMax;}
    QString rawUnit() const {return _rawUnit;}

    int decimalPlaces() const {return _decimalPlaces;}
    double increment() const {return _increment;}
    bool rebootRequired() const {return _rebootRequired;}

    QStringList enumStrings() const {return _enumStrings;}
    QVariantList enumValues() const {return _enumValues;}

    static const int defaultDecimalPlaces = 3;  ///< Default value for decimal places if not specified/known
    static const int unknownDecimalPlaces = -1; ///< Number of decimal places to specify is not known

signals:

public slots:
private:

    QVariant _minForType() const;
    QVariant _maxForType() const;
    ValueType_t _type;

    bool     _defaultValueAvailable; //true when the default value we get is in range (_rawMin,_rawMax)
                                                                 //accepted and copied to _rawDefaultValue
    QString _group;
    QString _name;
    QString _shortDescription;
    QString _longDescription;
    QVariant _rawDefaultValue;
    QString _rawUnit;
    QVariant _rawMax;
    QVariant _rawMin;

    int _decimalPlaces;
    double _increment;
    bool _rebootRequired;

    QStringList _enumStrings;
    QVariantList _enumValues;

    };

#endif // FACTMETADATA_H
