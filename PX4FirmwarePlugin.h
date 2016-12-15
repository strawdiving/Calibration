#ifndef PX4FIRMWAREPLUGIN_H
#define PX4FIRMWAREPLUGIN_H

#include "Toolbox.h"
#include "Fact.h"

class QuadApplication;
class PX4ParameterMetaData;

class PX4FirmwarePlugin : public ToolBase
{
    Q_OBJECT
public:
    explicit PX4FirmwarePlugin(QuadApplication* app);
    ~PX4FirmwarePlugin();

     virtual void setToolbox(Toolbox* toolbox);

    /// Returns the parameter set version info pulled from inside the meta data file. -1 if not found.
    void        getParameterMetaDataVersionInfo (const QString& metaDataFile, int& majorVersion, int& minorVersion);


    PX4ParameterMetaData* loadParamFactMetaDataFile(QString &metaDataFile);

    /// Returns the internal resource parameter meta date file.
    QString     internalParameterMetaDataFile   (void) { return QString(":/ParameterFactMetaData.xml"); }

    void addMetaDataToFact(Fact* fact);

signals:

public slots:

private:
    PX4ParameterMetaData* _px4metaData;

};

#endif // PX4FIRMWAREPLUGIN_H
