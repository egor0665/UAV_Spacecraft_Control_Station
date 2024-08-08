#ifndef DISPLAYATTITUDEWIDGET_H
#define DISPLAYATTITUDEWIDGET_H

#include "custom_widgets/tabmodule.h"

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <mavlink/ardupilotmega/mavlink.h>

//void initMainLabel(QLabel *label, int fontSize, int fontWeight, QString color);

class DisplayAttitudeWidget: public QWidget, public tabModule
{
    Q_OBJECT
    QGridLayout mainLayout;
    QLabel rollLBL,
            pitchLBL,
            yawLBL,
            rollSpeedLBL,
            pitchSpeedLBL,
            yawSpeedLBL;
    QLabel rollLBLTitleLBL,
            pitchLBLTitleLBL,
            yawLBLTitleLBL,
            rollSpeedLBLTitleLBL,
            pitchSpeedLBLTitleLBL,
            yawSpeedLBLTitleLBL;
    float roll, pitch, yaw, rollspeed, pitchspeed, yawspeed;
public:
    DisplayAttitudeWidget(QWidget *parent = nullptr);
    ~DisplayAttitudeWidget();
    void updateData(mavlink_attitude_t message);
protected:
    void displayData();
    void initMainLabel(QLabel *label, int fontSize, int fontWeight, QString color);
};

#endif // DISPLAYATTITUDEWIDGET_H
