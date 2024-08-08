#ifndef DRONESTATUSWIDGET_H
#define DRONESTATUSWIDGET_H

#include "C:/Qt/5.15.2/mingw81_32/GroundControlStation/mavlink/common/mavlink.h"
#include <QWidget>
#include <QLabel>

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
#include <sys/time.h>

                                                // bit number  876543210987654321
#define MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_POSITION     0b0000110111111000
#define MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_VELOCITY     0b0000110111000111
#define MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_ACCELERATION 0b0000110000111111
#define MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_FORCE        0b0000111000111111
#define MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_YAW_ANGLE    0b0000100111111111
#define MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_YAW_RATE     0b0000010111111111

#define MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_TAKEOFF      0x1000
#define MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_LAND         0x2000
#define MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_LOITER       0x3000
#define MAVLINK_MSG_SET_POSITION_TARGET_LOCAL_NED_IDLE         0x4000


struct mavlinkDataSfa
{
    mavlink_sys_status_t sysStatus;
//    onboard_control_sensors_present	uint32_t		MAV_SYS_STATUS_SENSOR	Bitmap showing which onboard controllers and sensors are present. Value of 0: not present. Value of 1: present.
//    onboard_control_sensors_enabled	uint32_t		MAV_SYS_STATUS_SENSOR	Bitmap showing which onboard controllers and sensors are enabled: Value of 0: not enabled. Value of 1: enabled.
//    onboard_control_sensors_health	uint32_t		MAV_SYS_STATUS_SENSOR	Bitmap showing which onboard controllers and sensors have an error (or are operational). Value of 0: error. Value of 1: healthy.
//    load	uint16_t	d%		Maximum usage in percent of the mainloop time. Values: [0-1000] - should always be below 1000
//    voltage_battery	uint16_t	mV		Battery voltage, UINT16_MAX: Voltage not sent by autopilot
//    current_battery	int16_t	cA		Battery current, -1: Current not sent by autopilot
//    battery_remaining	int8_t	%		Battery energy remaining, -1: Battery remaining energy not sent by autopilot
//    drop_rate_comm	uint16_t	c%		Communication drop rate, (UART, I2C, SPI, CAN), dropped packets on all links (packets that were corrupted on reception on the MAV)
//    errors_comm	uint16_t			Communication errors (UART, I2C, SPI, CAN), dropped packets on all links (packets that were corrupted on reception on the MAV)
//    errors_count1	uint16_t			Autopilot-specific errors
//    errors_count2	uint16_t			Autopilot-specific errors
//    errors_count3	uint16_t			Autopilot-specific errors
//    errors_count4	uint16_t			Autopilot-specific errors
    mavlink_system_time_t systemTimeStatus;
//    time_unix_usec	uint64_t	us	Timestamp (UNIX epoch time).
//    time_boot_ms	uint32_t	ms	Timestamp (time since system boot).
    mavlink_attitude_t attitudeStatus;
//    time_boot_ms	uint32_t	ms	Timestamp (time since system boot).
//    roll	float	rad	Roll angle (-pi..+pi)
//    pitch	float	rad	Pitch angle (-pi..+pi)
//    yaw	float	rad	Yaw angle (-pi..+pi)
//    rollspeed	float	rad/s	Roll angular speed
//    pitchspeed	float	rad/s	Pitch angular speed
//    yawspeed	float	rad/s	Yaw angular speed
    mavlink_local_position_ned_t localPositionStatus;
//    time_boot_ms	uint32_t	ms	Timestamp (time since system boot).
//    x	float	m	X Position
//    y	float	m	Y Position
//    z	float	m	Z Position
//    vx	float	m/s	X Speed
//    vy	float	m/s	Y Speed
//    vz	float	m/s	Z Speed
    mavlink_global_position_int_t globalPositionStatus;
//    time_boot_ms	uint32_t	ms	Timestamp (time since system boot).
//    lat	int32_t	degE7	Latitude, expressed
//    lon	int32_t	degE7	Longitude, expressed
//    alt	int32_t	mm	Altitude (MSL). Note that virtually all GPS modules provide both WGS84 and MSL.
//    relative_alt	int32_t	mm	Altitude above ground
//    vx	int16_t	cm/s	Ground X Speed (Latitude, positive north)
//    vy	int16_t	cm/s	Ground Y Speed (Longitude, positive east)
//    vz	int16_t	cm/s	Ground Z Speed (Altitude, positive down)
//    hdg	uint16_t	cdeg	Vehicle heading (yaw angle), 0.0..359.99 degrees. If unknown, set to: UINT16_MAX


    mavlinkDataSfa(){};
};


class DroneStatusWidget: public QWidget
{
//    Q_OBJECT

    mavlinkDataSfa data;

    QLabel *droneNameLBL = new QLabel();

    QLabel *droneStatusCircleLBL = new QLabel();
    QLabel *droneCommStatusCircleLBL = new QLabel();

    QLabel *GPSLBL = new QLabel();

    QLabel *rollLBL = new QLabel(),
            *pitchLBL = new QLabel(),
            *yawLBL = new QLabel();
    QLabel *rollSpeedLBL = new QLabel(),
            *pitchSpeedLBL = new QLabel(),
            *yawSpeedLBL = new QLabel();
    QLabel *localXLBL = new QLabel(),
            *localYLBL = new QLabel(),
            *localZLBL = new QLabel();
    QLabel *localXSpeedLBL = new QLabel(),
            *localYSpeedLBL = new QLabel(),
            *localZSpeedLBL = new QLabel();
    QLabel *latitudeLBL = new QLabel(),
            *longitudeLBL = new QLabel(),
            *altitudeLBL = new QLabel(),
            *relativeAltitudeLBL = new QLabel();
    QLabel *groundXSpeedLBL = new QLabel(),
            *groundYSpeedLBL = new QLabel(),
            *groundZSpeedLBL = new QLabel();
    QLabel *voltageBatteryLBL = new QLabel(),
            *currentBatteryLBL = new QLabel(),
            *batteryRemainingLBL = new QLabel();
    QLabel *dropRateCommLBL = new QLabel(),
            *errorsCommLBL = new QLabel();
    QLabel *errorsCount1LBL = new QLabel(),
            *errorsCount2LBL = new QLabel(),
            *errorsCount3LBL = new QLabel(),
            *errorsCount4LBL = new QLabel();
    QLabel *loadLBL = new QLabel(),
            *timeUnixSecLBL = new QLabel(),
            *timeBootSecLBL = new QLabel();
public:
    DroneStatusWidget();

};

#endif // DRONESTATUSWIDGET_H

