//#include "framehandler.h"
//#include <QDebug>

//FrameHandler::FrameHandler(QObject *parent, LogerWidget *logerWidget)
//    : QObject(parent)
//{
//    this->logerWidget = logerWidget;
//}

//int FrameHandler::handleMessage(mavlink_message_t message)
//{
////    if (message.sysid == 1 && message.compid == 1)
////    {
//        currentMessages.sysId = message.sysid;
//        currentMessages.compId = message.compid;

////    qDebug()<<message.
////    qDebug()<<"sys id = " + QString::number(currentMessages.sysId) + " comp id = " + QString::number(currentMessages.compId);
//    switch (message.msgid)
//    {
//    case MAVLINK_MSG_ID_HEARTBEAT:
//    {

//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_HEARTBEAT RECEIVED");
//        mavlink_msg_heartbeat_decode(&message, &(currentMessages.heartbeat));
////        qDebug()<<QString::number(currentMessages.heartbeat.mavlink_version);
//        break;
//    }
//    case MAVLINK_MSG_ID_SYS_STATUS:
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SYSTEM_TIME:
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_PING: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL:
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK:
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_AUTH_KEY:
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_LINK_NODE_STATUS: //WIP
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SET_MODE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_PARAM_VALUE:
//    {
////        mavlink_param_value_t currentMessages.paramValue;
//        mavlink_msg_param_value_decode(&message, &(currentMessages.paramValue));
////        if (currentMessages.paramValue.param_index == 0)
////            autopilotValues.clear();
//        autopilotValues[currentMessages.paramValue.param_id] = AutoPilotValue(currentMessages.paramValue.param_id, currentMessages.paramValue.param_index, QVariant(currentMessages.paramValue.param_value), currentMessages.paramValue.param_type);
//        QString debugString = "got param " + QString(currentMessages.paramValue.param_id) + " index " + QString::number(currentMessages.paramValue.param_index) + " type " + QString::number(currentMessages.paramValue.param_type) + " value ";
////        qDebug()<<"got param " << currentMessages.paramValue.param_id + " " ;
//        switch(currentMessages.paramValue.param_type)
//        {
//        case (MAV_PARAM_TYPE_UINT8):
//        {
//            debugString += QString::number(autopilotValues[currentMessages.paramValue.param_id].value.toUInt());
//            break;
//        }
//        case (MAV_PARAM_TYPE_INT8):
//        {
//            debugString += QString::number(autopilotValues[currentMessages.paramValue.param_id].value.toInt());
//            break;
//        }
//        case (MAV_PARAM_TYPE_UINT16):
//        {
//            debugString += QString::number(autopilotValues[currentMessages.paramValue.param_id].value.toUInt());
//            break;
//        }
//        case (MAV_PARAM_TYPE_INT16):
//        {
//            debugString += QString::number(autopilotValues[currentMessages.paramValue.param_id].value.toInt());
//            break;
//        }
//        case (MAV_PARAM_TYPE_UINT32):
//        {
//            debugString += QString::number(autopilotValues[currentMessages.paramValue.param_id].value.toULongLong());
//            break;
//        }
//        case (MAV_PARAM_TYPE_INT32):
//        {
//            debugString += QString::number(autopilotValues[currentMessages.paramValue.param_id].value.toLongLong());
//            break;
//        }
//        case (MAV_PARAM_TYPE_UINT64):
//        {
//            debugString += QString::number(autopilotValues[currentMessages.paramValue.param_id].value.toULongLong());
//            break;
//        }
//        case (MAV_PARAM_TYPE_INT64):
//        {
//            debugString += QString::number(autopilotValues[currentMessages.paramValue.param_id].value.toLongLong());
//            break;
//        }
//        case (MAV_PARAM_TYPE_REAL32):
//        {
//            debugString += QString::number(autopilotValues[currentMessages.paramValue.param_id].value.toFloat());
//            break;
//        }
//        case (MAV_PARAM_TYPE_REAL64):
//        {
//            debugString += QString::number(autopilotValues[currentMessages.paramValue.param_id].value.toDouble());
//            break;
//        }
//        }
//        debugString+= " total count " + QString::number(currentMessages.paramValue.param_count);
//        qDebug()<<debugString;
//        break;
//    }
//    case MAVLINK_MSG_ID_PARAM_SET:
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GPS_RAW_INT:
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GPS_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SCALED_IMU: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_RAW_IMU: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_RAW_PRESSURE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SCALED_PRESSURE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_ATTITUDE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        mavlink_msg_attitude_decode(&message, &(currentMessages.attitude));
//        break;
//    }
//    case MAVLINK_MSG_ID_ATTITUDE_QUATERNION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_LOCAL_POSITION_NED: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GLOBAL_POSITION_INT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_RC_CHANNELS_SCALED: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_RC_CHANNELS_RAW: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MISSION_REQUEST_PARTIAL_LIST: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MISSION_WRITE_PARTIAL_LIST: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MISSION_ITEM: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MISSION_REQUEST: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MISSION_SET_CURRENT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MISSION_CURRENT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MISSION_REQUEST_LIST: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MISSION_COUNT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MISSION_CLEAR_ALL: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MISSION_ITEM_REACHED: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MISSION_ACK: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SET_GPS_GLOBAL_ORIGIN: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_PARAM_MAP_RC: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MISSION_REQUEST_INT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SAFETY_SET_ALLOWED_AREA: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SAFETY_ALLOWED_AREA: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_ATTITUDE_QUATERNION_COV: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GLOBAL_POSITION_INT_COV: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_LOCAL_POSITION_NED_COV: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_RC_CHANNELS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_REQUEST_DATA_STREAM: //DEPRICATED
//    {
//        mavlink_request_data_stream_t msg;
//        mavlink_msg_request_data_stream_decode(&message, &msg);
//        qDebug()<<"request data stream. message rate " + QString::number(msg.req_message_rate) + " stream id " + QString::number(msg.req_stream_id) + " start/stop " + QString::number(msg.start_stop) + " comp/syst " + QString::number(msg.target_system) + "/" +QString::number(msg.target_component);
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_DATA_STREAM: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MANUAL_CONTROL: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_RC_CHANNELS_OVERRIDE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MISSION_ITEM_INT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_VFR_HUD: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_COMMAND_INT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_COMMAND_LONG: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_COMMAND_ACK: //DEPRICATED
//    {
//        mavlink_command_ack_t msg;
//        mavlink_msg_command_ack_decode(&message, &msg);
//        qDebug()<<"command ack. command id " + QString::number(msg.command) + " result " + QString::number(msg.result) + " progress " + QString::number(msg.progress) + " result param " + QString::number(msg.result_param2) + "target system " +QString::number(msg.target_system);
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_COMMAND_CANCEL: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MANUAL_SETPOINT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SET_ATTITUDE_TARGET: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_ATTITUDE_TARGET: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SET_POSITION_TARGET_LOCAL_NED: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_POSITION_TARGET_LOCAL_NED: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SET_POSITION_TARGET_GLOBAL_INT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_LOCAL_POSITION_NED_SYSTEM_GLOBAL_OFFSET: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_HIL_STATE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_HIL_CONTROLS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_HIL_RC_INPUTS_RAW: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_HIL_ACTUATOR_CONTROLS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_OPTICAL_FLOW: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GLOBAL_VISION_POSITION_ESTIMATE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_VISION_POSITION_ESTIMATE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_VISION_SPEED_ESTIMATE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_VICON_POSITION_ESTIMATE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_HIGHRES_IMU: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_OPTICAL_FLOW_RAD: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_HIL_SENSOR: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SIM_STATE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_RADIO_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_FILE_TRANSFER_PROTOCOL: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_TIMESYNC: //DEPRICATED
//    {
////        mavlink_timesync_t msg;
//        mavlink_msg_timesync_decode(&message, &(currentMessages.timesync));

//        qDebug()<<"timesync. timestamp 1 " +
//                  QString::number(currentMessages.timesync.tc1) +
//                  " timestamp 2 " + QString::number(currentMessages.timesync.tc1) +
//                  " target syst " + QString::number(currentMessages.timesync.target_system) +
//                  " target comp " + QString::number(currentMessages.timesync.target_component);

//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_CAMERA_TRIGGER: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_HIL_GPS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_HIL_OPTICAL_FLOW: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_HIL_STATE_QUATERNION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SCALED_IMU2: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_LOG_REQUEST_LIST: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_LOG_ENTRY: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_LOG_REQUEST_DATA: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_LOG_DATA: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_LOG_ERASE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_LOG_REQUEST_END: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GPS_INJECT_DATA: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GPS2_RAW: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_POWER_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SERIAL_CONTROL: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GPS_RTK: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GPS2_RTK: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SCALED_IMU3: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_DATA_TRANSMISSION_HANDSHAKE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_ENCAPSULATED_DATA: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_DISTANCE_SENSOR: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_TERRAIN_REQUEST: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_TERRAIN_DATA: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_TERRAIN_CHECK: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_TERRAIN_REPORT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SCALED_PRESSURE2: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_ATT_POS_MOCAP: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SET_ACTUATOR_CONTROL_TARGET: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_ACTUATOR_CONTROL_TARGET: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_ALTITUDE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_RESOURCE_REQUEST: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SCALED_PRESSURE3: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_FOLLOW_TARGET: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_CONTROL_SYSTEM_STATE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_BATTERY_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_AUTOPILOT_VERSION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_LANDING_TARGET: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_FENCE_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MAG_CAL_REPORT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_EFI_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_ESTIMATOR_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_WIND_COV: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GPS_INPUT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GPS_RTCM_DATA: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_HIGH_LATENCY: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_HIGH_LATENCY2: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_VIBRATION: //DEPRICATED
//    {
//        //        logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_VIBRATION RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_HOME_POSITION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SET_HOME_POSITION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MESSAGE_INTERVAL: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_EXTENDED_SYS_STATE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_ADSB_VEHICLE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_COLLISION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_V2_EXTENSION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MEMORY_VECT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_DEBUG_VECT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_NAMED_VALUE_FLOAT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_NAMED_VALUE_INT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_STATUSTEXT: //DEPRICATED
//    {
//        mavlink_statustext_t statusText;
//        mavlink_msg_statustext_decode(&message, &statusText);
//        qDebug()<<" statustext. severinity " + QString::number(statusText.severity)+ " text " + statusText.text;

//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_DEBUG: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SETUP_SIGNING: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_BUTTON_CHANGE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_PLAY_TUNE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_CAMERA_INFORMATION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_CAMERA_SETTINGS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_STORAGE_INFORMATION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_CAMERA_CAPTURE_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_CAMERA_IMAGE_CAPTURED: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_FLIGHT_INFORMATION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_MOUNT_ORIENTATION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_LOGGING_DATA: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_LOGGING_DATA_ACKED: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_LOGGING_ACK: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_VIDEO_STREAM_INFORMATION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_VIDEO_STREAM_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_CAMERA_FOV_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_CAMERA_TRACKING_IMAGE_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_CAMERA_TRACKING_GEO_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GIMBAL_MANAGER_INFORMATION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GIMBAL_MANAGER_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GIMBAL_MANAGER_SET_ATTITUDE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GIMBAL_DEVICE_INFORMATION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GIMBAL_DEVICE_SET_ATTITUDE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GIMBAL_DEVICE_ATTITUDE_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_AUTOPILOT_STATE_FOR_GIMBAL_DEVICE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GIMBAL_MANAGER_SET_PITCHYAW: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GIMBAL_MANAGER_SET_MANUAL_CONTROL: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_ESC_INFO: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_ESC_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_WIFI_CONFIG_AP: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_AIS_VESSEL: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_UAVCAN_NODE_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_UAVCAN_NODE_INFO: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_PARAM_EXT_REQUEST_READ: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_PARAM_EXT_REQUEST_LIST: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_PARAM_EXT_VALUE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_PARAM_EXT_SET: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_PARAM_EXT_ACK: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_OBSTACLE_DISTANCE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_ODOMETRY: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_TRAJECTORY_REPRESENTATION_WAYPOINTS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_TRAJECTORY_REPRESENTATION_BEZIER: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_CELLULAR_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_ISBD_LINK_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_CELLULAR_CONFIG: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_RAW_RPM: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_UTM_GLOBAL_POSITION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_DEBUG_FLOAT_ARRAY: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_ORBIT_EXECUTION_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SMART_BATTERY_INFO: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_GENERATOR_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_ACTUATOR_OUTPUT_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_TIME_ESTIMATE_TO_TARGET: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_TUNNEL: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_CAN_FRAME: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_ONBOARD_COMPUTER_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_COMPONENT_INFORMATION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_COMPONENT_METADATA: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_PLAY_TUNE_V2: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_SUPPORTED_TUNES: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_EVENT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_CURRENT_EVENT_SEQUENCE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_REQUEST_EVENT: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_RESPONSE_EVENT_ERROR: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_CANFD_FRAME: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_CAN_FILTER_MODIFY: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_WHEEL_DISTANCE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_WINCH_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_OPEN_DRONE_ID_BASIC_ID: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_OPEN_DRONE_ID_LOCATION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_OPEN_DRONE_ID_AUTHENTICATION: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_OPEN_DRONE_ID_SELF_ID: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_OPEN_DRONE_ID_SYSTEM: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_OPEN_DRONE_ID_OPERATOR_ID: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_OPEN_DRONE_ID_MESSAGE_PACK: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_OPEN_DRONE_ID_ARM_STATUS: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_OPEN_DRONE_ID_SYSTEM_UPDATE: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_HYGROMETER_SENSOR: //DEPRICATED
//    {
//        //            logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_SYS_STATUS RECEIVED");
//        //            mavlink_msg_sys_status_decode(&message, &(currentMessages.sysStatus));
//        break;
//    }
//        // ARDUPILOTMEGA
//    case MAVLINK_MSG_ID_MEMINFO:
//    {
//        //        logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_MEMINFO");
//        mavlink_msg_meminfo_decode(&message, &(currentMessages.memInfo));
//        break;
//    }
//    case MAVLINK_MSG_ID_EKF_STATUS_REPORT:
//    {
//        //        logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_EKF_STATUS_REPORT");
//        mavlink_msg_ekf_status_report_decode(&message, &(currentMessages.ekfStatusReport));
//        break;
//    }
//    case MAVLINK_MSG_ID_HWSTATUS:
//    {
//        //        logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_HWSTATUS");
//        mavlink_msg_hwstatus_decode(&message, &(currentMessages.hwStatus));
//        break;
//    }
//    case MAVLINK_MSG_ID_AHRS:
//    {
//        //        logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_AHRS");
//        mavlink_msg_ahrs_decode(&message, &(currentMessages.ahrs));
//        break;
//    }
//    case MAVLINK_MSG_ID_AHRS2:
//    {
//        //        logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_AHRS2");
//        mavlink_msg_ahrs2_decode(&message, &(currentMessages.ahrs2));
//        break;
//    }
//    case MAVLINK_MSG_ID_AHRS3:
//    {
//        //        logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_AHRS3");
//        mavlink_msg_ahrs3_decode(&message, &(currentMessages.ahrs3));
//        break;
//    }
//    case MAVLINK_MSG_ID_SIMSTATE:
//    {
//        //        logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_AHRS3");
//        mavlink_msg_simstate_decode(&message, &(currentMessages.simState));
//        break;
//    }
//    case MAVLINK_MSG_ID_SENSOR_OFFSETS:
//    {
//        //        logerWidget->addLog(QTime().currentTime(), 0, "MAVLINK_MSG_ID_AHRS3");
//        mavlink_msg_sensor_offsets_decode(&message, &(currentMessages.sensorOffset));
//        break;
//    }
//    default:
//    {
//        logerWidget->addLog(QTime().currentTime(), 0, QString::number(message.msgid));
//        break;
//    }
//    }


//    return message.msgid;
//}

//QPair<int,int> FrameHandler::getSysCompIds()
//{
//    return QPair<int,int>(currentMessages.sysId, currentMessages.compId);
//}

//// =================================================================================================================================================================================================================
//// =================================================================================== FRAME CODER / DECODER == ====================================================================================================
//// =================================================================================================================================================================================================================


//// =================================================================================================================================================================================================================
//// =================================================================================== EXTRA INTERNAL FUNCTIONS ====================================================================================================
//// =================================================================================================================================================================================================================

//const MavlinkMessages &FrameHandler::getCurrentMessages() const
//{
//    return currentMessages;
//}

//uint64_t getTimeUsec()
//{
//    static struct timeval _time_stamp;
//    gettimeofday(&_time_stamp, NULL);
//    return _time_stamp.tv_sec*1000000 + _time_stamp.tv_usec;
//}

