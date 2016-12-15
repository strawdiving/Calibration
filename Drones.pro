#-------------------------------------------------
#
# Project created by QtCreator 2016-06-24T09:26:30
#
#-------------------------------------------------

QT       += core \
                  gui \
                  serialport \
                  axcontainer \
                  multimedia

!MobileBuild {
QT += \
    printsupport \
    serialport \
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Drones
TEMPLATE = app

include(./qextserialport/src/qextserialport.pri)
INCLUDEPATH +=./qextserialport/src/qextserialport

include(./MAVLinkLib.pri)
INCLUDEPATH +=./libs/mavlink/include/mavlink/v1.0

SOURCES += main.cpp\
        mainwindow.cpp \
    attitude_indicator.cpp \
    audio_worker.cpp \
    helper.cpp \
    linkmanager.cpp \
    SerialCommunication.cpp \
    Fact.cpp \
    FactMetaData.cpp \
    ParameterLoader.cpp \
    PX4ParameterMetaData.cpp \
    VehicleComponent.cpp \
    PX4AutopioltPlugins/AirframeComponent.cpp \
    PX4AutopioltPlugins/FlightModesComponent.cpp \
    PX4AutopioltPlugins/PowerComponent.cpp \
    PX4AutopioltPlugins/PX4AutopilotPlugin.cpp \
    PX4AutopioltPlugins/RadioComponent.cpp \
    PX4AutopioltPlugins/SafetyComponent.cpp \
    PX4AutopioltPlugins/SensorsComponent.cpp \
    FirmwareUpgrade/Bootloader.cpp \
    FirmwareUpgrade/FirmwareImage.cpp \
    FirmwareUpgrade/PX4FirmUpgradeThread.cpp \
    PX4FirmwarePlugin.cpp \
    PX4AutopioltPlugins/AirframeComponentController.cpp \
    SetupWizard/AirframePage.cpp \
    SetupWizard/FirmwarePage.cpp \
    SetupWizard/ParamsPage.cpp \
    SetupWizard/SensorsPage.cpp \
    Vehicle.cpp \
    PX4AutopioltPlugins/ParamEditorController.cpp \
    PX4AutopioltPlugins/SensorsComponentController.cpp \
    PX4AutopioltPlugins/PowerComponentController.cpp \
    QuadApplication.cpp \
    Toolbox.cpp \
    VehicleManager.cpp \
    UASMessageHandler.cpp \
    UAS.cpp \
    TitleLabel.cpp \
    SetupWizard/SummaryPage.cpp \
    ComponentController.cpp \
    SetupWizard/MessagePanel.cpp \
    SetupWidget.cpp \
    SetupWizard/PowerPage.cpp

HEADERS  += mainwindow.h \
    attitude_indicator.h \
    audio_worker.h \
    helper.h \
    linkmanager.h \
    SerialCommunication.h \
    Fact.h \
    FactMetaData.h \
    ParameterLoader.h \
    PX4ParameterMetaData.h \
    VehicleComponent.h \
    PX4AutopioltPlugins/AirframeComponent.h \
    PX4AutopioltPlugins/FlightModesComponent.h \
    PX4AutopioltPlugins/PowerComponent.h \
    PX4AutopioltPlugins/PX4AutopilotPlugin.h \
    PX4AutopioltPlugins/RadioComponent.h \
    PX4AutopioltPlugins/SafetyComponent.h \
    PX4AutopioltPlugins/SensorsComponent.h \
    FirmwareUpgrade/Bootloader.h \
    FirmwareUpgrade/FirmwareImage.h \
    FirmwareUpgrade/PX4FirmUpgradeThread.h \
    PX4FirmwarePlugin.h \
    PX4AutopioltPlugins/AirframeComponentController.h \
    SetupWizard/AirframePage.h \
    SetupWizard/FirmwarePage.h \
    SetupWizard/ParamsPage.h \
    SetupWizard/SensorsPage.h \
    Vehicle.h \
    PX4AutopioltPlugins/ParamEditorController.h \
    PX4AutopioltPlugins/SensorsComponentController.h \
    PX4AutopioltPlugins/PowerComponentController.h \
    QuadApplication.h \
    Toolbox.h \
    VehicleManager.h \
    UASMessageHandler.h \
    UAS.h \
    TitleLabel.h \
    SetupWizard/SummaryPage.h \
    ComponentController.h \
    SetupWizard/MessagePanel.h \
    SetupWidget.h \
    SetupWizard/PowerPage.h

FORMS    += mainwindow.ui \
    SetupWidget.ui \
    powerpage.ui

UI_DIR  += E:\baseModule-12.1

RESOURCES += \
    attitude.qrc \
    qml.qrc

DISTFILES += \
    PX4AirframeFactMetaData.xml \
    PX4ParameterFactMetaData.xml

