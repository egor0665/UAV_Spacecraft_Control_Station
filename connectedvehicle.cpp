#include "connectedvehicle.h"
#include "structs.h"

// =================================================================================================================================================================================================================
// =================================================================================== CON / DE STRUCTORS ==========================================================================================================
// =================================================================================================================================================================================================================


const MavlinkMessages &ConnectedVehicle::getCurrentMessages() const
{
    return currentMessages;
}

ConnectedVehicle::ConnectedVehicle(int vehicleId, LogerWidget *logerWidget, QObject *parent) : QObject(parent)
{
    this->vehicleId = vehicleId;
    this->logerWidget = logerWidget;
    connectionHandler = new ConnectionHandler(this,logerWidget);
    connect(connectionHandler, &ConnectionHandler::newMessageReceived, this, &ConnectedVehicle::handleNewMessage);

    connect(&ackTimer, &QTimer::timeout, this, &ConnectedVehicle::handleAckCommands);
    ackTimer.start(1000);

    startSendingHelloPackets();
    startConnectionProcess();
}


QVector<ValueToFollow> ConnectedVehicle::getValuesToFollow()
{

    QVector<ValueToFollow> valuesToFollow = formMessageLinksStructure(&currentMessages);
    return valuesToFollow;
}


ConnectedVehicle::~ConnectedVehicle()
{
    helloPacketTimer.stop();
    disconnect(&helloPacketTimer, &QTimer::timeout, this, &ConnectedVehicle::sendHelloPacket);
    delete(connectionHandler);
    if (connectionProcessDialog != nullptr)
        delete(connectionProcessDialog);
}

// =================================================================================================================================================================================================================
// =================================================================================== PHYS CONNECTION =============================================================================================================
// =================================================================================================================================================================================================================


bool ConnectedVehicle::connectToPort(QString ipAddress, PortEnum connectionType, int baudRate, int portNum)
{
    this->ipAddress = ipAddress;
    this->portNum = portNum;
    this->connectionType = connectionType;
    return connectionHandler->connectToPort(ipAddress, connectionType, baudRate, portNum);
}

// =================================================================================================================================================================================================================
// =================================================================================== VEHICLE CONNECTION ==========================================================================================================
// =================================================================================================================================================================================================================


void ConnectedVehicle::startSendingHelloPackets()
{
    connect(&helloPacketTimer, &QTimer::timeout, this, &ConnectedVehicle::sendHelloPacket);
    helloPacketTimer.start(1000);
}

void ConnectedVehicle::startConnectionProcess()
{
    inConnectionProgressStage1 = true;

    // tyt hz kak postavit' zavisimost' ot Object
    //connectionProcessDialog = new ProcessDialog(this);

    connectionProcessDialog = new ProcessDialog();
    connectionProcessDialog->show();
    connectionProcessDialog->updateStatus(0, "Ожидание Heartbeat");
    connect(connectionProcessDialog, &ProcessDialog::closeButtonPressed, this, &ConnectedVehicle::stopConnection);
}

const int MSG_ID_SYS_STATUS_INTERVAL            = 10000000;
const int MSG_ID_SYSTEM_TIME_INTERVAL           = 10000000;
const int MSG_ID_LOCAL_POSITION_NED_INTERVAL    = 100000;
const int MSG_ID_GLOBAL_POSITION_INT_INTERVAL   = 1000000;
const int MSG_ID_ATTITUDE_INTERVAL              = 500000;
const int MSG_ID_PARAM_VALUE_INTERVAL           = 5000;

void ConnectedVehicle::startVehicleInitStageOne()
{
    sendRequestMessageInterval(MAVLINK_MSG_ID_SYS_STATUS,MSG_ID_SYS_STATUS_INTERVAL);
//    sendRequestMessageInterval(MAVLINK_MSG_ID_SYSTEM_TIME,MSG_ID_SYSTEM_TIME_INTERVAL);
    sendRequestMessageInterval(MAVLINK_MSG_ID_LOCAL_POSITION_NED,MSG_ID_LOCAL_POSITION_NED_INTERVAL);
//    sendRequestMessageInterval(MAVLINK_MSG_ID_GLOBAL_POSITION_INT,MSG_ID_GLOBAL_POSITION_INT_INTERVAL);
    sendRequestMessageInterval(MAVLINK_MSG_ID_ATTITUDE,MSG_ID_ATTITUDE_INTERVAL);
    sendRequestMessageInterval(MAVLINK_MSG_ID_PARAM_VALUE,MSG_ID_PARAM_VALUE_INTERVAL);

    sendRequestMessage(MAVLINK_MSG_ID_AUTOPILOT_VERSION);
    sendRequestMessage(MAVLINK_MSG_ID_HOME_POSITION);

    inConnectionProgressStage2 = true;
    requestParams();
}


void ConnectedVehicle::requestParams()
{
    mavlink_message_t message;
    mavlink_param_request_list_t com = { 0 };
    com.target_system = 1;
    com.target_component = 1;
    mavlink_msg_param_request_list_encode(255, 230, &message, &com);
    int len = connectionHandler->writeMessage(message);
    qDebug()<<len;
}

void ConnectedVehicle::startVehicleInitStageTwo()
{
    inConnectionProgressStage1 = false;
    inConnectionProgressStage2 = false;
    inConnectionProgressStage3 = false;
    connectionProcessDialog->hide();
    disconnect(connectionProcessDialog, &ProcessDialog::closeButtonPressed, this, &ConnectedVehicle::stopConnection);
    delete (connectionProcessDialog);
    connectionProcessDialog = nullptr;
    emit allParamsReceived(vehicleId, autopilotValues);
}

void ConnectedVehicle::stopConnection()
{
    inConnectionProgressStage1 = false;
    inConnectionProgressStage2 = false;
    inConnectionProgressStage3 = false;
    connectionProcessDialog->hide();
    disconnect(connectionProcessDialog, &ProcessDialog::closeButtonPressed, this, &ConnectedVehicle::stopConnection);
    delete (connectionProcessDialog);
    emit cantConnectTovehicle(vehicleId);
}

// =================================================================================================================================================================================================================
// =================================================================================== SEND MESSAGE FUNCTIONS ======================================================================================================
// =================================================================================================================================================================================================================

void ConnectedVehicle::sendRequestMessageInterval(int messageId, int interval)
{
    mavlink_message_t message;
    mavlink_command_long_t com = { 0 };
    com.command = MAV_CMD_SET_MESSAGE_INTERVAL;
    com.param1 = messageId;
    com.param2 = interval;
    com.param7 = 2;
    com.target_system = 1;
    com.target_component = 1;
    mavlink_msg_command_long_encode(255, 230, &message, &com);
    addCommandToAckVectorAndExecute(message, MAV_CMD_SET_MESSAGE_INTERVAL);
//    int len = connectionHandler->writeMessage(message);
}


void ConnectedVehicle::sendRequestMessage(int messageId)
{
    mavlink_message_t message;
    mavlink_command_long_t com = { 0 };
    com.command = MAV_CMD_REQUEST_MESSAGE;
    com.param1 = messageId;
    com.param7 = 1;
    com.target_system = 1;
    com.target_component = 1;
    mavlink_msg_command_long_encode(255, 230, &message, &com);
//    int len = connectionHandler->writeMessage(message);
    addCommandToAckVectorAndExecute(message, MAV_CMD_REQUEST_MESSAGE);
}

void ConnectedVehicle::sendHelloPacket()
{
    mavlink_heartbeat_t msg = { 0 };
    msg.type = MAV_TYPE_GCS;
    msg.autopilot = MAV_AUTOPILOT_INVALID;
    msg.base_mode =  MAV_MODE_MANUAL_ARMED;
    msg.custom_mode = 0;
    msg.system_status = MAV_STATE_ACTIVE;
    msg.mavlink_version = currentMessages.heartbeat.mavlink_version;
    mavlink_message_t message;
    mavlink_msg_heartbeat_encode(255, 230, &message, &msg); //TODO CHANGE TO VARS
    int len = connectionHandler->writeMessage(message);

//    mavlink_command_long_t com;
//    com.target_system = 1;
//    com.target_component = 2;
//    com.command = MAV_CMD_CAN_FORWARD;
//    com.confirmation = 0;
//    com.param1 = 1;
//    com.param2 = 2;
//    com.param2 = 3;
//    com.param2 = 4;
//    com.param2 = 5;
//    com.param2 = 6;
//    com.param2 = 7;
//    mavlink_message_t message;
//    mavlink_msg_command_long_encode(255, 230, &message, &com);
//    connectionHandler->writeMessage(message);

}

void ConnectedVehicle::sendArm(int force)
{
    mavlink_command_long_t com = {0};
    com.target_system = 1;
    com.target_component = 1;
    com.command = MAV_CMD_COMPONENT_ARM_DISARM;
    com.confirmation = 0;
    com.param1 = 1;
    com.param2 = 0;
    mavlink_message_t message;
    mavlink_msg_command_long_encode(255, 230, &message, &com); //TODO CHANGE TO VARS
//    int len = connectionHandler->writeMessage(message);
    addCommandToAckVectorAndExecute(message, MAV_CMD_COMPONENT_ARM_DISARM);
}

void ConnectedVehicle::sendDisarm(int force)
{
    mavlink_command_long_t com = {0};
    com.target_system = 1;
    com.target_component = 1;
    com.command = MAV_CMD_COMPONENT_ARM_DISARM;
    com.confirmation = 0;
    com.param1 = 0;
    com.param2 = 0;
    mavlink_message_t message;
    mavlink_msg_command_long_encode(255, 230, &message, &com); //TODO CHANGE TO VARS
//    int len = connectionHandler->writeMessage(message);
    addCommandToAckVectorAndExecute(message, MAV_CMD_COMPONENT_ARM_DISARM);

}

void ConnectedVehicle::sendSetMode(int mode)
{
    mavlink_command_long_t com = {0};
    com.target_system = 1;
    com.target_component = 1;
    com.command = MAV_CMD_DO_SET_MODE;
    com.confirmation = 0;
    com.param1 = mode;
    com.param2 = 0;
    mavlink_message_t message;
    mavlink_msg_command_long_encode(255, 230, &message, &com); //TODO CHANGE TO VARS
//    int len = connectionHandler->writeMessage(message);
    addCommandToAckVectorAndExecute(message, MAV_CMD_DO_SET_MODE);
}

void ConnectedVehicle::sendTakeOff(int altitude)
{
    if (currentMode != MAV_MODE_GUIDED_ARMED)
        sendSetMode(MAV_MODE_GUIDED_ARMED);

    mavlink_command_long_t com2 = { 0 };
    com2.command = MAV_CMD_NAV_TAKEOFF;
    com2.param7 = altitude;
    mavlink_message_t message2;
    mavlink_msg_command_long_encode(255, 230, &message2, &com2); //TODO CHANGE TO VARS
//    int len = connectionHandler->writeMessage(message2);
    addCommandToAckVectorAndExecute(message2, MAV_CMD_NAV_TAKEOFF);
}

void ConnectedVehicle::sendLand()
{
    if (currentMode != MAV_MODE_GUIDED_ARMED)
        sendSetMode(MAV_MODE_GUIDED_ARMED);
    mavlink_command_long_t com = { 0 };
    com.command = MAV_CMD_NAV_LAND;
    com.param5 = 0;
    com.param6 = 0;
    mavlink_message_t message;
    mavlink_msg_command_long_encode(255, 230, &message, &com); //TODO CHANGE TO VARS
//    int len = connectionHandler->writeMessage(message);
    addCommandToAckVectorAndExecute(message, MAV_CMD_NAV_LAND);
}

void ConnectedVehicle::sendReturnHome()
{
//    if (currentMode != MAV_MODE_)
//        sendSetMode(MAV_MODE_RTL);

    mavlink_command_long_t com = {0};
    com.target_system = 1;
    com.target_component = 1;
    com.command = MAV_CMD_NAV_RETURN_TO_LAUNCH;
    com.confirmation = 0;
    mavlink_message_t message;
    mavlink_msg_command_long_encode(255, 230, &message, &com); //TODO CHANGE TO VARS
//    int len = connectionHandler->writeMessage(message);
    addCommandToAckVectorAndExecute(message, MAV_CMD_NAV_RETURN_TO_LAUNCH);
}

void ConnectedVehicle::sendSetHomeHere()
{
    mavlink_command_long_t com = {0};
    com.target_system = 1;
    com.target_component = 1;
    com.command = MAV_CMD_DO_SET_HOME;
    com.confirmation = 0;
    com.param1 = 1;
    mavlink_message_t message;
    mavlink_msg_command_long_encode(255, 230, &message, &com); //TODO CHANGE TO VARS
//    int len = connectionHandler->writeMessage(message);
    addCommandToAckVectorAndExecute(message, MAV_CMD_DO_SET_HOME);
}

void ConnectedVehicle::sendSetPositionTargetLocalNEDXYZ(float x, float y, float z)
{
    if (currentMode != MAV_MODE_GUIDED_ARMED)
        sendSetMode(MAV_MODE_GUIDED_ARMED);

    mavlink_set_position_target_local_ned_t com = {0};
    com.target_system = 1;
    com.target_component = 1;
    com.type_mask = 4088;
    com.coordinate_frame = MAV_FRAME_LOCAL_NED;
    com.x = x;
    com.y = y;
    com.z = z;
    mavlink_message_t message;
    mavlink_msg_set_position_target_local_ned_encode(255, 230, &message, &com); //TODO CHANGE TO VARS
    int len = connectionHandler->writeMessage(message);

}

void ConnectedVehicle::sendSetPositionTargetLocalNEDXZ(float x, float z)
{
    if (currentMode != MAV_MODE_GUIDED_ARMED)
        sendSetMode(MAV_MODE_GUIDED_ARMED);

    mavlink_set_position_target_local_ned_t com = {0};
    com.target_system = 1;
    com.target_component = 1;
    com.type_mask = 4088;
    com.coordinate_frame = MAV_FRAME_LOCAL_NED;
    com.x = x;
    com.y = currentMessages.localPositionNed.y;
    com.z = z;
    mavlink_message_t message;
    mavlink_msg_set_position_target_local_ned_encode(255, 230, &message, &com); //TODO CHANGE TO VARS
    int len = connectionHandler->writeMessage(message);

}

void ConnectedVehicle::writePlanToVehicle(QVector<MissionPlanItem> planItems)
{
    qDebug()<<"writing mission plan";
    missionPlanItemsToWrite = planItems;

    mavlink_mission_count_t com = {0};
    com.target_system = 1;
    com.target_component = 1;
    com.count = planItems.length();
    mavlink_message_t message;
    mavlink_msg_mission_count_encode(255, 230, &message, &com); //TODO CHANGE TO VARS
    int len = connectionHandler->writeMessage(message);


    for (int i=0;i<planItems.length();i++)
    {
        // tyt po horoshemy timeout
        qDebug()<<"writing mission item " + QString::number(currentMessages.globalPositionInt.lat) + " " +
                  QString::number(currentMessages.globalPositionInt.lon) + " " +
                  QString::number(currentMessages.globalPositionInt.alt);
        missionPlanItemsToWrite[i];

        mavlink_mission_item_int_t com = {0};
        com.target_system = 1;
        com.target_component = 1;
        com.seq = i;
        com.frame = 0; //missionPlanItemsToWrite[i]->frameType;
        qDebug() << QString::number(missionPlanItemsToWrite[i].missionItemType);
        com.command = missionPlanItemsToWrite[i].missionItemType;
        if (i == 0) com.current = 1;
        else com.current = 0;
        com.autocontinue = 1;
        com.param1 = missionPlanItemsToWrite[i].param1;
        com.param2 = missionPlanItemsToWrite[i].param2;
        com.param3 = missionPlanItemsToWrite[i].param3;
        com.param4 = missionPlanItemsToWrite[i].param4;
//        const float meterToDegMult = 8.9831e-6;
        com.x = missionPlanItemsToWrite[i].param5X; // * meterToDegMult + currentMessages.homePosition.latitude / 1e7 ;
        com.y = missionPlanItemsToWrite[i].param6Y; //* meterToDegMult + currentMessages.homePosition.longitude / 1e7;
        com.z = missionPlanItemsToWrite[i].param7Z; //+ currentMessages.homePosition.altitude;
//        qDebug()<< "x: " + QString::number(missionPlanItemsToWrite[i].param5X * meterToDegMult + currentMessages.homePosition.latitude);
//        qDebug()<< "y: " + QString::number( missionPlanItemsToWrite[i].param6Y * meterToDegMult + currentMessages.homePosition.longitude);
//        qDebug()<< "z: " + QString::number(missionPlanItemsToWrite[i].param7Z + currentMessages.homePosition.altitude);
        //        com.x = missionPlanItemsToWrite[i].param5X;
//        com.y = missionPlanItemsToWrite[i].param6Y;
//        com.z = missionPlanItemsToWrite[i].param7Z;
        mavlink_message_t message;
        mavlink_msg_mission_item_int_encode(255, 230, &message, &com); //TODO CHANGE TO VARS
        int len = connectionHandler->writeMessage(message);
    }
}

//currentMessages.homePosition.latitude
//currentMessages.homePosition.longitude
//currentMessages.homePosition.altitude


void ConnectedVehicle::sendCurrentMissionItem(int num)
{
    qDebug()<<"writing mission item " + QString::number(num);
    missionPlanItemsToWrite[num];

    mavlink_mission_item_int_t com = {0};
    com.target_system = 1;
    com.target_component = 1;
    com.seq = num;
    com.frame = missionPlanItemsToWrite[num].frameType;
    com.command = missionPlanItemsToWrite[num].missionItemType;
    if (num == 0) com.current = 1;
    else com.current = 0;
    com.autocontinue = 1;
    com.param1 = missionPlanItemsToWrite[num].param1;
    com.param2 = missionPlanItemsToWrite[num].param2;
    com.param3 = missionPlanItemsToWrite[num].param3;
    com.param4 = missionPlanItemsToWrite[num].param4;
    com.x = missionPlanItemsToWrite[num].param5X;
    com.y = missionPlanItemsToWrite[num].param6Y;
    com.z = missionPlanItemsToWrite[num].param7Z;
    mavlink_message_t message;
    mavlink_msg_mission_item_int_encode(255, 230, &message, &com); //TODO CHANGE TO VARS
    int len = connectionHandler->writeMessage(message);
}
// =================================================================================================================================================================================================================
// =================================================================================== MAIN MODEL FUNCS ============================================================================================================
// =================================================================================================================================================================================================================

void ConnectedVehicle::refreshParams()
{
    inConnectionProgressStage2 = true;
    connectionProcessDialog = new ProcessDialog();
    connectionProcessDialog->show();
    connectionProcessDialog->updateStatus(0, "Ожидание параметров");
    connect(connectionProcessDialog, &ProcessDialog::closeButtonPressed, this, &ConnectedVehicle::stopConnection);
    requestParams();
}

void ConnectedVehicle::writeParams(QVector<mavlink_param_value_t> paramsToChange)
{
    qDebug() << "azazazaz" << paramsToChange.length();
    for (int i=0;i<paramsToChange.length();i++)
    {
        mavlink_param_set_t msg = { 0 };
        msg.target_system = 1;
        msg.target_component = 1;
        for (int j = 0;j<16;j++)
            msg.param_id[j]=paramsToChange[i].param_id[j];
        msg.param_type = paramsToChange[i].param_type;
        msg.param_value = paramsToChange[i].param_value;
        mavlink_message_t message;
        mavlink_msg_param_set_encode(255, 230, &message, &msg); //TODO CHANGE TO VARS
        int len = connectionHandler->writeMessage(message);
    }
    // TODO ERROR HANDLER
}


void ConnectedVehicle::missionSetMode(int mode, float x, float y, float z)
{
    mavlink_command_long_t com = {0};
    com.target_system = 1;
    com.target_component = 1;
    com.command = MAV_CMD_OVERRIDE_GOTO;
    com.confirmation = 0;
    if (mode == MAV_GOTO_DO_CONTINUE){
        com.param1 = mode;
        com.param2 = 255;
    }
    else if (mode == MAV_GOTO_HOLD_AT_CURRENT_POSITION || mode == MAV_GOTO_HOLD_AT_SPECIFIED_POSITION){
        com.param1 = MAV_GOTO_DO_HOLD;
        com.param2 = mode;
        com.param5 = x;
        com.param6 = y;
        com.param7 = z;
    }
    mavlink_message_t message;
    mavlink_msg_command_long_encode(255, 230, &message, &com); //TODO CHANGE TO VARS
//    int len = connectionHandler->writeMessage(message);
    addCommandToAckVectorAndExecute(message, MAV_CMD_OVERRIDE_GOTO);
}
// =================================================================================================================================================================================================================
// =================================================================================== COMMAND ACKS ================================================================================================================
// =================================================================================================================================================================================================================

void ConnectedVehicle::addCommandToAckVectorAndExecute(mavlink_message_t message, int commandId)
{
    commandsToAck.append(CommandToAck(commandId, 0, message, QTime().currentTime()));
    connectionHandler->writeMessage(message);
}


void ConnectedVehicle::handleAckCommands()
{
//    QVector<int> commandIdsToRemove = {};
    for (int i=0;i<commandsToAck.length();i++)
    {
        qDebug()<<QString::number(commandsToAck[i].id);
        if (commandsToAck[i].timeStamp.secsTo(QTime().currentTime())>=3)
        {
            commandsToAck[i].seq ++;
            commandsToAck[i].timeStamp = QTime().currentTime();
            connectionHandler->writeMessage(commandsToAck[i].message);
            if (commandsToAck[i].seq >= 3)
            {
                logerWidget->addLog(QTime().currentTime(),WARNING_MESSAGE_TYPE, "Устройство не отвечает на команду " + QString::number(commandsToAck[i].id));
//                commandIdsToRemove.append(i);
                commandsToAck.remove(i);
            }
        }
    }
//    for (int i=0)
}


// =================================================================================================================================================================================================================
// =================================================================================== MAIN HANDLER ================================================================================================================
// =================================================================================================================================================================================================================


void ConnectedVehicle::handleNewMessage(mavlink_message_t message)
{
    currentMessages.sysId = message.sysid;
    currentMessages.compId = message.compid;
//    qDebug()<<"msg id = " + QString::number(currentMessages.msgId);
    emit mavlinkMSGReceived(vehicleId, message.msgid);
    switch (message.msgid)
    {
    case MAVLINK_MSG_ID_HEARTBEAT:
    {
        mavlink_msg_heartbeat_decode(&message, &(currentMessages.heartbeat));
        currentMode = currentMessages.heartbeat.custom_mode;
        emit mavlinkMSGHeartbeatReceived(vehicleId, currentMessages.heartbeat);
//        qDebug()<< "asdaf" + QString::number(currentMessages.heartbeat.autopilot)
//               << QString::number(currentMessages.heartbeat.base_mode )
//               << QString::number(currentMessages.heartbeat.custom_mode)
//               << QString::number(currentMessages.heartbeat.system_status)
//              << QString::number(currentMessages.heartbeat.type);
        if (inConnectionProgressStage1)
        {
            inConnectionProgressStage1 = false;
            startVehicleInitStageOne();
        }
        break;
    }
    case MAVLINK_MSG_ID_SYS_STATUS:
    {
        mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
        emit mavlinkMSGSysStatusReceived(vehicleId, currentMessages.sysStatus);
        break;
    }
    case MAVLINK_MSG_ID_SYSTEM_TIME:
    {
        mavlink_msg_system_time_decode(&message, &(currentMessages.systemTime));
        emit mavlinkMSGSysTimeReceived(vehicleId, currentMessages.systemTime);
        break;
    }
    case MAVLINK_MSG_ID_PING: {break;}
    case MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL:{break;}
    case MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK:{break;}
    case MAVLINK_MSG_ID_AUTH_KEY:{break;}
    case MAVLINK_MSG_ID_LINK_NODE_STATUS:{break;}
    case MAVLINK_MSG_ID_SET_MODE:{break;}
    case MAVLINK_MSG_ID_PARAM_REQUEST_READ:{break;}
    case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:{break;}
    case MAVLINK_MSG_ID_PARAM_VALUE:
    {
        mavlink_msg_param_value_decode(&message, &(currentMessages.paramValue));
        qDebug()<<currentMessages.paramValue.param_index << currentMessages.paramValue.param_count;
        autopilotValues[currentMessages.paramValue.param_id] = AutoPilotValue(currentMessages.paramValue.param_id,
                                                                              currentMessages.paramValue.param_index,
                                                                              QVariant(currentMessages.paramValue.param_value),
                                                                              currentMessages.paramValue.param_type);
        if (inConnectionProgressStage2)
        {
            if(currentMessages.paramValue.param_index%4 == 0)
                connectionProcessDialog->updateStatus((currentMessages.paramValue.param_index*100 / currentMessages.paramValue.param_count),
                                                    "Получен " + QString(currentMessages.paramValue.param_id));
            if (currentMessages.paramValue.param_index == (currentMessages.paramValue.param_count-1))
            {
                inConnectionProgressStage2 = false;
                startVehicleInitStageTwo();
            }
        }

        break;
    }
    case MAVLINK_MSG_ID_PARAM_SET:{break;}
    case MAVLINK_MSG_ID_GPS_RAW_INT:{break;}
    case MAVLINK_MSG_ID_GPS_STATUS:{break;}
    case MAVLINK_MSG_ID_SCALED_IMU: {break;}
    case MAVLINK_MSG_ID_RAW_IMU:{break;}
    case MAVLINK_MSG_ID_RAW_PRESSURE: {break;}
    case MAVLINK_MSG_ID_SCALED_PRESSURE: {break;}
    case MAVLINK_MSG_ID_ATTITUDE:
    {
        mavlink_msg_attitude_decode(&message, &(currentMessages.attitude));
        emit mavlinkMSGAttitudeReceived(vehicleId, currentMessages.attitude);
        break;
    }
    case MAVLINK_MSG_ID_ATTITUDE_QUATERNION: {break;}
    case MAVLINK_MSG_ID_LOCAL_POSITION_NED:
    {
        mavlink_msg_local_position_ned_decode(&message, &(currentMessages.localPositionNed));
        emit mavlinkMSGLocalPositionNEDReceived(vehicleId, currentMessages.localPositionNed);
        break;
    }
    case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
    {
        mavlink_msg_global_position_int_decode(&message, &(currentMessages.globalPositionInt));
        emit mavlinkMSGGlobalPositionIntReceived(vehicleId, currentMessages.globalPositionInt);
        break;
    }
    case MAVLINK_MSG_ID_RC_CHANNELS_SCALED: {break;}
    case MAVLINK_MSG_ID_RC_CHANNELS_RAW: {break;}
    case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW: {break;}
    case MAVLINK_MSG_ID_MISSION_REQUEST_PARTIAL_LIST:{break;}
    case MAVLINK_MSG_ID_MISSION_WRITE_PARTIAL_LIST: {break;}
    case MAVLINK_MSG_ID_MISSION_ITEM: {break;}
    case MAVLINK_MSG_ID_MISSION_REQUEST: {break;}
    case MAVLINK_MSG_ID_MISSION_SET_CURRENT: {break;}
    case MAVLINK_MSG_ID_MISSION_CURRENT: {break;}
    case MAVLINK_MSG_ID_MISSION_REQUEST_LIST: {break;}
    case MAVLINK_MSG_ID_MISSION_COUNT:
    {
        mavlink_msg_mission_count_decode(&message, &(currentMessages.missionCount));
//        emit mavlinkMSGLocalPositionNEDReceived(currentMessages.localPositionNed);
        qDebug() << "MISSION_COUNT " + QString::number(currentMessages.missionCount.count) ;
        break;
    }
    case MAVLINK_MSG_ID_MISSION_CLEAR_ALL: {break;}
    case MAVLINK_MSG_ID_MISSION_ITEM_REACHED: {
        mavlink_msg_mission_item_reached_decode(&message, &(currentMessages.missionItemReached));
        emit mavlinkMSGMissionItemReachedReceived(vehicleId, currentMessages.missionItemReached);
        break;
    }
    case MAVLINK_MSG_ID_MISSION_ACK:
    {
        mavlink_msg_mission_ack_decode(&message, &(currentMessages.missionAck));
        if (currentMessages.missionAck.type == MAV_MISSION_ACCEPTED)
            emit missionAckReceived();
        qDebug() << "MISSION_ACK " + QString::number(currentMessages.missionAck.type) ;
        break;
    }
    case MAVLINK_MSG_ID_SET_GPS_GLOBAL_ORIGIN: {break;}
    case MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN: {break;}
    case MAVLINK_MSG_ID_PARAM_MAP_RC: {break;}
    case MAVLINK_MSG_ID_MISSION_REQUEST_INT:
    {
        mavlink_msg_mission_request_int_decode(&message, &(currentMessages.missionRequestInt));
        qDebug() << "MISSION_REQUEST_INT " + QString::number(currentMessages.missionRequestInt.seq);

        sendCurrentMissionItem(currentMessages.missionRequestInt.seq);

        break;
    }
    case MAVLINK_MSG_ID_SAFETY_SET_ALLOWED_AREA: {break;}
    case MAVLINK_MSG_ID_SAFETY_ALLOWED_AREA: {break;}
    case MAVLINK_MSG_ID_ATTITUDE_QUATERNION_COV: {break;}
    case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT: {break;}
    case MAVLINK_MSG_ID_GLOBAL_POSITION_INT_COV: {break;}
    case MAVLINK_MSG_ID_LOCAL_POSITION_NED_COV: {break;}
    case MAVLINK_MSG_ID_RC_CHANNELS: {break;}
    case MAVLINK_MSG_ID_REQUEST_DATA_STREAM: //DEPRICATED
    {
        mavlink_request_data_stream_t msg;
        mavlink_msg_request_data_stream_decode(&message, &msg);
        qDebug()<<"request data stream. message rate " +
                  QString::number(msg.req_message_rate) +
                  " stream id " + QString::number(msg.req_stream_id) +
                  " start/stop " + QString::number(msg.start_stop) +
                  " comp/syst " + QString::number(msg.target_system) +
                  "/" +QString::number(msg.target_component);
        break;
    }
    case MAVLINK_MSG_ID_DATA_STREAM: {break;}
    case MAVLINK_MSG_ID_MANUAL_CONTROL: {break;}
    case MAVLINK_MSG_ID_RC_CHANNELS_OVERRIDE: {break;}
    case MAVLINK_MSG_ID_MISSION_ITEM_INT:
    {
        mavlink_msg_mission_item_int_decode(&message, &(currentMessages.missionItemInt));
        qDebug() << "MISSION_ITEM_INT " + QString::number(currentMessages.missionItemInt.command) ;
        break;
    }
    case MAVLINK_MSG_ID_VFR_HUD: {break;}
    case MAVLINK_MSG_ID_COMMAND_INT: {break;}
    case MAVLINK_MSG_ID_COMMAND_LONG: {break;}
    case MAVLINK_MSG_ID_COMMAND_ACK:
    {
        mavlink_command_ack_t msg;
        mavlink_msg_command_ack_decode(&message, &msg);

        // check if command is acked
        for(int i=0;i<commandsToAck.length();i++)
        {
            if (commandsToAck[i].id==msg.command)
            {
                switch(msg.result)
                {
                case (MAV_RESULT_ACCEPTED):{break;}
                case (MAV_RESULT_TEMPORARILY_REJECTED):{logerWidget->addLog(QTime().currentTime(), WARNING_MESSAGE_TYPE, ""); break;}
                case (MAV_RESULT_DENIED):{logerWidget->addLog(QTime().currentTime(), WARNING_MESSAGE_TYPE, "Невозможно выполнение команды в данный момент"); break;}
                case (MAV_RESULT_UNSUPPORTED):{logerWidget->addLog(QTime().currentTime(), WARNING_MESSAGE_TYPE, "Команда не поддерживается устройством"); break;}
                case (MAV_RESULT_FAILED):{logerWidget->addLog(QTime().currentTime(), WARNING_MESSAGE_TYPE, "Ошибка исполнения команды"); break;}
                case (MAV_RESULT_IN_PROGRESS):{logerWidget->addLog(QTime().currentTime(), SUCCESS_MESSAGE_TYPE, "Выполнение команды " + QString::number(msg.progress) + "%"); break;}
                case (MAV_RESULT_CANCELLED):{logerWidget->addLog(QTime().currentTime(), WARNING_MESSAGE_TYPE, "Команда отменена"); break;}
                case (MAV_RESULT_COMMAND_LONG_ONLY):{logerWidget->addLog(QTime().currentTime(), WARNING_MESSAGE_TYPE, "Неправильный формат отправки команды (Long only)"); break;}
                case (MAV_RESULT_COMMAND_INT_ONLY):{logerWidget->addLog(QTime().currentTime(), WARNING_MESSAGE_TYPE, "Неправильный формат отправки команды (Int only)"); break;}
                case (MAV_RESULT_COMMAND_UNSUPPORTED_MAV_FRAME):{logerWidget->addLog(QTime().currentTime(), WARNING_MESSAGE_TYPE, "Неверная система координат"); break;}
                }

                commandsToAck.remove(i);
                break;
            }
        }
        switch(msg.command)
        {
        case (MAV_CMD_DO_SET_HOME):
        {
            break;
        }
        default:
        {break;}
        }


        qDebug()<<"command ack. command id " +
                  QString::number(msg.command) +
                  " result " + QString::number(msg.result) +
                  " progress " + QString::number(msg.progress) +
                  " result param " + QString::number(msg.result_param2) +
                  "target system " +QString::number(msg.target_system);
        break;
    }
    case MAVLINK_MSG_ID_COMMAND_CANCEL: {break;}
    case MAVLINK_MSG_ID_MANUAL_SETPOINT: {break;}
    case MAVLINK_MSG_ID_SET_ATTITUDE_TARGET: {break;}
    case MAVLINK_MSG_ID_ATTITUDE_TARGET: {break;}
    case MAVLINK_MSG_ID_SET_POSITION_TARGET_LOCAL_NED: {break;}
    case MAVLINK_MSG_ID_POSITION_TARGET_LOCAL_NED: {break;}
    case MAVLINK_MSG_ID_SET_POSITION_TARGET_GLOBAL_INT: {break;}
    case MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT: {break;}
    case MAVLINK_MSG_ID_LOCAL_POSITION_NED_SYSTEM_GLOBAL_OFFSET: {break;}
    case MAVLINK_MSG_ID_HIL_STATE: {break;}
    case MAVLINK_MSG_ID_HIL_CONTROLS: {break;}
    case MAVLINK_MSG_ID_HIL_RC_INPUTS_RAW: {break;}
    case MAVLINK_MSG_ID_HIL_ACTUATOR_CONTROLS: {break;}
    case MAVLINK_MSG_ID_OPTICAL_FLOW: {break;}
    case MAVLINK_MSG_ID_GLOBAL_VISION_POSITION_ESTIMATE: {break;}
    case MAVLINK_MSG_ID_VISION_POSITION_ESTIMATE: {break;}
    case MAVLINK_MSG_ID_VISION_SPEED_ESTIMATE: {break;}
    case MAVLINK_MSG_ID_VICON_POSITION_ESTIMATE: {break;}
    case MAVLINK_MSG_ID_HIGHRES_IMU: {break;}
    case MAVLINK_MSG_ID_OPTICAL_FLOW_RAD: {break;}
    case MAVLINK_MSG_ID_HIL_SENSOR: {break;}
    case MAVLINK_MSG_ID_SIM_STATE: {break;}
    case MAVLINK_MSG_ID_RADIO_STATUS: {break;}
    case MAVLINK_MSG_ID_FILE_TRANSFER_PROTOCOL: {break;}
    case MAVLINK_MSG_ID_TIMESYNC: {break;}
    case MAVLINK_MSG_ID_CAMERA_TRIGGER: {break;}
    case MAVLINK_MSG_ID_HIL_GPS: {break;}
    case MAVLINK_MSG_ID_HIL_OPTICAL_FLOW: {break;}
    case MAVLINK_MSG_ID_HIL_STATE_QUATERNION: {break;}
    case MAVLINK_MSG_ID_SCALED_IMU2: {break;}
    case MAVLINK_MSG_ID_LOG_REQUEST_LIST: {break;}
    case MAVLINK_MSG_ID_LOG_ENTRY: {break;}
    case MAVLINK_MSG_ID_LOG_REQUEST_DATA: {break;}
    case MAVLINK_MSG_ID_LOG_DATA: {break;}
    case MAVLINK_MSG_ID_LOG_ERASE: {break;}
    case MAVLINK_MSG_ID_LOG_REQUEST_END: {break;}
    case MAVLINK_MSG_ID_GPS_INJECT_DATA: {break;}
    case MAVLINK_MSG_ID_GPS2_RAW: {break;}
    case MAVLINK_MSG_ID_POWER_STATUS: {break;}
    case MAVLINK_MSG_ID_SERIAL_CONTROL: {break;}
    case MAVLINK_MSG_ID_GPS_RTK: {break;}
    case MAVLINK_MSG_ID_GPS2_RTK: {break;}
    case MAVLINK_MSG_ID_SCALED_IMU3: {break;}
    case MAVLINK_MSG_ID_DATA_TRANSMISSION_HANDSHAKE: {break;}
    case MAVLINK_MSG_ID_ENCAPSULATED_DATA: {break;}
    case MAVLINK_MSG_ID_DISTANCE_SENSOR: {break;}
    case MAVLINK_MSG_ID_TERRAIN_REQUEST: {break;}
    case MAVLINK_MSG_ID_TERRAIN_DATA: {break;}
    case MAVLINK_MSG_ID_TERRAIN_CHECK: {break;}
    case MAVLINK_MSG_ID_TERRAIN_REPORT: {break;}
    case MAVLINK_MSG_ID_SCALED_PRESSURE2: {break;}
    case MAVLINK_MSG_ID_ATT_POS_MOCAP: {break;}
    case MAVLINK_MSG_ID_SET_ACTUATOR_CONTROL_TARGET: {break;}
    case MAVLINK_MSG_ID_ACTUATOR_CONTROL_TARGET: {break;}
    case MAVLINK_MSG_ID_ALTITUDE: {break;}
    case MAVLINK_MSG_ID_RESOURCE_REQUEST: {break;}
    case MAVLINK_MSG_ID_SCALED_PRESSURE3: {break;}
    case MAVLINK_MSG_ID_FOLLOW_TARGET: {break;}
    case MAVLINK_MSG_ID_CONTROL_SYSTEM_STATE: {break;}
    case MAVLINK_MSG_ID_BATTERY_STATUS: {break;}
    case MAVLINK_MSG_ID_AUTOPILOT_VERSION:
    {
        mavlink_msg_autopilot_version_decode(&message, &(currentMessages.autopilotVersion));
        qDebug()<<"autopilot version capabilities: " + QString::number(currentMessages.autopilotVersion.capabilities);
        break;
    }
    case MAVLINK_MSG_ID_LANDING_TARGET: {break;}
    case MAVLINK_MSG_ID_FENCE_STATUS: {break;}
    case MAVLINK_MSG_ID_MAG_CAL_REPORT: {break;}
    case MAVLINK_MSG_ID_EFI_STATUS: {break;}
    case MAVLINK_MSG_ID_ESTIMATOR_STATUS: {break;}
    case MAVLINK_MSG_ID_WIND_COV: {break;}
    case MAVLINK_MSG_ID_GPS_INPUT: {break;}
    case MAVLINK_MSG_ID_GPS_RTCM_DATA: {break;}
    case MAVLINK_MSG_ID_HIGH_LATENCY: {break;}
    case MAVLINK_MSG_ID_HIGH_LATENCY2: {break;}
    case MAVLINK_MSG_ID_VIBRATION: {break;}
    case MAVLINK_MSG_ID_HOME_POSITION:
    {
        mavlink_msg_home_position_decode(&message, &(currentMessages.homePosition));
        emit mavlinkMSGHomePositionReceived(vehicleId, currentMessages.homePosition);
        break;
    }
    case MAVLINK_MSG_ID_SET_HOME_POSITION: {break;}
    case MAVLINK_MSG_ID_MESSAGE_INTERVAL: {break;}
    case MAVLINK_MSG_ID_EXTENDED_SYS_STATE: {break;}
    case MAVLINK_MSG_ID_ADSB_VEHICLE: {break;}
    case MAVLINK_MSG_ID_COLLISION: {break;}
    case MAVLINK_MSG_ID_V2_EXTENSION: {break;}
    case MAVLINK_MSG_ID_MEMORY_VECT: {break;}
    case MAVLINK_MSG_ID_DEBUG_VECT: {break;}
    case MAVLINK_MSG_ID_NAMED_VALUE_FLOAT: {break;}
    case MAVLINK_MSG_ID_NAMED_VALUE_INT: {break;}
    case MAVLINK_MSG_ID_STATUSTEXT:
    {
        mavlink_statustext_t statusText;
        mavlink_msg_statustext_decode(&message, &statusText);
        qDebug()<<" statustext. severinity " + QString::number(statusText.severity)+ " text " + statusText.text;
        logerWidget->addLog(QTime().currentTime(), NORMAL_MESSAGE_TYPE, "Устройство (" + QString::number(vehicleId) + "): " +statusText.text);
        break;
    }
    case MAVLINK_MSG_ID_DEBUG: {break;}
    case MAVLINK_MSG_ID_SETUP_SIGNING: {break;}
    case MAVLINK_MSG_ID_BUTTON_CHANGE: {break;}
    case MAVLINK_MSG_ID_PLAY_TUNE: {break;}
    case MAVLINK_MSG_ID_CAMERA_INFORMATION: {break;}
    case MAVLINK_MSG_ID_CAMERA_SETTINGS: {break;}
    case MAVLINK_MSG_ID_STORAGE_INFORMATION: {break;}
    case MAVLINK_MSG_ID_CAMERA_CAPTURE_STATUS: {break;}
    case MAVLINK_MSG_ID_CAMERA_IMAGE_CAPTURED: {break;}
    case MAVLINK_MSG_ID_FLIGHT_INFORMATION: {break;}
    case MAVLINK_MSG_ID_MOUNT_ORIENTATION: {break;}
    case MAVLINK_MSG_ID_LOGGING_DATA: {break;}
    case MAVLINK_MSG_ID_LOGGING_DATA_ACKED: {break;}
    case MAVLINK_MSG_ID_LOGGING_ACK: {break;}
    case MAVLINK_MSG_ID_VIDEO_STREAM_INFORMATION: {break;}
    case MAVLINK_MSG_ID_VIDEO_STREAM_STATUS: {break;}
    case MAVLINK_MSG_ID_CAMERA_FOV_STATUS: {break;}
    case MAVLINK_MSG_ID_CAMERA_TRACKING_IMAGE_STATUS: {break;}
    case MAVLINK_MSG_ID_CAMERA_TRACKING_GEO_STATUS: {break;}
    case MAVLINK_MSG_ID_GIMBAL_MANAGER_INFORMATION: {break;}
    case MAVLINK_MSG_ID_GIMBAL_MANAGER_STATUS: {break;}
    case MAVLINK_MSG_ID_GIMBAL_MANAGER_SET_ATTITUDE: {break;}
    case MAVLINK_MSG_ID_GIMBAL_DEVICE_INFORMATION: {break;}
    case MAVLINK_MSG_ID_GIMBAL_DEVICE_SET_ATTITUDE: {break;}
    case MAVLINK_MSG_ID_GIMBAL_DEVICE_ATTITUDE_STATUS: {break;}
    case MAVLINK_MSG_ID_AUTOPILOT_STATE_FOR_GIMBAL_DEVICE: {break;}
    case MAVLINK_MSG_ID_GIMBAL_MANAGER_SET_PITCHYAW: {break;}
    case MAVLINK_MSG_ID_GIMBAL_MANAGER_SET_MANUAL_CONTROL: {break;}
    case MAVLINK_MSG_ID_ESC_INFO: {break;}
    case MAVLINK_MSG_ID_ESC_STATUS: {break;}
    case MAVLINK_MSG_ID_WIFI_CONFIG_AP: {break;}
    case MAVLINK_MSG_ID_AIS_VESSEL: {break;}
    case MAVLINK_MSG_ID_UAVCAN_NODE_STATUS: {break;}
    case MAVLINK_MSG_ID_UAVCAN_NODE_INFO: {break;}
    case MAVLINK_MSG_ID_PARAM_EXT_REQUEST_READ: {break;}
    case MAVLINK_MSG_ID_PARAM_EXT_REQUEST_LIST: {break;}
    case MAVLINK_MSG_ID_PARAM_EXT_VALUE: {break;}
    case MAVLINK_MSG_ID_PARAM_EXT_SET: {break;}
    case MAVLINK_MSG_ID_PARAM_EXT_ACK: {break;}
    case MAVLINK_MSG_ID_OBSTACLE_DISTANCE: {break;}
    case MAVLINK_MSG_ID_ODOMETRY: {break;}
    case MAVLINK_MSG_ID_TRAJECTORY_REPRESENTATION_WAYPOINTS: {break;}
    case MAVLINK_MSG_ID_TRAJECTORY_REPRESENTATION_BEZIER: {break;}
    case MAVLINK_MSG_ID_CELLULAR_STATUS: {break;}
    case MAVLINK_MSG_ID_ISBD_LINK_STATUS: {break;}
    case MAVLINK_MSG_ID_CELLULAR_CONFIG: {break;}
    case MAVLINK_MSG_ID_RAW_RPM: {break;}
    case MAVLINK_MSG_ID_UTM_GLOBAL_POSITION: {break;}
    case MAVLINK_MSG_ID_DEBUG_FLOAT_ARRAY: {break;}
    case MAVLINK_MSG_ID_ORBIT_EXECUTION_STATUS: {break;}
    case MAVLINK_MSG_ID_SMART_BATTERY_INFO: {break;}
    case MAVLINK_MSG_ID_GENERATOR_STATUS: {break;}
    case MAVLINK_MSG_ID_ACTUATOR_OUTPUT_STATUS: {break;}
    case MAVLINK_MSG_ID_TIME_ESTIMATE_TO_TARGET: {break;}
    case MAVLINK_MSG_ID_TUNNEL: {break;}
    case MAVLINK_MSG_ID_CAN_FRAME: {break;}
    case MAVLINK_MSG_ID_ONBOARD_COMPUTER_STATUS: {break;}
    case MAVLINK_MSG_ID_COMPONENT_INFORMATION: {break;}
    case MAVLINK_MSG_ID_COMPONENT_METADATA: {break;}
    case MAVLINK_MSG_ID_PLAY_TUNE_V2: {break;}
    case MAVLINK_MSG_ID_SUPPORTED_TUNES: {break;}
    case MAVLINK_MSG_ID_EVENT: {break;}
    case MAVLINK_MSG_ID_CURRENT_EVENT_SEQUENCE: {break;}
    case MAVLINK_MSG_ID_REQUEST_EVENT: {break;}
    case MAVLINK_MSG_ID_RESPONSE_EVENT_ERROR: {break;}
    case MAVLINK_MSG_ID_CANFD_FRAME: {break;}
    case MAVLINK_MSG_ID_CAN_FILTER_MODIFY: {break;}
    case MAVLINK_MSG_ID_WHEEL_DISTANCE: {break;}
    case MAVLINK_MSG_ID_WINCH_STATUS: {break;}
    case MAVLINK_MSG_ID_OPEN_DRONE_ID_BASIC_ID: {break;}
    case MAVLINK_MSG_ID_OPEN_DRONE_ID_LOCATION: {break;}
    case MAVLINK_MSG_ID_OPEN_DRONE_ID_AUTHENTICATION: {break;}
    case MAVLINK_MSG_ID_OPEN_DRONE_ID_SELF_ID: {break;}
    case MAVLINK_MSG_ID_OPEN_DRONE_ID_SYSTEM: {break;}
    case MAVLINK_MSG_ID_OPEN_DRONE_ID_OPERATOR_ID: {break;}
    case MAVLINK_MSG_ID_OPEN_DRONE_ID_MESSAGE_PACK: {break;}
    case MAVLINK_MSG_ID_OPEN_DRONE_ID_ARM_STATUS: {break;}
    case MAVLINK_MSG_ID_OPEN_DRONE_ID_SYSTEM_UPDATE: {break;}
    case MAVLINK_MSG_ID_HYGROMETER_SENSOR: {break;}
        // ARDUPILOTMEGA
    case MAVLINK_MSG_ID_MEMINFO:{break;}
    case MAVLINK_MSG_ID_EKF_STATUS_REPORT:{break;}
    case MAVLINK_MSG_ID_HWSTATUS:{break;}
    case MAVLINK_MSG_ID_AHRS:{break;}
    case MAVLINK_MSG_ID_AHRS2:{break;}
    case MAVLINK_MSG_ID_AHRS3:{break;}
    case MAVLINK_MSG_ID_SIMSTATE:{break;}
    case MAVLINK_MSG_ID_SENSOR_OFFSETS:{break;}
    default:
    {
        logerWidget->addLog(QTime().currentTime(), NORMAL_MESSAGE_TYPE, QString::number(message.msgid));
        break;
    }
    }
}




Q_DECLARE_METATYPE(float*)
Q_DECLARE_METATYPE(uint8_t*)
Q_DECLARE_METATYPE(int8_t*)
Q_DECLARE_METATYPE(uint16_t*)
Q_DECLARE_METATYPE(int16_t*)
Q_DECLARE_METATYPE(uint32_t*)
Q_DECLARE_METATYPE(int32_t*)
Q_DECLARE_METATYPE(uint64_t*)

QVector<ValueToFollow> formMessageLinksStructure(MavlinkMessages *currentMessages)
{
    QVector<ValueToFollow> valuesToFollow;

    QVariant temp;
    temp.setValue(&currentMessages->heartbeat.autopilot);
    valuesToFollow.append(ValueToFollow(temp,UINT8_T_TYPE, "Тип"));

    temp.setValue(&currentMessages->heartbeat.base_mode);
    valuesToFollow.append(ValueToFollow(temp,UINT8_T_TYPE, "Базовый режим"));

    temp.setValue(&currentMessages->heartbeat.custom_mode);
    valuesToFollow.append(ValueToFollow(temp,UINT32_T_TYPE, "Режим работы"));

    temp.setValue(&currentMessages->heartbeat.system_status);
    valuesToFollow.append(ValueToFollow(temp,UINT8_T_TYPE, "Статус системы"));

    temp.setValue(&currentMessages->heartbeat.type);
    valuesToFollow.append(ValueToFollow(temp,UINT8_T_TYPE, "Тип устройства"));

    temp.setValue(&currentMessages->sysStatus.battery_remaining);
    valuesToFollow.append(ValueToFollow(temp,INT8_T_TYPE, "Осталось батареи"));
    temp.setValue(&currentMessages->sysStatus.current_battery);
    valuesToFollow.append(ValueToFollow(temp,INT16_T_TYPE, "Батарея"));
    temp.setValue(&currentMessages->sysStatus.drop_rate_comm);
    valuesToFollow.append(ValueToFollow(temp,UINT16_T_TYPE, "Потери канала"));
    temp.setValue(&currentMessages->sysStatus.errors_comm);
    valuesToFollow.append(ValueToFollow(temp,UINT16_T_TYPE, "Ошибки передачи"));
    temp.setValue(&currentMessages->sysStatus.errors_count1);
    valuesToFollow.append(ValueToFollow(temp,UINT16_T_TYPE, "Ошибки Т.1"));
    temp.setValue(&currentMessages->sysStatus.errors_count2);
    valuesToFollow.append(ValueToFollow(temp,UINT16_T_TYPE, "Ошибки Т.2"));
    temp.setValue(&currentMessages->sysStatus.errors_count3);
    valuesToFollow.append(ValueToFollow(temp,UINT16_T_TYPE, "Ошибки Т.3"));
    temp.setValue(&currentMessages->sysStatus.errors_count4);
    valuesToFollow.append(ValueToFollow(temp,UINT16_T_TYPE, "Ошибки Т.4"));
    temp.setValue(&currentMessages->sysStatus.load);
    valuesToFollow.append(ValueToFollow(temp,UINT16_T_TYPE, "Загруженность"));
    temp.setValue(&currentMessages->sysStatus.voltage_battery);
    valuesToFollow.append(ValueToFollow(temp,UINT16_T_TYPE, "Напряжение тока"));

    temp.setValue(&currentMessages->attitude.pitch);
    valuesToFollow.append(ValueToFollow(temp,FLOAT_TYPE, "Тангаж"));
    temp.setValue(&currentMessages->attitude.pitchspeed);
    valuesToFollow.append(ValueToFollow(temp,FLOAT_TYPE, "Скор. тангажа"));
    temp.setValue(&currentMessages->attitude.roll);
    valuesToFollow.append(ValueToFollow(temp,FLOAT_TYPE, "Крен"));
    temp.setValue(&currentMessages->attitude.rollspeed);
    valuesToFollow.append(ValueToFollow(temp,FLOAT_TYPE, "Скор. крена"));
    temp.setValue(&currentMessages->attitude.yaw);
    valuesToFollow.append(ValueToFollow(temp,FLOAT_TYPE, "Рысканье"));
    temp.setValue(&currentMessages->attitude.yawspeed);
    valuesToFollow.append(ValueToFollow(temp,FLOAT_TYPE, "Скор. рысканья"));

    temp.setValue(&currentMessages->localPositionNed.x);
    valuesToFollow.append(ValueToFollow(temp,FLOAT_TYPE, "Лок. x"));
    temp.setValue(&currentMessages->localPositionNed.vx);
    valuesToFollow.append(ValueToFollow(temp,FLOAT_TYPE, "Скор. лок. x"));
    temp.setValue(&currentMessages->localPositionNed.y);
    valuesToFollow.append(ValueToFollow(temp,FLOAT_TYPE, "Лок. y"));
    temp.setValue(&currentMessages->localPositionNed.vy);
    valuesToFollow.append(ValueToFollow(temp,FLOAT_TYPE, "Скор. лок. y"));
    temp.setValue(&currentMessages->localPositionNed.z);
    valuesToFollow.append(ValueToFollow(temp,FLOAT_TYPE, "Лок. z"));
    temp.setValue(&currentMessages->localPositionNed.vz);
    valuesToFollow.append(ValueToFollow(temp,FLOAT_TYPE, "Скор. лок. z"));

    temp.setValue(&currentMessages->homePosition.approach_x);
    valuesToFollow.append(ValueToFollow(temp,FLOAT_TYPE, "Сближение со ст. x"));
    temp.setValue(&currentMessages->homePosition.approach_y);
    valuesToFollow.append(ValueToFollow(temp,FLOAT_TYPE, "Сближение со ст. y"));
    temp.setValue(&currentMessages->homePosition.approach_z);
    valuesToFollow.append(ValueToFollow(temp,FLOAT_TYPE, "Сближение со ст. z"));

    return valuesToFollow;
}

