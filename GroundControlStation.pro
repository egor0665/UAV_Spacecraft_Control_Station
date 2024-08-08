QT       += core gui opengl serialport network
LIBS     += -lopengl32 -lglu32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connectedvehicle.cpp \
    connection/connectionhandler.cpp \
    connection/serialporthandler.cpp \
    connection/sockethandler.cpp \
    connection/socketport.cpp \
    connection/tcpport.cpp \
    connection/udpport.cpp \
    custom_dialogs/choosevaluetofollowdialog.cpp \
    custom_dialogs/comboboxdialog.cpp \
    custom_dialogs/connectiondialog.cpp \
    custom_dialogs/processdialog.cpp \
    custom_dialogs/settablesizedialog.cpp \
    custom_dialogs/valuedialog.cpp \
    custom_models/choosevaluemodel.cpp \
    custom_models/missionprogresstablemodel.cpp \
    custom_models/settingsmenulistmodel.cpp \
    custom_models/totalmessagestablemodel.cpp \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/helplines.cpp \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/marker.cpp \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/objloader.cpp \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/planroute.cpp \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/scene.cpp \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/startpoint.cpp \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/textrenderer.cpp \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/vehicle.cpp \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/vehiclepositiondisplaywidget.cpp \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/vehicleroute.cpp \
    custom_widgets/Main_tab_widgets/Vehicle_manual_control_widgets/vehiclemanualcontrolwidget.cpp \
    custom_widgets/Main_tab_widgets/Vehicle_manual_control_widgets/vehiclemanualcontrolwidget2.cpp \
    custom_widgets/Main_tab_widgets/displayattitudewidget.cpp \
    custom_widgets/Main_tab_widgets/messagestotalloggerwidget.cpp \
    custom_widgets/Main_tab_widgets/valuedisplaywidget.cpp \
    custom_widgets/Main_tab_widgets/valuedisplaywidgetunit.cpp \
    custom_widgets/Main_tab_widgets/vehiclesensorsinfowidget.cpp \
    custom_widgets/Main_widgets/connectionwidget.cpp \
    custom_widgets/Main_widgets/logerwidget.cpp \
    custom_widgets/Mission_planning_tab_widgets/missionplanitem.cpp \
    custom_widgets/Mission_planning_tab_widgets/missionplansetupwidget.cpp \
    custom_widgets/Mission_planning_tab_widgets/missionprogresswidget.cpp \
    custom_widgets/Mission_planning_tab_widgets/missiontable.cpp \
    custom_widgets/Settings_tab_widgets/Vehicle_param_settings_widgets/vehicleparamsettingswidget.cpp \
    custom_widgets/Settings_tab_widgets/Vehicle_param_settings_widgets/vehicleparamtableunit.cpp \
    custom_widgets/Settings_tab_widgets/settingsmenulistwidget.cpp \
    custom_widgets/Settings_tab_widgets/vehiclegeofencesettingswidget.cpp \
    custom_widgets/Settings_tab_widgets/vehicleothersettingswidget.cpp \
    custom_widgets/tabmodule.cpp \
    custom_widgets/vehicleparamchartwidget.cpp \
    customfilemanager.cpp \
    exceptions/cantreadwritefileexception.cpp \
    main.cpp \
    mainmodel.cpp \
    mainwindow.cpp \
    markermaphandler.cpp \
    taboverviewmodel.cpp \
    tabsettingsmodel.cpp \


HEADERS += \
    connectedvehicle.h \
    connection/connectionhandler.h \
    connection/genericport.h \
    connection/serialporthandler.h \
    connection/sockethandler.h \
    connection/socketport.h \
    connection/tcpport.h \
    connection/udpport.h \
    connectionhandler.h \
    custom_dialogs/ChooseValueToFollowDialog.h \
    custom_dialogs/comboboxdialog.h \
    custom_dialogs/connectiondialog.h \
    custom_dialogs/processdialog.h \
    custom_dialogs/settablesizedialog.h \
    custom_dialogs/valuedialog.h \
    custom_models/choosevaluemodel.h \
    custom_models/missionprogresstablemodel.h \
    custom_models/settingsmenulistmodel.h \
    custom_models/totalmessagestablemodel.h \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/helplines.h \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/marker.h \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/objloader.h \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/planroute.h \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/scene.h \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/startpoint.h \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/textrenderer.h \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/vehicle.h \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/vehiclepositiondisplaywidget.h \
    custom_widgets/Main_tab_widgets/Vehicle_display_widgets/vehicleroute.h \
    custom_widgets/Main_tab_widgets/Vehicle_manual_control_widgets/vehiclemanualcontrolwidget.h \
    custom_widgets/Main_tab_widgets/Vehicle_manual_control_widgets/vehiclemanualcontrolwidget2.h \
    custom_widgets/Main_tab_widgets/displayattitudewidget.h \
    custom_widgets/Main_tab_widgets/messagestotalloggerwidget.h \
    custom_widgets/Main_tab_widgets/valuedisplaywidget.h \
    custom_widgets/Main_tab_widgets/valuedisplaywidgetunit.h \
    custom_widgets/Main_tab_widgets/vehiclesensorsinfowidget.h \
    custom_widgets/Main_widgets/connectionwidget.h \
    custom_widgets/Main_widgets/logerwidget.h \
    custom_widgets/Mission_planning_tab_widgets/missionplanitem.h \
    custom_widgets/Mission_planning_tab_widgets/missionplansetupwidget.h \
    custom_widgets/Mission_planning_tab_widgets/missionprogresswidget.h \
    custom_widgets/Mission_planning_tab_widgets/missiontable.h \
    custom_widgets/Settings_tab_widgets/Vehicle_param_settings_widgets/vehicleparamsettingswidget.h \
    custom_widgets/Settings_tab_widgets/Vehicle_param_settings_widgets/vehicleparamtableunit.h \
    custom_widgets/Settings_tab_widgets/settingsmenulistwidget.h \
    custom_widgets/Settings_tab_widgets/vehiclegeofencesettingswidget.h \
    custom_widgets/Settings_tab_widgets/vehicleothersettingswidget.h \
    exceptions/cantreadwritefileexception.h \
    custom_widgets/tabmodule.h \
    custom_widgets/vehicleparamchartwidget.h \
    customfilemanager.h \
    customtab.h \
    mainmodel.h \
    mainwindow.h \
    markermaphandler.h \
    mavlink/minimal/mavlink.h \
    mavlink/minimal/mavlink_msg_heartbeat.h \
    mavlink/minimal/mavlink_msg_protocol_version.h \
    mavlink/minimal/minimal.h \
    mavlink/minimal/testsuite.h \
    mavlink/minimal/version.h \
    mavlink/standard/mavlink.h \
    mavlink/standard/standard.h \
    mavlink/standard/testsuite.h \
    mavlink/standard/version.h \
    positionStructs.h \
    structs.h \
    taboverviewmodel.h \
    tabsettingsmodel.h \

FORMS += \
    custom_dialogs/choosevaluetofollowdialog.ui \
    custom_dialogs/comboboxdialog.ui \
    custom_dialogs/connectiondialog.ui \
    custom_dialogs/processdialog.ui \
    custom_dialogs/settablesizedialog.ui \
    custom_dialogs/valuedialog.ui \
    mainwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    exceptions/1.txt \
    resources/blueStatusCircle.png \
    resources/greenStatusCircle.png \
    resources/greenStatusCirle.png \
    resources/orangeStatusCircle.png \
    resources/redStatusCircle.png
