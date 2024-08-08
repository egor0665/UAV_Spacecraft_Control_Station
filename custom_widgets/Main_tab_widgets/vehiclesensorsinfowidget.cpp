#include "vehiclesensorsinfowidget.h"

#include <QHeaderView>
#include <QVBoxLayout>

VehicleSensorsInfoWidget::VehicleSensorsInfoWidget(QWidget *parent) : QWidget(parent)
{
    statusCircles.append(QPixmap("C:/Qt/5.15.2/mingw81_32/GroundControlStation/resources/blueStatusCircle.png").scaled(15,15));
    statusCircles.append(QPixmap("C:/Qt/5.15.2/mingw81_32/GroundControlStation/resources/greenStatusCircle.png").scaled(15,15));

    mainTable.setRowCount(SENSOR_NUM);
    mainTable.setColumnCount(3);

    mainTable.setHorizontalHeaderLabels({
                                         "Присутствует",
                                         "Включен",
                                         "Состояние"
                                         });
    mainTable.setVerticalHeaderLabels({
                                        "3D_GYRO",
                                        "3D_ACCEL",
                                        "3D_MAG",
                                        "ABS_PRES",
                                        "DIF_PRES",
                                        "GPS",
                                        "OPT_FLOW",
                                        "VIS_POS",
                                        "LASER_POS",
                                        "EXT_TRTH",
                                        "ANG_CNTRL",
                                        "ATT_STAB",
                                        "YAW_POS",
                                        "Z_ALT_CNTRL",
                                        "XY_POS_CNTRL",
                                        "MTR_OUT",
                                        "RC_RCVR",
                                        "3D_GYRO2",
                                        "3D_ACCEL2",
                                        "3D_MAG2",
                                        "GEOFENCE",
                                        "AHRS",
                                        "TERRAIN",
                                        "RVRS_MTR",
                                        "LOGGING",
                                        "SNSR_BAT",
                                        "SNSR_PROX",
                                        "SNSR_SAT",
                                        "PRRM_CHCK",
                                        "OBS_AVOID",
                                        "SNSR_PROP"});
    mainTable.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainTable.verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    mainTable.verticalHeader()->setDefaultSectionSize(10);

    for (int i=0;i<SENSOR_NUM;i++)
    {
        statusLabelVector.append(QVector<QLabel*>());
        statusLabelVector[i].append({new QLabel(this), new QLabel(this), new QLabel(this)});
        statusLabelVector[i][0]->setFont(QFont("MS Shell Dlg 2", 8, 10));
        statusLabelVector[i][0]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        statusLabelVector[i][0]->setMinimumWidth(65);

        statusLabelVector[i][1]->setFont(QFont("MS Shell Dlg 2", 8, 10));
        statusLabelVector[i][1]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        statusLabelVector[i][1]->setMinimumWidth(65);

        statusLabelVector[i][2]->setFont(QFont("MS Shell Dlg 2", 8, 10));
        statusLabelVector[i][2]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        statusLabelVector[i][2]->setMinimumWidth(65);

        statusLabelVector[i][0]->setPixmap(statusCircles[0]);
        statusLabelVector[i][1]->setPixmap(statusCircles[0]);
        statusLabelVector[i][2]->setPixmap(statusCircles[0]);
        mainTable.setCellWidget(i,0,statusLabelVector[i][0]);
        mainTable.setCellWidget(i,1,statusLabelVector[i][1]);
        mainTable.setCellWidget(i,2,statusLabelVector[i][2]);
    }
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(&mainTable);
    this->setLayout(mainLayout);
}

VehicleSensorsInfoWidget::~VehicleSensorsInfoWidget()
{
    for (int i=0;i<statusLabelVector.length();i++)
        for (int j=0;j<statusLabelVector[0].length();j++)
            delete statusLabelVector[i][j];
}

void VehicleSensorsInfoWidget::updateSysStatus(mavlink_sys_status_t message)
{
    present = message.onboard_control_sensors_present;
    enabled = message.onboard_control_sensors_enabled;
    health = message.onboard_control_sensors_health;

    if (!sleep)
        displaySensorInfo();
}

void VehicleSensorsInfoWidget::displaySensorInfo()
{
    statusLabelVector[0][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_3D_GYRO)/MAV_SYS_STATUS_SENSOR_3D_GYRO]);
    statusLabelVector[0][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_3D_GYRO)/MAV_SYS_STATUS_SENSOR_3D_GYRO]);
    statusLabelVector[0][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_3D_GYRO)/MAV_SYS_STATUS_SENSOR_3D_GYRO]);

    statusLabelVector[1][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_3D_ACCEL)/MAV_SYS_STATUS_SENSOR_3D_ACCEL]);
    statusLabelVector[1][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_3D_ACCEL)/MAV_SYS_STATUS_SENSOR_3D_ACCEL]);
    statusLabelVector[1][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_3D_ACCEL)/MAV_SYS_STATUS_SENSOR_3D_ACCEL]);

    statusLabelVector[2][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_3D_MAG)/MAV_SYS_STATUS_SENSOR_3D_MAG]);
    statusLabelVector[2][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_3D_MAG)/MAV_SYS_STATUS_SENSOR_3D_MAG]);
    statusLabelVector[2][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_3D_MAG)/MAV_SYS_STATUS_SENSOR_3D_MAG]);

    statusLabelVector[3][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE)/MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE]);
    statusLabelVector[3][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE)/MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE]);
    statusLabelVector[3][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE)/MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE]);

    statusLabelVector[4][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE)/MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE]);
    statusLabelVector[4][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE)/MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE]);
    statusLabelVector[4][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE)/MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE]);

    statusLabelVector[5][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_GPS)/MAV_SYS_STATUS_SENSOR_GPS]);
    statusLabelVector[5][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_GPS)/MAV_SYS_STATUS_SENSOR_GPS]);
    statusLabelVector[5][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_GPS)/MAV_SYS_STATUS_SENSOR_GPS]);

    statusLabelVector[6][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_OPTICAL_FLOW)/MAV_SYS_STATUS_SENSOR_OPTICAL_FLOW]);
    statusLabelVector[6][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_OPTICAL_FLOW)/MAV_SYS_STATUS_SENSOR_OPTICAL_FLOW]);
    statusLabelVector[6][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_OPTICAL_FLOW)/MAV_SYS_STATUS_SENSOR_OPTICAL_FLOW]);

    statusLabelVector[7][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_VISION_POSITION)/MAV_SYS_STATUS_SENSOR_VISION_POSITION]);
    statusLabelVector[7][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_VISION_POSITION)/MAV_SYS_STATUS_SENSOR_VISION_POSITION]);
    statusLabelVector[7][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_VISION_POSITION)/MAV_SYS_STATUS_SENSOR_VISION_POSITION]);

    statusLabelVector[8][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_LASER_POSITION)/MAV_SYS_STATUS_SENSOR_LASER_POSITION]);
    statusLabelVector[8][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_LASER_POSITION)/MAV_SYS_STATUS_SENSOR_LASER_POSITION]);
    statusLabelVector[8][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_LASER_POSITION)/MAV_SYS_STATUS_SENSOR_LASER_POSITION]);

    statusLabelVector[9][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_EXTERNAL_GROUND_TRUTH)/MAV_SYS_STATUS_SENSOR_EXTERNAL_GROUND_TRUTH]);
    statusLabelVector[9][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_EXTERNAL_GROUND_TRUTH)/MAV_SYS_STATUS_SENSOR_EXTERNAL_GROUND_TRUTH]);
    statusLabelVector[9][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_EXTERNAL_GROUND_TRUTH)/MAV_SYS_STATUS_SENSOR_EXTERNAL_GROUND_TRUTH]);

    statusLabelVector[10][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_ANGULAR_RATE_CONTROL)/MAV_SYS_STATUS_SENSOR_ANGULAR_RATE_CONTROL]);
    statusLabelVector[10][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_ANGULAR_RATE_CONTROL)/MAV_SYS_STATUS_SENSOR_ANGULAR_RATE_CONTROL]);
    statusLabelVector[10][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_ANGULAR_RATE_CONTROL)/MAV_SYS_STATUS_SENSOR_ANGULAR_RATE_CONTROL]);

    statusLabelVector[11][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_ATTITUDE_STABILIZATION)/MAV_SYS_STATUS_SENSOR_ATTITUDE_STABILIZATION]);
    statusLabelVector[11][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_ATTITUDE_STABILIZATION)/MAV_SYS_STATUS_SENSOR_ATTITUDE_STABILIZATION]);
    statusLabelVector[11][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_ATTITUDE_STABILIZATION)/MAV_SYS_STATUS_SENSOR_ATTITUDE_STABILIZATION]);

    statusLabelVector[12][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_YAW_POSITION)/MAV_SYS_STATUS_SENSOR_YAW_POSITION]);
    statusLabelVector[12][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_YAW_POSITION)/MAV_SYS_STATUS_SENSOR_YAW_POSITION]);
    statusLabelVector[12][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_YAW_POSITION)/MAV_SYS_STATUS_SENSOR_YAW_POSITION]);

    statusLabelVector[13][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_Z_ALTITUDE_CONTROL)/MAV_SYS_STATUS_SENSOR_Z_ALTITUDE_CONTROL]);
    statusLabelVector[13][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_Z_ALTITUDE_CONTROL)/MAV_SYS_STATUS_SENSOR_Z_ALTITUDE_CONTROL]);
    statusLabelVector[13][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_Z_ALTITUDE_CONTROL)/MAV_SYS_STATUS_SENSOR_Z_ALTITUDE_CONTROL]);

    statusLabelVector[14][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_XY_POSITION_CONTROL)/MAV_SYS_STATUS_SENSOR_XY_POSITION_CONTROL]);
    statusLabelVector[14][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_XY_POSITION_CONTROL)/MAV_SYS_STATUS_SENSOR_XY_POSITION_CONTROL]);
    statusLabelVector[14][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_XY_POSITION_CONTROL)/MAV_SYS_STATUS_SENSOR_XY_POSITION_CONTROL]);

    statusLabelVector[15][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS)/MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS]);
    statusLabelVector[15][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS)/MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS]);
    statusLabelVector[15][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS)/MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS]);

    statusLabelVector[16][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_RC_RECEIVER)/MAV_SYS_STATUS_SENSOR_RC_RECEIVER]);
    statusLabelVector[16][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_RC_RECEIVER)/MAV_SYS_STATUS_SENSOR_RC_RECEIVER]);
    statusLabelVector[16][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_RC_RECEIVER)/MAV_SYS_STATUS_SENSOR_RC_RECEIVER]);

    statusLabelVector[17][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_3D_GYRO2)/MAV_SYS_STATUS_SENSOR_3D_GYRO2]);
    statusLabelVector[17][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_3D_GYRO2)/MAV_SYS_STATUS_SENSOR_3D_GYRO2]);
    statusLabelVector[17][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_3D_GYRO2)/MAV_SYS_STATUS_SENSOR_3D_GYRO2]);

    statusLabelVector[18][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_3D_ACCEL2)/MAV_SYS_STATUS_SENSOR_3D_ACCEL2]);
    statusLabelVector[18][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_3D_ACCEL2)/MAV_SYS_STATUS_SENSOR_3D_ACCEL2]);
    statusLabelVector[18][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_3D_ACCEL2)/MAV_SYS_STATUS_SENSOR_3D_ACCEL2]);

    statusLabelVector[19][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_3D_MAG2)/MAV_SYS_STATUS_SENSOR_3D_MAG2]);
    statusLabelVector[19][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_3D_MAG2)/MAV_SYS_STATUS_SENSOR_3D_MAG2]);
    statusLabelVector[19][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_3D_MAG2)/MAV_SYS_STATUS_SENSOR_3D_MAG2]);

    statusLabelVector[20][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_GEOFENCE)/MAV_SYS_STATUS_GEOFENCE]);
    statusLabelVector[20][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_GEOFENCE)/MAV_SYS_STATUS_GEOFENCE]);
    statusLabelVector[20][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_GEOFENCE)/MAV_SYS_STATUS_GEOFENCE]);

    statusLabelVector[21][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_AHRS)/MAV_SYS_STATUS_AHRS]);
    statusLabelVector[21][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_AHRS)/MAV_SYS_STATUS_AHRS]);
    statusLabelVector[21][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_AHRS)/MAV_SYS_STATUS_AHRS]);

    statusLabelVector[22][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_TERRAIN)/MAV_SYS_STATUS_TERRAIN]);
    statusLabelVector[22][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_TERRAIN)/MAV_SYS_STATUS_TERRAIN]);
    statusLabelVector[22][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_TERRAIN)/MAV_SYS_STATUS_TERRAIN]);

    statusLabelVector[23][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_REVERSE_MOTOR)/MAV_SYS_STATUS_REVERSE_MOTOR]);
    statusLabelVector[23][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_REVERSE_MOTOR)/MAV_SYS_STATUS_REVERSE_MOTOR]);
    statusLabelVector[23][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_REVERSE_MOTOR)/MAV_SYS_STATUS_REVERSE_MOTOR]);

    statusLabelVector[24][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_LOGGING)/MAV_SYS_STATUS_LOGGING]);
    statusLabelVector[24][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_LOGGING)/MAV_SYS_STATUS_LOGGING]);
    statusLabelVector[24][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_LOGGING)/MAV_SYS_STATUS_LOGGING]);

    statusLabelVector[25][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_BATTERY)/MAV_SYS_STATUS_SENSOR_BATTERY]);
    statusLabelVector[25][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_BATTERY)/MAV_SYS_STATUS_SENSOR_BATTERY]);
    statusLabelVector[25][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_BATTERY)/MAV_SYS_STATUS_SENSOR_BATTERY]);

    statusLabelVector[26][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_PROXIMITY)/MAV_SYS_STATUS_SENSOR_PROXIMITY]);
    statusLabelVector[26][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_PROXIMITY)/MAV_SYS_STATUS_SENSOR_PROXIMITY]);
    statusLabelVector[26][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_PROXIMITY)/MAV_SYS_STATUS_SENSOR_PROXIMITY]);

    statusLabelVector[27][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_SATCOM)/MAV_SYS_STATUS_SENSOR_SATCOM]);
    statusLabelVector[27][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_SATCOM)/MAV_SYS_STATUS_SENSOR_SATCOM]);
    statusLabelVector[27][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_SATCOM)/MAV_SYS_STATUS_SENSOR_SATCOM]);

    statusLabelVector[28][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_PREARM_CHECK)/MAV_SYS_STATUS_PREARM_CHECK]);
    statusLabelVector[28][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_PREARM_CHECK)/MAV_SYS_STATUS_PREARM_CHECK]);
    statusLabelVector[28][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_PREARM_CHECK)/MAV_SYS_STATUS_PREARM_CHECK]);

    statusLabelVector[29][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_OBSTACLE_AVOIDANCE)/MAV_SYS_STATUS_OBSTACLE_AVOIDANCE]);
    statusLabelVector[29][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_OBSTACLE_AVOIDANCE)/MAV_SYS_STATUS_OBSTACLE_AVOIDANCE]);
    statusLabelVector[29][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_OBSTACLE_AVOIDANCE)/MAV_SYS_STATUS_OBSTACLE_AVOIDANCE]);

    statusLabelVector[30][0]->setPixmap(statusCircles[(present & MAV_SYS_STATUS_SENSOR_PROPULSION)/MAV_SYS_STATUS_SENSOR_PROPULSION]);
    statusLabelVector[30][1]->setPixmap(statusCircles[(enabled & MAV_SYS_STATUS_SENSOR_PROPULSION)/MAV_SYS_STATUS_SENSOR_PROPULSION]);
    statusLabelVector[30][2]->setPixmap(statusCircles[(health & MAV_SYS_STATUS_SENSOR_PROPULSION)/MAV_SYS_STATUS_SENSOR_PROPULSION]);
}
