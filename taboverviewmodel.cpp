#include "taboverviewmodel.h"

TabOverviewModel::TabOverviewModel(QWidget *parent) : QWidget(parent)
{
    initUI();
    initManualContolWidgetConnections();
    initMissionPlanSetupWidgetConnections();

    connect(&markerMapHandler,&MarkerMapHandler::markerMapHandlerVehicleDisplayWidgetSetMarkerMap, this,
            [&](QVector<QVector<char>> markerMap, QVector<MarkerInfo> markerInfoVector)
    {
        vehiclePositionDisplayWidget.setMarkerMap(markerMap,markerInfoVector);
        missionPlanSetupWidget.updateMarkerIdSpinBox(markerInfoVector.length());
    });

    markerMapHandler.formMarkerMap();
}

TabOverviewModel::~TabOverviewModel()
{
}

void TabOverviewModel::initUI()
{
    smallTabWidget.setContentsMargins(0, 0, 0, 0);
    smallTabWidget.setMinimumHeight(200);
    smallTabWidget.setMinimumWidth(400);

    longTabWidget.setMinimumHeight(200);

    highTabWidget.setMinimumWidth(400);
    highTabWidget.setMinimumHeight(300);

    bigTabWidget.setMinimumWidth(550);
    bigTabWidget.setMinimumHeight(300);

    longTabWidget.addTab(&valueDisplayWidget, "Позиция");
    longTabWidget.addTab(&missionPlanSetupWidget, "Настройки миссии");

    highTabWidget.addTab(&vehicleSensorInfoWidget,"Подсистемы");
    highTabWidget.addTab(&messagesTotalLoggerWidget,"Сообщения");
    highTabWidget.addTab(&missionProgressWidget,"Статус миссии");

    bigTabWidget.addTab(&vehiclePositionDisplayWidget,"Положение");

    smallTabWidget.addTab(&vehicleManualControlWidget, "Ручное управление");
    smallTabWidget.addTab(&vehicleManualControlWidget2, "Ручное управление 2");

    topWidgetSplitter.setContentsMargins(0, 0, 0, 0);
    bottomWidgetSplitter.setContentsMargins(0, 0, 0, 0);
    mainSplitter.setContentsMargins(0, 0, 0, 0);

    topWidgetSplitter.addWidget(&smallTabWidget);
    topWidgetSplitter.addWidget(&longTabWidget);
    bottomWidgetSplitter.addWidget(&highTabWidget);
    bottomWidgetSplitter.addWidget(&bigTabWidget);
    mainSplitter.addWidget(&topWidgetSplitter);
    mainSplitter.addWidget(&bottomWidgetSplitter);
    mainSplitter.setOrientation(Qt::Vertical);

    mainLayout.addWidget(&mainSplitter,0,0);
}

void TabOverviewModel::initManualContolWidgetConnections()
{
//    connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetMissionSetMode, this, &TabOverviewModel::handleManualControlWidgetMissionSetMode);
//    connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetSetMode, this, &TabOverviewModel::handleManualControlWidgetSetMode);
//    connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetHome, this, &TabOverviewModel::handleManualControlWidgetHome);
//    connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetSetMount, this, &TabOverviewModel::handleManualControlWidgetSetMount);
//    connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetArm, this, &TabOverviewModel::handleManualControlWidgetArm);
//    connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetDisarm, this, &TabOverviewModel::handleManualControlWidgetDisarm);
//    connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetTakeOff, this, &TabOverviewModel::handleManualControlWidgetTakeOff);
//    connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetLand, this, &TabOverviewModel::handleManualControlWidgetLand);
//    connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetFlyToCords, this, &TabOverviewModel::handleManualControlWidgetFlyToCords);
//    connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetFlyToAltCords, this, &TabOverviewModel::handleManualControlWidgetFlyToAltCords);
//    connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetAddWayPoint, this, &TabOverviewModel::handleManualControlWidgetAddWayPoint);
//    connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetSetHomeHere, this, &TabOverviewModel::handleManualControlWidgetSetHomeHere);
        connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetMissionSetMode, this,
                [this](int mode, float x, float y, float z){
            emit tabMainModelMissionSetMode(mode, x, y, z);
            if (mode == MAV_GOTO_HOLD_AT_CURRENT_POSITION || mode == MAV_GOTO_HOLD_AT_SPECIFIED_POSITION)
                missionProgressWidget.startMissionTimeCount();
            else
                missionProgressWidget.stopMissionTimeCount();
        });

        connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetSetMode, this,
                [this](int mode){
            emit tabMainModelSetMode(mode);
            if (mode == MAV_MODE_AUTO)
                missionProgressWidget.startMissionTimeCount();
            else
                missionProgressWidget.stopMissionTimeCount();
        });

        connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetHome, this,
                [this](){
             emit tabMainModelHome();
        });

        connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetSetMount, this,
                [this](int mount){
            emit tabMainModelSetMount(mount);
        });

        connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetArm,this,
                [this](){
            emit tabMainModelArm();
        });

        connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetDisarm, this,
                [this](){
            emit tabMainModelDisarm();
        });

        connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetTakeOff, this,
                [this](int altitude){
            // INT -> FLOAT
            emit tabMainModelTakeOff(altitude);
        });

        connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetLand, this,
                [this](){
            emit tabMainModelLand();
        });

        connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetFlyToCords, this,
                [this](float x, float z){
            emit tabMainModelFlyToCords(x,z);
        });

        connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetFlyToAltCords, this,
                [this](float x, float y, float z){
            emit tabMainModelFlyToAltCords(x, y, z);
        });

        connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetAddWayPoint, this,
                [this](){
            emit tabMainModelAddWayPoint();
        });

        connect(&vehicleManualControlWidget, &VehicleManualControlWidget::manualControlWidgetSetHomeHere, this,
                [this](){
            emit tabMainModelSetHomeHere();
        });
}

void TabOverviewModel::initMissionPlanSetupWidgetConnections()
{
//    connect(&missionPlanSetupWidget, &MissionPlanSetupWidget::logError, this, &TabOverviewModel::handleLogError);
//    connect(&missionPlanSetupWidget, &MissionPlanSetupWidget::missionPlanSetupWidgetUpdateVehicleDisplayMissionPlan, this, &TabOverviewModel::handleUpdateMissionPlanSetupWidgetUpdateVehicleDisplayMissionPlan);
//    connect(&missionPlanSetupWidget, &MissionPlanSetupWidget::missionPlanSetupWidgetWritePlanToVehicle, this, &TabOverviewModel::handleMissionPlanSetupWidgetWritePlanToVehicle);
//    connect(&missionPlanSetupWidget, &MissionPlanSetupWidget::missionPlanSetupWidgetFormMarkerRoute, this, &TabOverviewModel::handleMissionPlanSetupWidgetFormMarkerRoute);
    connect(&missionPlanSetupWidget, &MissionPlanSetupWidget::logError, this,
            [this](CantReadWriteFileException exception)
    {
        emit tabMainModelLogError(exception);
    });

    connect(&missionPlanSetupWidget, &MissionPlanSetupWidget::missionPlanSetupWidgetUpdateVehicleDisplayMissionPlan, this,
            [this](QVector<MissionPlanItem> planItems)
    {
        vehiclePositionDisplayWidget.updateMissionPlan(planItems);
    });

    connect(&missionPlanSetupWidget, &MissionPlanSetupWidget::missionPlanSetupWidgetWritePlanToVehicle, this,
            [this](QVector<MissionPlanItem> planItems)
    {
        emit tabMainModelWritePlanToVehicle(planItems);
        toSaveMissionPlan = planItems;
    });

    connect(&missionPlanSetupWidget, &MissionPlanSetupWidget::missionPlanSetupWidgetFormMarkerRoute, this,
            [this](int endMarkerId, float distanceToMarker)
    {
        AttitudeInfo vehicleAttitude = vehiclePositionDisplayWidget.getVehicleAttitude();

        QVector<MissionPlanItem> newPlan = markerMapHandler.formMarkerRoute(vehicleAttitude.x, vehicleAttitude.y, vehicleAttitude.z, endMarkerId, distanceToMarker);
        vehiclePositionDisplayWidget.updateMissionPlan(newPlan);
        missionPlanSetupWidget.updatePlan(newPlan);
    });
}

void TabOverviewModel::initValueDisplayWidget(QVector <ValueToFollow> currentVehicleValuesToFollow)
{
    valueDisplayWidget.init(currentVehicleValuesToFollow);
}

void TabOverviewModel::setValueDisplayWidgetValuesToFollow(QVector<ValueToFollow> valuesToFollow)
{
    valueDisplayWidget.setValuesToFollow(valuesToFollow);
}

void TabOverviewModel::setCurrent(bool current)
{
    isCurrentTab = current;
    vehiclePositionDisplayWidget.setSleep(!current);
    vehicleSensorInfoWidget.setSleep(!current);
    messagesTotalLoggerWidget.setSleep(!current);
    displayAttitudeWidget.setSleep(!current);
}

void TabOverviewModel::handleMavlinkMSGHeartbeatReceived(mavlink_heartbeat_t message)
{
    vehiclePositionDisplayWidget.updateHeartBeat(message);
}

void TabOverviewModel::handleMavlinkMSGLocalPositionNEDReceived(mavlink_local_position_ned_t message)
{
    vehiclePositionDisplayWidget.setPosition(message.x, message.y, message.z);
}

void TabOverviewModel::handleMavlinkMSG(int messageId)
{
    messagesTotalLoggerWidget.newMessageReceived(messageId);
}

void TabOverviewModel::handleMavlinkMSGSysStatusReceived(mavlink_sys_status_t message)
{
    vehicleSensorInfoWidget.updateSysStatus(message);
}

void TabOverviewModel::handleMavlinkMSGAttitudeReceived(mavlink_attitude_t message)
{
    displayAttitudeWidget.updateData(message);
    vehiclePositionDisplayWidget.updatePosition(message);
}

void TabOverviewModel::handleMavlinkMSGHomePositionReceived(mavlink_home_position_t message)
{
    vehiclePositionDisplayWidget.updateHomePosition(message);
}

void TabOverviewModel::saveMissionPlanToMissionProgressWidget()
{
    missionProgressWidget.setPlan(toSaveMissionPlan);
}

void TabOverviewModel::updateCurrentMissionPlan(mavlink_mission_item_reached_t missionItemReached)
{
    missionProgressWidget.updateMissionProgress(missionItemReached);
}


QGridLayout &TabOverviewModel::getMainLayout()
{
    return mainLayout;
}



//void TabOverviewModel::handleMarkerMapHandlerVehicleDisplayWidgetSetMarkerMap(QVector<QVector<char>> markerMap, QVector<MarkerInfo> markerInfoVector)
//{
//    vehiclePositionDisplayWidget.setMarkerMap(markerMap,markerInfoVector);
//    missionPlanSetupWidget.updateMarkerIdSpinBox(markerInfoVector.length());
//}


//void TabOverviewModel::handleMissionPlanSetupWidgetFormMarkerRoute(int endMarkerId, float distanceToMarker)
//{
//    AttitudeInfo vehicleAttitude = vehiclePositionDisplayWidget.getVehicleAttitude();

//    QVector<MissionPlanItem> newPlan = markerMapHandler.formMarkerRoute(vehicleAttitude.x, vehicleAttitude.y, vehicleAttitude.z, endMarkerId, distanceToMarker);
//    vehiclePositionDisplayWidget.updateMissionPlan(newPlan);
//    missionPlanSetupWidget.updatePlan(newPlan);
//}


//void TabOverviewModel::handleMissionPlanSetupWidgetWritePlanToVehicle(QVector<MissionPlanItem> planItems)
//{
//    emit tabMainModelWritePlanToVehicle(planItems);
//    toSaveMissionPlan = planItems;
//}

//void TabOverviewModel::handleUpdateMissionPlanSetupWidgetUpdateVehicleDisplayMissionPlan(QVector<MissionPlanItem> planItems)
//{
//    vehiclePositionDisplayWidget.updateMissionPlan(planItems);
//}

//void TabOverviewModel::handleLogError(CantReadWriteFileException exception)
//{
//    emit tabMainModelLogError(exception);
//}

//void TabOverviewModel::handleManualControlWidgetMissionSetMode(int mode, float x, float y, float z)
//{
//    emit tabMainModelMissionSetMode(mode, x, y, z);
//    if (mode == MAV_GOTO_HOLD_AT_CURRENT_POSITION || mode == MAV_GOTO_HOLD_AT_SPECIFIED_POSITION)
//        missionProgressWidget.startMissionTimeCount();
//    else
//        missionProgressWidget.stopMissionTimeCount();
//}

//void TabOverviewModel::handleManualControlWidgetSetMode(int mode)
//{
//    emit tabMainModelSetMode(mode);
//    if (mode == MAV_MODE_AUTO)
//        missionProgressWidget.startMissionTimeCount();
//    else
//        missionProgressWidget.stopMissionTimeCount();

//}

//void TabOverviewModel::handleManualControlWidgetHome()
//{
//    emit tabMainModelHome();
//}
//void TabOverviewModel::handleManualControlWidgetSetMount(int mount)
//{
//    emit tabMainModelSetMount(mount);
//}
//void TabOverviewModel::handleManualControlWidgetArm()
//{
//    emit tabMainModelArm();
//}
//void TabOverviewModel::handleManualControlWidgetDisarm()
//{
//    emit tabMainModelDisarm();
//}
//void TabOverviewModel::handleManualControlWidgetTakeOff(int altitude)
//{
//    emit tabMainModelTakeOff(altitude);
//}
//void TabOverviewModel::handleManualControlWidgetLand()
//{
//    emit tabMainModelLand();
//}
//void TabOverviewModel::handleManualControlWidgetFlyToCords(float x, float z)
//{
//    emit tabMainModelFlyToCords(x,z);
//}
//void TabOverviewModel::handleManualControlWidgetFlyToAltCords(float x, float y, float z)
//{
//    emit tabMainModelFlyToAltCords(x,y,z);
//}
//void TabOverviewModel::handleManualControlWidgetAddWayPoint()
//{
//    emit tabMainModelAddWayPoint();
//}
//void TabOverviewModel::handleManualControlWidgetSetHomeHere()
//{
//    emit tabMainModelSetHomeHere();
//}
