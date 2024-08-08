#ifndef VEHICLESENSORSINFOWIDGET_H
#define VEHICLESENSORSINFOWIDGET_H

#include "custom_widgets/tabmodule.h"

#include <QWidget>
#include <QLabel>
#include <QMap>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <string.h>
#include <inttypes.h>
#include <fstream>
#include <signal.h>
#include <time.h>
#include <QTableWidget>
#include <sys/time.h>

#include <mavlink/ardupilotmega/mavlink.h>

const int SENSOR_NUM = 31;

class VehicleSensorsInfoWidget: public QWidget, public tabModule
{
    Q_OBJECT
    QVector<QPixmap> statusCircles;
    QTableWidget mainTable;
    QVector<QVector<QLabel*>> statusLabelVector;

    unsigned int present;
    unsigned int enabled;
    unsigned int health;

public:
    VehicleSensorsInfoWidget(QWidget *parent = nullptr);
    ~VehicleSensorsInfoWidget();
    void updateSysStatus(mavlink_sys_status_t message);
protected:
    void displaySensorInfo();
};

#endif // VEHICLESENSORSINFOWIDGET_H

//1	MAV_SYS_STATUS_SENSOR_3D_GYRO	0x01 3D gyro
//2	MAV_SYS_STATUS_SENSOR_3D_ACCEL	0x02 3D accelerometer
//4	MAV_SYS_STATUS_SENSOR_3D_MAG	0x04 3D magnetometer
//8	MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE	0x08 absolute pressure
//16	MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE	0x10 differential pressure
//32	MAV_SYS_STATUS_SENSOR_GPS	0x20 GPS
//64	MAV_SYS_STATUS_SENSOR_OPTICAL_FLOW	0x40 optical flow
//128	MAV_SYS_STATUS_SENSOR_VISION_POSITION	0x80 computer vision position
//256	MAV_SYS_STATUS_SENSOR_LASER_POSITION	0x100 laser based position
//512	MAV_SYS_STATUS_SENSOR_EXTERNAL_GROUND_TRUTH	0x200 external ground truth (Vicon or Leica)
//1024	MAV_SYS_STATUS_SENSOR_ANGULAR_RATE_CONTROL	0x400 3D angular rate control
//2048	MAV_SYS_STATUS_SENSOR_ATTITUDE_STABILIZATION	0x800 attitude stabilization
//4096	MAV_SYS_STATUS_SENSOR_YAW_POSITION	0x1000 yaw position
//8192	MAV_SYS_STATUS_SENSOR_Z_ALTITUDE_CONTROL	0x2000 z/altitude control
//16384	MAV_SYS_STATUS_SENSOR_XY_POSITION_CONTROL	0x4000 x/y position control
//32768	MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS	0x8000 motor outputs / control
//65536	MAV_SYS_STATUS_SENSOR_RC_RECEIVER	0x10000 rc receiver
//131072	MAV_SYS_STATUS_SENSOR_3D_GYRO2	0x20000 2nd 3D gyro
//262144	MAV_SYS_STATUS_SENSOR_3D_ACCEL2	0x40000 2nd 3D accelerometer
//524288	MAV_SYS_STATUS_SENSOR_3D_MAG2	0x80000 2nd 3D magnetometer
//1048576	MAV_SYS_STATUS_GEOFENCE	0x100000 geofence
//2097152	MAV_SYS_STATUS_AHRS	0x200000 AHRS subsystem health
//4194304	MAV_SYS_STATUS_TERRAIN	0x400000 Terrain subsystem health
//8388608	MAV_SYS_STATUS_REVERSE_MOTOR	0x800000 Motors are reversed
//16777216	MAV_SYS_STATUS_LOGGING	0x1000000 Logging
//33554432	MAV_SYS_STATUS_SENSOR_BATTERY	0x2000000 Battery
//67108864	MAV_SYS_STATUS_SENSOR_PROXIMITY	0x4000000 Proximity
//134217728	MAV_SYS_STATUS_SENSOR_SATCOM	0x8000000 Satellite Communication
//268435456	MAV_SYS_STATUS_PREARM_CHECK	0x10000000 pre-arm check status. Always healthy when armed
//536870912	MAV_SYS_STATUS_OBSTACLE_AVOIDANCE	0x20000000 Avoidance/collision prevention
//1073741824	MAV_SYS_STATUS_SENSOR_PROPULSION	0x40000000 propulsion (actuator, esc, motor or propellor)
//2147483648	MAV_SYS_STATUS_EXTENSION_USED	0x80000000 Extended bit-field are used for further sensor status bits (needs to be set in onboard_control_sensors_present only)

