#include "Fact.h"
#include <QDebug>

Fact::Fact(QObject *parent) :
    QObject(parent),
    _metaData(NULL),
    _type()
{

}

Fact::Fact(int componentId,QString name, FactMetaData::ValueType_t type,QObject *parent)
    :QObject(parent),
      _compId(componentId),
      _metaData(NULL),
      _name(name),
      _type(type)
{
    FactMetaData* metaData = new FactMetaData(_type,this);
    setMetaData(metaData);
}


Fact::~Fact()
{

}

QString Fact::group() const
{
    if(_metaData) {
        return _metaData->group();
    } else {
        qWarning() << "Meta data pointer missing";
        return QString();
    }
}

QString Fact::shortDescription() const
{
    if (_metaData) {
        return _metaData->shortDescription();
    } else {
        qWarning() << "Meta data pointer missing";
        return QString();
    }
}

QString Fact::longDescription() const
{
    if (_metaData) {
        return _metaData->longDescription();
    } else {
        qWarning() << "Meta data pointer missing";
        return QString();
    }
}

 QVariant Fact::rawDefaultValue() const
 {
     if (_metaData) {
         if(_metaData->defaultValueAvailable()) {
            qDebug()<<"Fact:FactMetaData:rawDefaultValue";            
         }
         else {
             qDebug()<<"Access to unavailable default value.";
         }
         return _metaData->rawDefaultValue();
     }
     else {
         qWarning() << "Meta data pointer missing";
         return QVariant(0);
     }
 }

QVariant Fact::rawMin() const
{
    if (_metaData) {
        return _metaData->rawMin();
    } else {
        qWarning() << "Meta data pointer missing";
        return QVariant(0);
    }
}

QVariant Fact::rawMax() const
{
    if (_metaData) {
        return _metaData->rawMax();
    } else {
        qWarning() << "Meta data pointer missing";
        return QVariant(0);
    }
}

QString Fact::rawUnit() const
{
    if (_metaData) {
        return _metaData->rawUnit();
    } else {
        qWarning() << "Meta data pointer missing";
        return QString();
    }
}

int Fact::decimalPlaces() const
{
    if (_metaData) {
        return _metaData->decimalPlaces();
    } else {
        qWarning() << "Meta data pointer missing";
        return FactMetaData::defaultDecimalPlaces;
    }
}

double Fact::increment() const
{
    if (_metaData) {
        return _metaData->increment();
    } else {
        qWarning() << "Meta data pointer missing";
        return std::numeric_limits<double>::quiet_NaN();
    }
}

bool Fact::rebootRequired() const
{
    if (_metaData) {
        return _metaData->rebootRequired();
    } else {
        qWarning() << "Meta data pointer missing";
        return false;
    }
}

QStringList Fact::enumStrings() const
{
    if(_metaData) {
        return _metaData->enumStrings();
    }else {
        qWarning() << "Meta data pointer missing";
        return QStringList();
    }
}

QVariantList Fact::enumValues() const
{
    if(_metaData) {
        return _metaData->enumValues();
    }else {
        qWarning() << "Meta data pointer missing";
        return QVariantList();
    }
}

void Fact::setRawValue(const QVariant &value)
{
    if(_metaData) {
        QVariant typedValue;
        QString errorString;

        //convertOnly
        if(_metaData->convertAndValidateRaw(value,true,typedValue,errorString)) {
            if(_rawValue != typedValue) {
                _rawValue.setValue(typedValue);
                emit valueChanged(rawValue());
                emit _containerRawValueChanged(rawValue());
            }
        }
        else {
            qWarning() << "Meta data pointer missing";
        }
    }
}

void Fact::forceSetRawValue(const QVariant &value)
{
    if(_metaData) {
        QVariant typedValue;
        QString errorString;

        //convertOnly
        if(_metaData->convertAndValidateRaw(value,true,typedValue,errorString)) {
            _rawValue.setValue(typedValue);
            emit valueChanged(rawValue());
            emit _containerRawValueChanged(rawValue());
        }
        else {
            qWarning() << "Meta data pointer missing";
        }
    }

}

 void Fact::_containerSetRawValue(const QVariant& value)
 {
     _rawValue = value;
     emit valueChanged(rawValue());
     emit vehicleUpdated(_rawValue);
 }

 void Fact::setMetaData(FactMetaData* metadata)
 {
     _metaData = metadata;
     emit valueChanged(rawValue());
 }
