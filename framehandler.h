//#ifndef FRAMEHANDLER_H
//#define FRAMEHANDLER_H

////#include <mainmodel.h>
//#include <QByteArray>
//#include <QObject>
//#include <QString>
//#include <QVariant>
//#include <QVector>
//#include <time.h>
//#include <sys/time.h>
//#include <mavlink/ardupilotmega/mavlink.h>
//#include <custom_widgets/logerwidget.h>

//uint64_t getTimeUsec();

////struct Value{
////    QVariant value;
////    QString type;
////    Value(QVariant value, QString type)
////    {
////        this->value = value;
////        this->type = type;
////    }
////};

////struct CustomMessage{
////    //На примере MavLink
////    //Первый байт пакета (STX) — это символ начала сообщения: 0xFD для версии v2.0, 0xFE для версии v1.0, 0x55 для версии v0.9.
////    // LEN — длинна полезной нагрузки (сообщения).
////    // SEQ — содержит счётчик пакета (0-255), который поможет нам выявить потерю сообщения.
////    // SYS (System ID) — идентификатор отправляющий системы, а COMP (Component ID) — идентификатор отправляющего компонента.
////    // MSG (Message ID) — тип сообщения, от него зависит, какие данные будут лежать в полезной нагрузки пакета.
////    // PAYLOAD — полезная нагрузка пакета, сообщение, размером от 0 до 255 байт.
////    //Два последних байта пакета — CKA и CKB, нижний и верхний байт, соответственно, содержат контрольную сумму пакета.

////    qint8 length;
////    qint8 sequence;
////    qint8 sysId;
////    qint8 spacecraftId;
////    qint8 msgType;
////    QByteArray data;
////    CustomMessage(qint8 length, qint8 sequence, qint8 sysId, qint8 spacecraftId, qint8 msgType, QByteArray data)
////    {
////        this->length = length;
////        this->sequence = sequence;
////        this->sysId = sysId;
////        this->spacecraftId = spacecraftId;
////        this->msgType = msgType;
////        this->data = data;
////    }
////    CustomMessage(){};
////};
////struct TimeStamps
////{
////    TimeStamps()
////    {
////        reset_timestamps();
////    }

////    uint64_t heartbeat;
////    uint64_t sysStatus;
////    uint64_t batteryStatus;
////    uint64_t radioStatus;
////    uint64_t localPositionNed;
////    uint64_t globalPositionInt;
////    uint64_t positionTargetLocalNed;
////    uint64_t positionTargetGlobalInt;
////    uint64_t highresImu;
////    uint64_t attitude;

////    void
////    reset_timestamps()
////    {
////        heartbeat = 0;
////        sysStatus = 0;
////        batteryStatus = 0;
////        radioStatus = 0;
////        localPositionNed = 0;
////        globalPositionInt = 0;
////        positionTargetLocalNed = 0;
////        positionTargetGlobalInt = 0;
////        highresImu = 0;
////        attitude = 0;
////    }

////};


//// Struct containing information on the MAV we are currently connected to

//struct AutoPilotValue {
//    QString id;
//    int index;
//    QVariant value;
//    int type;
//    AutoPilotValue(QString id, int index, QVariant value, int type)
//    {
//        this->id = id;
//        this->index = index;
//        this->value = value;
//        this->type = type;
//    }
//    AutoPilotValue(){}
//};

//struct MavlinkMessages {

//    int sysId = 0;
//    int compId = 0;

//    // Heartbeat
//    mavlink_heartbeat_t heartbeat;

//    // System Status


//    // Battery Status
//    mavlink_timesync_t timesync;


//    mavlink_hwstatus_t hwStatus;
//    mavlink_system_time_t systemTime;
//    mavlink_terrain_report_t terrainReport;
//    mavlink_ekf_status_report_t ekfStatusReport;
//    mavlink_vibration_t vibration;
//    mavlink_raw_imu_t rawImu;
//    mavlink_scaled_imu2_t scaledImu2;
//    mavlink_scaled_pressure_t scaledPressure;
//    mavlink_sys_status_t sysStatus;
//    mavlink_meminfo_t memInfo;
//    mavlink_mission_current_t missonCurrent;
//    mavlink_gps_raw_int_t GPSRawInt;
//    mavlink_nav_controller_output_t NavControllerOutput;
//    mavlink_global_position_int_t globalPositionInt;
//    mavlink_servo_output_raw_t servoOutputRaw;
//    mavlink_rc_channels_raw_t rcChannelsRaw;
//    mavlink_attitude_t attitude;
//    mavlink_simstate_t simState;
//    mavlink_ahrs2_t ahrs2;
//    mavlink_vfr_hud_t vfrHud;
//    mavlink_ahrs_t ahrs;


//    mavlink_param_value_t paramValue;

//    mavlink_sensor_offsets_t sensorOffset;



//    mavlink_battery_status_t batteryStatus;
//    mavlink_radio_status_t radioStatus;
//    mavlink_local_position_ned_t localPositionNed;
//    mavlink_position_target_local_ned_t positionTargetLocalNed;
//    mavlink_position_target_global_int_t positionTargetGlobalInt;
//    mavlink_highres_imu_t highresImu;
//    mavlink_ahrs3_t ahrs3;


//    mavlink_attitude_quaternion_t attitudeQuaterunion;

//    mavlink_log_request_list_t logRequestList;
//    mavlink_named_value_int_t namedValueInt;
//    mavlink_named_value_float_t namedValueFloat;
//    mavlink_gps2_raw_t GPS2Raw;
//    mavlink_mission_request_list_t missionRequestList;

//    mavlink_mission_request_partial_list_t missionRequestPartialList;
//    mavlink_collision_t collision;
//    mavlink_vision_speed_estimate_t visionSpeedEstimate;
//    mavlink_terrain_request_t terrainRequest;
//    mavlink_scaled_imu_t scaledImu;
//    mavlink_scaled_imu3_t scaledImu3;
//    mavlink_scaled_pressure2_t scaledPressure2;
//    mavlink_scaled_pressure3_t scaledPressure3;


//    // System Parameters?

//    // Time Stamps
////    TimeStamps timeStamps;

////    void
////    resetTimestamps()
////    {
////        timeStamps.reset_timestamps();
////    }

//};


//class FrameHandler: public QObject
//{
//    Q_OBJECT

//    QMap<QString,AutoPilotValue> autopilotValues = {};

//    char readingStatus;
//    char writingStatus;
//    char controlStatus;
//    uint64_t writeCount;

//    int systemId = 255;
//    int autopilotId = 255;
//    int companionId = 255;

//    MavlinkMessages currentMessages;
//    mavlink_set_position_target_local_ned_t initialPosition;

//    LogerWidget *logerWidget;

//public:
//    FrameHandler(QObject *parent = nullptr, LogerWidget *logerWidget = nullptr);
//    ~FrameHandler(){};
//    int handleMessage(mavlink_message_t message);
////    void handleMessageData(qint8 spacecraftId, qint8 msgType, QByteArray data);
//    //    QByteArray codeFrame(QVector<Value> values, qint8 seq, qint8 msgType, qint8 spacecraftId);
//    const MavlinkMessages &getCurrentMessages() const;

//    QPair<int,int> getSysCompIds();
//protected:
////    bool checkCheckSum(QByteArray data);
////    int checkCommunicationStatus();
////    QVector<float> getPIDValuesFromData(QByteArray data);
//signals:
//    void helloFrameReceived(int spacecraftId, int estBatteryHrs, int estBatteryMin, int status);
//    void answerPIDValuesFrameReceived(int spacecraftId, QVector<float> values);
//    void updateFrameReceived(int id);
//};

//#endif // FRAMEHANDLER_H
