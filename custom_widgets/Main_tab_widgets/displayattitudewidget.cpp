#include "displayattitudewidget.h"

#include <QGridLayout>

DisplayAttitudeWidget::DisplayAttitudeWidget(QWidget *parent) : QWidget(parent)
{
    rollLBL.setText("0.00");
    initMainLabel(&rollLBL, 40,10,"rgb(200, 0, 0)");
    pitchLBL.setText("0.00");
    initMainLabel(&pitchLBL, 40,10,"rgb(0, 200, 0)");
    yawLBL.setText("0.00");
    initMainLabel(&yawLBL, 40,10,"rgb(0, 0, 200)");
    rollSpeedLBL.setText("0.00");
    initMainLabel(&rollSpeedLBL, 40,10,"rgb(200, 128, 0)");
    pitchSpeedLBL.setText("0.00");
    initMainLabel(&pitchSpeedLBL, 40,10,"rgb(0, 200, 200)");
    yawSpeedLBL.setText("0.00");
    initMainLabel(&yawSpeedLBL, 40,10,"rgb(128, 0, 200)");

    rollLBLTitleLBL.setText("Крен °");
    initMainLabel(&rollLBLTitleLBL, 15,10, "#E1E2E2");
    pitchLBLTitleLBL.setText("Тангаж °");
    initMainLabel(&pitchLBLTitleLBL, 15,10,"#E1E2E2");
    yawLBLTitleLBL.setText("Рысканье °");
    initMainLabel(&yawLBLTitleLBL, 15,10,"#E1E2E2");
    rollSpeedLBLTitleLBL.setText("Скор. Крена °/сек");
    initMainLabel(&rollSpeedLBLTitleLBL, 15,10,"#E1E2E2");
    pitchSpeedLBLTitleLBL.setText("Скор. Тангажа °/сек");
    initMainLabel(&pitchSpeedLBLTitleLBL, 15,10,"#E1E2E2");
    yawSpeedLBLTitleLBL.setText("Скор. Рысканья °/сек");
    initMainLabel(&yawSpeedLBLTitleLBL, 15,10,"#E1E2E2");

    mainLayout.addWidget(&rollLBLTitleLBL,0,0);
    mainLayout.addWidget(&pitchLBLTitleLBL,0,1);
    mainLayout.addWidget(&yawLBLTitleLBL,0,2);

    mainLayout.addWidget(&rollLBL,1,0);
    mainLayout.addWidget(&pitchLBL,1,1);
    mainLayout.addWidget(&yawLBL,1,2);

    mainLayout.addWidget(&rollSpeedLBLTitleLBL,2,0);
    mainLayout.addWidget(&pitchSpeedLBLTitleLBL,2,1);
    mainLayout.addWidget(&yawSpeedLBLTitleLBL,2,2);

    mainLayout.addWidget(&rollSpeedLBL,3,0);
    mainLayout.addWidget(&pitchSpeedLBL,3,1);
    mainLayout.addWidget(&yawSpeedLBL,3,2);

    mainLayout.setMargin(0);
    this->setLayout(&mainLayout);
}

void DisplayAttitudeWidget::initMainLabel(QLabel *label, int fontSize, int fontWeight, QString color)
{
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label->setFont(QFont("MS Shell Dlg 2", fontSize, fontWeight));
    label->setStyleSheet("QLabel { color : " + color + "; }");
}

DisplayAttitudeWidget::~DisplayAttitudeWidget()
{
}

void DisplayAttitudeWidget::updateData(mavlink_attitude_t message)
{
    const float radToDegMultiplier = 57.3;
    roll = message.roll * radToDegMultiplier;
    pitch = message.pitch * radToDegMultiplier;
    yaw = message.yaw * radToDegMultiplier;
    rollspeed = message.rollspeed * radToDegMultiplier;
    pitchspeed = message.pitchspeed * radToDegMultiplier;
    yawspeed = message.yawspeed * radToDegMultiplier;
    if (!sleep)
        displayData();
}

void DisplayAttitudeWidget::displayData()
{
    rollLBL.setText(QString::number(roll , 'f', 2));
    pitchLBL.setText(QString::number(pitch, 'f', 2));
    yawLBL.setText(QString::number(yaw, 'f', 2));
    rollSpeedLBL.setText(QString::number(rollspeed, 'f', 2));
    pitchSpeedLBL.setText(QString::number(pitchspeed, 'f', 2));
    yawSpeedLBL.setText(QString::number(yawspeed, 'f', 2));
}
