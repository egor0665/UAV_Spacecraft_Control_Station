#ifndef CONNECTEDVEHICLE_H
#define CONNECTEDVEHICLE_H

#include "framehandler.h"
#include <QObject>
#include <QTimer>
#include <QByteArray>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QVector>
#include <time.h>
#include <sys/time.h>
#include <custom_widgets/Main_widgets/logerwidget.h>
#include <mavlink/ardupilotmega/mavlink.h>
#include <connection/connectionhandler.h>
#include <custom_widgets/Mission_planning_tab_widgets/missionplanitem.h>
#include <custom_dialogs/processdialog.h>

//uint64_t getTimeUsec();




struct MavlinkMessages {

    int sysId = 0;
    int compId = 0;
    mavlink_heartbeat_t heartbeat = {0,0,0,0,0,0};
    mavlink_system_time_t systemTime = {0,0};
    mavlink_sys_status_t sysStatus = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    mavlink_global_position_int_t globalPositionInt = {0,0,0,0,0,0,0,0,0};
    mavlink_attitude_t attitude = {0,0,0,0,0,0,0};
    mavlink_param_value_t paramValue = {0,0,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},0};
    mavlink_local_position_ned_t localPositionNed = {0,0,0,0,0,0,0};

    mavlink_mission_count_t missionCount = {0,0,0,0};
    mavlink_mission_request_int_t missionRequestInt = {0,0,0,0};
    mavlink_mission_ack_t missionAck = {0,0,0,0};
    mavlink_mission_item_int_t missionItemInt = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    mavlink_autopilot_version_t autopilotVersion = {0,0,0,0,0,0,0,0,{0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0}};
    mavlink_home_position_t homePosition = {0,0,0,0,0,0,{0,0,0,0},0,0,0,0};

    mavlink_mission_item_reached_t missionItemReached = {0};
};

struct AutoPilotValue {
    QString id;
    int index;
    QVariant value;
    int type;
    AutoPilotValue(QString id, int index, QVariant value, int type)
    {
        this->id = id;
        this->index = index;
        this->value = value;
        this->type = type;
    }
    AutoPilotValue(){}
};

struct CommandToAck {
    int id;
    int seq;
    mavlink_message_t message;
    QTime timeStamp;
    CommandToAck(int id ,int seq, mavlink_message_t message, QTime timeStamp)
    {
        this->id = id;
        this->seq = seq;
        this->message = message;
        this->timeStamp = timeStamp;
    }
};

QVector<ValueToFollow> formMessageLinksStructure(MavlinkMessages *currentMessages);

class ConnectedVehicle: public QObject
{
    Q_OBJECT

//    QMap<QString, uint16_t*> valuesToFollow = {};
//    QVector<Value> valuesToFollow;

    QVector<CommandToAck> commandsToAck = {};

    int currentMode;

    bool inConnectionProgressStage1;
    bool inConnectionProgressStage2;
    bool inConnectionProgressStage3;

    ProcessDialog *connectionProcessDialog;

    QMap<QString,AutoPilotValue> autopilotValues = {};

    int systemId = 255;
    int componentId = 255;

    MavlinkMessages currentMessages;

    LogerWidget *logerWidget;

    QVector<MissionPlanItem> missionPlanItemsToWrite;

    QTimer helloPacketTimer;
    QTimer ackTimer;

    int vehicleId;

public:
    ConnectionHandler *connectionHandler;
    QString ipAddress;
    int portNum;
    PortEnum connectionType;

    ConnectedVehicle(int vehicleId, LogerWidget *logerWidget, QObject *parent = nullptr);
    ~ConnectedVehicle();
    bool connectToPort(QString ipAddress, PortEnum connectionType, int baudRate, int portNum);
    void refreshParams();
    void writeParams(QVector<mavlink_param_value_t> paramsToChange);
    void sendArm(int force);
    void sendDisarm(int force);
    void sendTakeOff(int altitude);
    void sendSetMode(int mode);
    void sendSetPositionTargetLocalNEDXYZ(float x, float y, float z);
    void sendSetPositionTargetLocalNEDXZ(float x, float z);
    void sendReturnHome();
    void sendLand();
    void sendSetHomeHere();
    void writePlanToVehicle(QVector<MissionPlanItem> planItems);
    const MavlinkMessages &getCurrentMessages() const;

    void missionSetMode(int executeCommand, float x, float y, float z);
    QVector<ValueToFollow> getValuesToFollow();
protected:

    void startSendingHelloPackets();
    void startConnectionProcess();

    void startVehicleInitStageOne();
    void startVehicleInitStageTwo();
    void sendRequestMessageInterval(int messageId, int interval);

    void requestParams();
    void sendRequestMessage(int messageId);
    void addCommandToAckVectorAndExecute(mavlink_message_t message, int commandId);
    void sendCurrentMissionItem(int num);

signals:

    void allParamsReceived(int vehicleId, QMap<QString,AutoPilotValue> autopilotValues);

    void cantConnectTovehicle(int vehicleId);

    void mavlinkMSGReceived(int vehicleId, int messageId);
    void mavlinkMSGHeartbeatReceived(int vehicleId, mavlink_heartbeat_t message);

    void mavlinkMSGSysStatusReceived(int vehicleId, mavlink_sys_status_t message);

    void mavlinkMSGSysTimeReceived(int vehicleId, mavlink_system_time_t message);

    void mavlinkMSGGlobalPositionIntReceived(int vehicleId, mavlink_global_position_int_t message);
    void mavlinkMSGAttitudeReceived(int vehicleId, mavlink_attitude_t message);
    void mavlinkMSGLocalPositionNEDReceived(int vehicleId, mavlink_local_position_ned_t message);

    void mavlinkMSGHomePositionReceived(int vehicleId, mavlink_home_position_t message);

    void missionAckReceived();

    void mavlinkMSGMissionItemReachedReceived(int vehicleId, mavlink_mission_item_reached_t missionItemReached);
protected slots:
    void handleAckCommands();
    void handleNewMessage(mavlink_message_t message);

    void sendHelloPacket();
    void stopConnection();
};

#endif // CONNECTEDVEHICLE_H
