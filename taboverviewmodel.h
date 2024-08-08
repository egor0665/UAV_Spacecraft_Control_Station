#ifndef TABOVERVIEWMODEL_H
#define TABOVERVIEWMODEL_H

#include <custom_widgets/Main_tab_widgets/displayattitudewidget.h>
#include <custom_widgets/Main_tab_widgets/valuedisplaywidget.h>
//#include <custom_widgets/Main_tab_widgets/valuedisplaywidget.h>
//#include <custom_widgets/Main_tab_widgets/dronestatuswidget.h>
#include <custom_widgets/Main_tab_widgets/messagestotalloggerwidget.h>
#include <custom_widgets/Main_tab_widgets/Vehicle_manual_control_widgets/vehiclemanualcontrolwidget.h>
#include <custom_widgets/Main_tab_widgets/Vehicle_manual_control_widgets/vehiclemanualcontrolwidget2.h>
#include <custom_widgets/Main_tab_widgets/Vehicle_display_widgets/vehiclepositiondisplaywidget.h>
#include <custom_widgets/Main_tab_widgets/vehiclesensorsinfowidget.h>
#include <custom_widgets/Mission_planning_tab_widgets/missionplansetupwidget.h>
#include <custom_widgets/Mission_planning_tab_widgets/missionprogresswidget.h>

#include <customtab.h>
#include <markermaphandler.h>

class TabOverviewModel: public QWidget, public CustomTab
{
    Q_OBJECT
    VehicleManualControlWidget vehicleManualControlWidget;
    VehicleManualControlWidget2 vehicleManualControlWidget2;

    VehiclePositionDisplayWidget vehiclePositionDisplayWidget;
    VehicleSensorsInfoWidget vehicleSensorInfoWidget;
    MessagesTotalLoggerWidget messagesTotalLoggerWidget;
    DisplayAttitudeWidget displayAttitudeWidget;

    ValueDisplayWidget valueDisplayWidget;

    MissionPlanSetupWidget missionPlanSetupWidget;

    MissionProgressWidget missionProgressWidget;

//    ValueDisplayWidget valueDisplayWidget;

//    VehicleStatusWidget *vehicleStatusWidget;

    QTabWidget smallTabWidget;
    QTabWidget longTabWidget;
    QTabWidget highTabWidget;
    QTabWidget bigTabWidget;

    MarkerMapHandler markerMapHandler;

    QVector<MissionPlanItem> toSaveMissionPlan;

    QSplitter topWidgetSplitter;
    QSplitter bottomWidgetSplitter;
    QSplitter mainSplitter;
    QSplitter splitter4;

//    QWidget *tabMain, *tabSettings;



public:
    TabOverviewModel(QWidget *parent = nullptr);
    ~TabOverviewModel();

    void setCurrent(bool current);

    QGridLayout &getMainLayout();
    void handleMavlinkMSGHeartbeatReceived(mavlink_heartbeat_t message);
    void handleMavlinkMSGLocalPositionNEDReceived(mavlink_local_position_ned_t message);
    void handleMavlinkMSG(int messageId);
    void handleMavlinkMSGSysStatusReceived(mavlink_sys_status_t message);
    void handleMavlinkMSGAttitudeReceived(mavlink_attitude_t message);

    void handleMavlinkMSGHomePositionReceived(mavlink_home_position_t message);

    void saveMissionPlanToMissionProgressWidget();

    void updateCurrentMissionPlan(mavlink_mission_item_reached_t missionItemReached);
    void setValueDisplayWidgetValuesToFollow(QVector<ValueToFollow> valuesToFollow);
    void initValueDisplayWidget(QVector<ValueToFollow> currentVehicleValuesToFollow);
protected slots:

//    void handleManualControlWidgetMissionSetMode(int executeCommand, float x, float y, float z);
//    void handleManualControlWidgetSetMode(int mode);
//    void handleManualControlWidgetHome();
//    void handleManualControlWidgetSetMount(int mount);
//    void handleManualControlWidgetArm();
//    void handleManualControlWidgetDisarm();

//    void handleManualControlWidgetTakeOff(int altitude);
//    void handleManualControlWidgetLand();
//    void handleManualControlWidgetFlyToCords(float x, float z);
//    void handleManualControlWidgetFlyToAltCords(float x, float y, float z);
//    void handleManualControlWidgetAddWayPoint();
//    void handleManualControlWidgetSetHomeHere();
//    void handleLogError(CantReadWriteFileException exception);
//    void handleUpdateMissionPlanSetupWidgetUpdateVehicleDisplayMissionPlan(QVector<MissionPlanItem> planItems);
//    void handleMissionPlanSetupWidgetWritePlanToVehicle(QVector<MissionPlanItem>);
//    void handleMissionPlanSetupWidgetFormMarkerRoute(int endMarkerId, float distanceToMarker);
//    void handleMarkerMapHandlerVehicleDisplayWidgetSetMarkerMap(QVector<QVector<char>> markerMap, QVector<MarkerInfo> markerInfoVector);
signals:
    void tabMainModelLogError(CantReadWriteFileException exception);

    void tabMainModelMissionSetMode(int executeCommand, float x, float y, float z);
    void tabMainModelSetMode(int mode);
    void tabMainModelHome();
    void tabMainModelSetMount(int mount);
    void tabMainModelArm();
    void tabMainModelDisarm();
    void tabMainModelTakeOff(int altitude);
    void tabMainModelLand();
    void tabMainModelFlyToCords(float x, float z);
    void tabMainModelFlyToAltCords(float x, float y, float z);
    void tabMainModelAddWayPoint();
    void tabMainModelSetHomeHere();

    void tabMainModelWritePlanToVehicle(QVector<MissionPlanItem>);

protected:
    void initManualContolWidgetConnections();
    void initMissionPlanSetupWidgetConnections();
    void initUI();
};

#endif // TABOVERVIEWMODEL_H
