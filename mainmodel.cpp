#include "MainModel.h"

Q_DECLARE_METATYPE(float*)
Q_DECLARE_METATYPE(uint8_t*)
Q_DECLARE_METATYPE(int8_t*)
Q_DECLARE_METATYPE(uint16_t*)
Q_DECLARE_METATYPE(int16_t*)
Q_DECLARE_METATYPE(uint32_t*)
Q_DECLARE_METATYPE(int32_t*)
Q_DECLARE_METATYPE(uint64_t*)

QHBoxLayout &MainModel::getMainLayout()
{
    return mainLayout;
}

MainModel::MainModel(QWidget *parent)
    : QWidget(parent)
{
    initConnectionWidget();
    initTabOverviewModel();
    initTabSettingsModel();
    initSplitterLayout();
    initMainTab();
//    initUpdateValueTimer();
}
MainModel::~MainModel()
{
}

void MainModel::initConnectionWidget()
{
    connect(&connectionWidget, &ConnectionWidget::connectOnButtonPressed, this, &MainModel::handleConnectSignal);
    connect(&connectionWidget, &ConnectionWidget::disconnectOnButtonPressed, this, &MainModel::handleDisconnectSignal);
    connect(&connectionWidget, &ConnectionWidget::currentVehicleChanged, this, &MainModel::handleCurrentVehicleChanged);
}

void MainModel::initTabOverviewModel()
{
//    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelMissionSetMode, this, &MainModel::handleTabMainModelMissionSetMode);
//    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelSetMode, this, &MainModel::handleTabMainModelSetMode);
//    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelHome, this, &MainModel::handleTabMainModelHome);
//    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelSetMount, this, &MainModel::handleTabMainModelSetMount);
//    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelArm, this, &MainModel::handleTabMainModelArm);
//    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelDisarm, this, &MainModel::handleTabMainModelDisarm);
//    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelTakeOff, this, &MainModel::handleTabMainModelTakeOff);
//    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelLand, this, &MainModel::handleTabMainModelLand);
//    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelFlyToCords, this, &MainModel::handleTabMainModelFlyToCords);
//    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelFlyToAltCords, this, &MainModel::handleTabMainModelFlyToAltCords);
//    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelAddWayPoint, this, &MainModel::handleTabMainModelAddWayPoint);
//    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelSetHomeHere, this, &MainModel::handleTabMainModelSetHomeHere);
//    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelWritePlanToVehicle, this, &MainModel::handleTabMainModelWritePlanToVehicle);
//    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelLogError, this, &MainModel::handleTabMainModelLogError);
    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelMissionSetMode, this,
            [this] (int mode, float x, float y, float z){
        if (currentVehicleAvailable())
            connectedVehicles[currentVehicleId]->missionSetMode(mode,x,y,z);
    });
    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelSetMode, this,
            [this] (int mode)
    {
        if (currentVehicleAvailable())
            connectedVehicles[currentVehicleId]->sendSetMode(mode);
    });
    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelHome, this,
            [this] (){
        if (currentVehicleAvailable())
            connectedVehicles[currentVehicleId]->sendReturnHome();
    });
    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelSetMount, this,
            [this] (int mount){
        Q_UNUSED(mount)
    });
    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelArm, this,
            [this] (){
        if (currentVehicleAvailable())
            connectedVehicles[currentVehicleId]->sendArm(0);
    });
    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelDisarm, this,
            [this] (){
        if (currentVehicleAvailable())
            connectedVehicles[currentVehicleId]->sendDisarm(0);
    });
    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelTakeOff, this,
            [this] (int altitude)
    {
        if (currentVehicleAvailable())
            connectedVehicles[currentVehicleId]->sendTakeOff(altitude);
    });
    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelLand, this,
            [this] (){
        if (currentVehicleAvailable())
            connectedVehicles[currentVehicleId]->sendLand();
    });
    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelFlyToCords, this,
            [this] (float x, float z)
    {
        if (currentVehicleAvailable())
            connectedVehicles[currentVehicleId]->sendSetPositionTargetLocalNEDXZ(x,z);
    });
    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelFlyToAltCords, this,
            [this] (float x, float y, float z)
    {
        if (currentVehicleAvailable())
            connectedVehicles[currentVehicleId]->sendSetPositionTargetLocalNEDXYZ(x,y,z);
    });
    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelAddWayPoint, this,
            [this] (){
        ;
    });
    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelSetHomeHere, this,
            [this] (){
        if (currentVehicleAvailable())
            connectedVehicles[currentVehicleId]->sendSetHomeHere();
    });
    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelWritePlanToVehicle,
            [this] (QVector<MissionPlanItem> planItems)
    {
        if (currentVehicleAvailable())
            connectedVehicles[currentVehicleId]->writePlanToVehicle(planItems);
    });
    connect(&tabOverviewModel, &TabOverviewModel::tabMainModelLogError, this,
            [this] (CantReadWriteFileException exception)
    {
        logerWidget.addLog(QTime::currentTime(),WARNING_MESSAGE_TYPE, exception.getText());
    });

    tabMain.setLayout(&tabOverviewModel.getMainLayout());
    currentVehicleValuesToFollow = formMessageLinksStructure(&initMessages);
    tabOverviewModel.initValueDisplayWidget(currentVehicleValuesToFollow);
}

void MainModel::initTabSettingsModel()
{
    connect(&tabSettingsModel, &TabSettingsModel::writeParams,this,
            [this](QVector<mavlink_param_value_t> valuesToChange){
        if (currentVehicleAvailable())
            connectedVehicles[currentVehicleId]->writeParams(valuesToChange);
    });
    connect(&tabSettingsModel, &TabSettingsModel::refreshParams,this,
            [this](){
        if (currentVehicleAvailable())
            connectedVehicles[currentVehicleId]->refreshParams();

    });
    tabSettings.setLayout(&tabSettingsModel.getMainLayout());
}

void MainModel::initMainTab()
{
    connect(&mainTabWidget, &QTabWidget::currentChanged, this, &MainModel::handleTabIndexChanged);
    mainTabWidget.addTab(&tabMain,"Главная");
    mainTabWidget.addTab(&tabSettings,"Настройка");
}

void MainModel::initSplitterLayout()
{
    connectionLogerSplitter.setContentsMargins(0, 0, 0, 0);
    mainRightSplitter.setContentsMargins(0, 0, 0, 0);

    connectionLogerSplitter.addWidget(&connectionWidget);
    connectionLogerSplitter.addWidget(&logerWidget);
    connectionLogerSplitter.setOrientation(Qt::Vertical);
    mainRightSplitter.addWidget(&mainTabWidget);
    mainRightSplitter.addWidget(&connectionLogerSplitter);
    mainLayout.addWidget(&mainRightSplitter);
}

//void MainModel::initUpdateValueTimer()
//{
//    updateCurrentVehicleMessagesTimer.start(1000);
//    connect(&updateCurrentVehicleMessagesTimer, &QTimer::timeout,this, &MainModel::handleUpdateMessagesTimer);
//}

void MainModel::handleTabIndexChanged(int index)
{
    currentTabIndex = index;
    switch(index)
    {
    case 0:
    {
        tabOverviewModel.setCurrent(true);
        tabSettingsModel.setCurrent(false);
        break;
    }
    case 1:
    {
        tabOverviewModel.setCurrent(false);
        tabSettingsModel.setCurrent(true);
        break;
    }
    }
}

void MainModel::handleConnectSignal(QString ipAddress, PortEnum connectionType, int baudRate, int portNum)
{
    int newVehicleId = findAvailableId();
    if (vehicleAlreadyConnected(ipAddress, connectionType, portNum))
    {
         connectionWidget.onConnectStatusResult(false);
         return;
    }
    ConnectedVehicle *newVehicle = new ConnectedVehicle(newVehicleId, &logerWidget, this);
    bool connectedToPort = connectVehicleToPort(newVehicleId, newVehicle, ipAddress, connectionType, baudRate, portNum);
    connectionWidget.onConnectStatusResult(connectedToPort);
}

bool MainModel::connectVehicleToPort(int newVehicleId, ConnectedVehicle *newVehicle, QString ipAddress, PortEnum connectionType, int baudRate, int portNum)
{
    bool connectedToPort = newVehicle->connectToPort(ipAddress, connectionType, baudRate, portNum);
    if (connectedToPort)
    {
        connectedVehicles[newVehicleId] = newVehicle;
        usedVehicleIds.append(newVehicleId);
        newVehicleConnected(newVehicleId);
        initNewVehicle(newVehicle);
        currentVehicleId = newVehicleId;
    }
    else
    {
        delete (newVehicle);
    }
    return connectedToPort;
}

void MainModel::initNewVehicle(ConnectedVehicle *newVehicle)
{
    connect(newVehicle, &ConnectedVehicle::cantConnectTovehicle, this, &MainModel::handleDisconnectSignal);
    connect(newVehicle, &ConnectedVehicle::mavlinkMSGReceived, this, &MainModel::handleMavlinkMSG);
    connect(newVehicle, &ConnectedVehicle::mavlinkMSGHeartbeatReceived, this, &MainModel::handleMavlinkMSGHeartbeatReceived);
    connect(newVehicle, &ConnectedVehicle::mavlinkMSGSysStatusReceived, this, &MainModel::handleMavlinkMSGSysStatusReceived);
    connect(newVehicle, &ConnectedVehicle::mavlinkMSGSysTimeReceived, this, &MainModel::handleMavlinkMSGSysTimeReceived);
    connect(newVehicle, &ConnectedVehicle::mavlinkMSGAttitudeReceived, this, &MainModel::handleMavlinkMSGAttitudeReceived);
    connect(newVehicle, &ConnectedVehicle::mavlinkMSGLocalPositionNEDReceived, this, &MainModel::handleMavlinkMSGLocalPositionNEDReceived);
    connect(newVehicle, &ConnectedVehicle::mavlinkMSGHomePositionReceived, this, &MainModel::handleMavlinkMSGHomePositionReceived);
    connect(newVehicle, &ConnectedVehicle::missionAckReceived, this, &MainModel::handleMissionAckReceived);
    connect(newVehicle, &ConnectedVehicle::mavlinkMSGMissionItemReachedReceived, this, &MainModel::handleMavlinkMSGMissionItemReachedReceived);
    connect(newVehicle, &ConnectedVehicle::allParamsReceived, this, &MainModel::handleAllParamsReceived);
}

bool MainModel::vehicleAlreadyConnected(QString ipAddress, PortEnum connectionType, int portNum)
{
    QMap<int,ConnectedVehicle*>::iterator connectedVehicleIterator;
    for (connectedVehicleIterator = connectedVehicles.begin(); connectedVehicleIterator != connectedVehicles.end(); ++connectedVehicleIterator) {
        if (connectedVehicleIterator.value()->ipAddress == ipAddress &&
                connectedVehicleIterator.value()->connectionType == connectionType &&
                connectedVehicleIterator.value()->portNum == portNum)
        {
            return true;
        }
    }
    return false;
}

int MainModel::findAvailableId()
{
    int newVehicleId = -1;
    for (int i=0;i<usedVehicleIds.length()+1;i++)
            if (!usedVehicleIds.contains(i))
                newVehicleId = i;
    return newVehicleId;
}

//void MainModel::handleUpdateMessagesTimer()
//{
//    if (currentVehicleAvailable())
//    {
////        tabMainModel->updateValueDisplayWidget(connectedVehicles[currentVehicleId]->getCurrentMessages());
//    }
//}




void MainModel::handleWriteParams(QVector<mavlink_param_value_t> valuesToChange)
{
    if (currentVehicleAvailable())
        connectedVehicles[currentVehicleId]->writeParams(valuesToChange);
}

void MainModel::handleRefreshParams()
{
    if (currentVehicleAvailable())
        connectedVehicles[currentVehicleId]->refreshParams();
}

void MainModel::handleCurrentVehicleChanged(int vehicleId)
{
    currentVehicleId = vehicleId;
    if (currentVehicleId!=-1)
    {
        tabOverviewModel.setValueDisplayWidgetValuesToFollow(connectedVehicles[currentVehicleId]->getValuesToFollow());
    }
    else
    {
        tabOverviewModel.setValueDisplayWidgetValuesToFollow(currentVehicleValuesToFollow);
    }
}

void MainModel::handleMavlinkMSGMissionItemReachedReceived(int vehicleId, mavlink_mission_item_reached_t missionItemReached)
{
    if (vehicleId == currentVehicleId)
        tabOverviewModel.updateCurrentMissionPlan(missionItemReached);
}

void MainModel::handleMissionAckReceived()
{
    tabOverviewModel.saveMissionPlanToMissionProgressWidget();
}

void MainModel::newVehicleConnected(int newVehicleId)
{
    connectionWidget.addNewVehicleSetCurrent(newVehicleId, connectedVehicles[newVehicleId]->connectionType, connectedVehicles[newVehicleId]->ipAddress, connectedVehicles[newVehicleId]->portNum);
}

void MainModel::handleDisconnectSignal(int vehicleId)
{
    bool result = connectedVehicles[vehicleId]->connectionHandler->disconnectFromPort();
    if (result)
    {
        delete(connectedVehicles[vehicleId]);
        connectedVehicles.remove(vehicleId);
        usedVehicleIds.removeAll(vehicleId);
    }
    connectionWidget.onDisconnectStatusResult(vehicleId, result);
}

void MainModel::handleMavlinkMSGHeartbeatReceived(int vehicleId, mavlink_heartbeat_t message)
{
    if (vehicleId == currentVehicleId)
        tabOverviewModel.handleMavlinkMSGHeartbeatReceived(message);
}

void MainModel::handleAllParamsReceived(int vehicleId, QMap<QString,AutoPilotValue> autopilotValues)
{
    Q_UNUSED(vehicleId)
    // TODO CHECK
    tabSettingsModel.handleAllParamsReceived(autopilotValues);
}

void MainModel::handleMavlinkMSGLocalPositionNEDReceived(int vehicleId, mavlink_local_position_ned_t message)
{
    if (vehicleId == currentVehicleId)
        tabOverviewModel.handleMavlinkMSGLocalPositionNEDReceived(message);
}

void MainModel::handleMavlinkMSG(int vehicleId, int messageId)
{
    Q_UNUSED(vehicleId)
    // TODO CHECK
    tabOverviewModel.handleMavlinkMSG(messageId);
}

void MainModel::handleMavlinkMSGSysStatusReceived(int vehicleId, mavlink_sys_status_t message)
{
    if (vehicleId == currentVehicleId)
        tabOverviewModel.handleMavlinkMSGSysStatusReceived(message);
}

void MainModel::handleMavlinkMSGSysTimeReceived(int vehicleId, mavlink_system_time_t message)
{
    Q_UNUSED(vehicleId) Q_UNUSED(message)
    // TODO IMPLEMENT
}

void MainModel::handleMavlinkMSGAttitudeReceived(int vehicleId, mavlink_attitude_t message)
{
    if (vehicleId == currentVehicleId)
        tabOverviewModel.handleMavlinkMSGAttitudeReceived(message);
}

void MainModel::handleMavlinkMSGHomePositionReceived(int vehicleId, mavlink_home_position_t message)
{
    if (vehicleId == currentVehicleId)
        tabOverviewModel.handleMavlinkMSGHomePositionReceived(message);
}

bool MainModel::currentVehicleAvailable()
{
    return currentVehicleId!=-1;
}

//void MainModel::handleTabMainModelWritePlanToVehicle(QVector<MissionPlanItem> planItems)
//{
//    if (currentVehicleAvailable())
//        connectedVehicles[currentVehicleId]->writePlanToVehicle(planItems);
//}

//void MainModel::handleTabMainModelLogError(CantReadWriteFileException exception)
//{
//    logerWidget.addLog(QTime::currentTime(),WARNING_MESSAGE_TYPE, exception.getText());
//}

//void MainModel::handleTabMainModelMissionSetMode(int mode, float x, float y, float z)
//{
//    if (currentVehicleAvailable())
//        connectedVehicles[currentVehicleId]->missionSetMode(mode,x,y,z);
//}
//void MainModel::handleTabMainModelSetMode(int mode)
//{
//    if (currentVehicleAvailable())
//        connectedVehicles[currentVehicleId]->sendSetMode(mode);
//}
//void MainModel::handleTabMainModelHome()
//{
//    if (currentVehicleAvailable())
//        connectedVehicles[currentVehicleId]->sendReturnHome();
//}
//void MainModel::handleTabMainModelSetMount(int mount)
//{
//    Q_UNUSED(mount)
//    // TODO IMPLEMENT
//}
//void MainModel::handleTabMainModelArm()
//{
//    if (currentVehicleAvailable())
//        connectedVehicles[currentVehicleId]->sendArm(0);
//}

//void MainModel::handleTabMainModelDisarm()
//{
//    if (currentVehicleAvailable())
//        connectedVehicles[currentVehicleId]->sendDisarm(0);
//}
//void MainModel::handleTabMainModelTakeOff(int altitude)
//{
//    if (currentVehicleAvailable())
//        connectedVehicles[currentVehicleId]->sendTakeOff(altitude);
//}
//void MainModel::handleTabMainModelLand()
//{
//    if (currentVehicleAvailable())
//        connectedVehicles[currentVehicleId]->sendLand();
//}
//void MainModel::handleTabMainModelFlyToCords(float x, float z)
//{
//    if (currentVehicleAvailable())
//        connectedVehicles[currentVehicleId]->sendSetPositionTargetLocalNEDXZ(x,z);
//}
//void MainModel::handleTabMainModelFlyToAltCords(float x, float y, float z)
//{
//    if (currentVehicleAvailable())
//        connectedVehicles[currentVehicleId]->sendSetPositionTargetLocalNEDXYZ(x,y,z);
//}
//void MainModel::handleTabMainModelAddWayPoint()
//{

//}
//void MainModel::handleTabMainModelSetHomeHere()
//{
//    if (currentVehicleAvailable())
//        connectedVehicles[currentVehicleId]->sendSetHomeHere();
//}
