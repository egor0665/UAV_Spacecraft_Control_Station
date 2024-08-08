#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QWidget>
#include <connection/connectionhandler.h>
#include <mavlink/ardupilotmega/mavlink.h>
#include <QTimer>
#include <custom_widgets/Main_widgets/connectionwidget.h>
#include "connectedvehicle.h"
#include "taboverviewmodel.h"
#include "tabsettingsmodel.h"
#include <QDialog>
#include <QMap>

class MainModel: public QWidget
{
    Q_OBJECT

    MavlinkMessages initMessages;
    QTimer updateCurrentVehicleMessagesTimer;

    QVector<ValueToFollow> currentVehicleValuesToFollow = {};


    int currentTabIndex = 0;
    QList<int> usedVehicleIds = {};
    QMap<int,ConnectedVehicle*> connectedVehicles = {};
    int currentVehicleId = -1;

    LogerWidget logerWidget;
    ConnectionWidget connectionWidget;
    QTabWidget mainTabWidget;

    QWidget tabMain, tabSettings; //, *tabPlanning;

    QHBoxLayout mainLayout;


    TabOverviewModel tabOverviewModel;
    TabSettingsModel tabSettingsModel;

    QSplitter connectionLogerSplitter;
    QSplitter mainRightSplitter;

public:
    MainModel(QWidget *parent = nullptr);
    ~MainModel();

    QHBoxLayout &getMainLayout();

protected:

    void newVehicleConnected(int newVehicleId);
    bool currentVehicleAvailable();
    void initConnectionWidget();
    void initTabOverviewModel();
    void initSplitterLayout();
    void initTabSettingsModel();
//    void initUpdateValueTimer();
    void initMainTab();
    int findAvailableId();
    bool vehicleAlreadyConnected(QString ipAddress, PortEnum connectionType, int portNum);
    bool connectVehicleToPort(int newVehicleId, ConnectedVehicle *newVehicle, QString ipAddress, PortEnum connectionType, int baudRate, int portNum);
    void initNewVehicle(ConnectedVehicle *newVehicle);
protected slots:

    void handleMavlinkMSGHeartbeatReceived(int vehicleId,mavlink_heartbeat_t message);
    void handleMavlinkMSGSysStatusReceived(int vehicleId,mavlink_sys_status_t message);
    void handleMavlinkMSGSysTimeReceived(int vehicleId,mavlink_system_time_t message);
    void handleMavlinkMSGAttitudeReceived(int vehicleId,mavlink_attitude_t message);


    void handleConnectSignal(QString ipAddress, PortEnum connectionType, int baudRate, int portNum);
    void handleDisconnectSignal(int vehicleId);
    void handleCurrentVehicleChanged(int vehicleId);

    void handleMavlinkMSG(int vehicleId,int messageId);
    void handleMavlinkMSGLocalPositionNEDReceived(int vehicleId,mavlink_local_position_ned_t message);
    void handleAllParamsReceived(int vehicleId, QMap<QString,AutoPilotValue> autopilotValues);
    void handleRefreshParams();
    void handleWriteParams(QVector<mavlink_param_value_t> valuesToChange);
    void handleTabIndexChanged(int index);

    //TABMAINMODEL
//    void handleTabMainModelMissionSetMode(int executeCommand, float x, float y, float z);
//    void handleTabMainModelSetMode(int mode);
//    void handleTabMainModelHome();
//    void handleTabMainModelSetMount(int mount);
//    void handleTabMainModelArm();
//    void handleTabMainModelDisarm();
//    void handleTabMainModelTakeOff(int altitude);
//    void handleTabMainModelLand();
//    void handleTabMainModelFlyToCords(float x, float z);
//    void handleTabMainModelFlyToAltCords(float x, float y, float z);
//    void handleTabMainModelAddWayPoint();
//    void handleTabMainModelSetHomeHere();

    void handleMavlinkMSGHomePositionReceived(int vehicleId,mavlink_home_position_t message);
//    void handleTabMainModelLogError(CantReadWriteFileException exception);
//    void handleTabMainModelWritePlanToVehicle(QVector<MissionPlanItem> planItems);
//    void handleUpdateMessagesTimer();
    void handleMissionAckReceived();
    void handleMavlinkMSGMissionItemReachedReceived(int vehicleId, mavlink_mission_item_reached_t missionItemReached);
};

#endif // MAINMODEL_H
