#include "vehiclemanualcontrolwidget2.h"

#include <QGridLayout>

VehicleManualControlWidget2::VehicleManualControlWidget2(QWidget *parent) : QWidget(parent)
{
    initButtons();
    speedDSB.setMaximumSize(300,300);
    loiterRadDSB.setMaximumSize(300,300);

    mainLayout.setSpacing(2);
    mainLayout.setContentsMargins(5, 5, 5, 5);

    mainLayout.addWidget(&speedDSB,0,0);
    mainLayout.addWidget(&loiterRadDSB,1,0);

    mainLayout.addWidget(&setSpeedButton,0,1);
    mainLayout.addWidget(&setLoiterRadButton,1,1);

    mainLayout.addWidget(&clearTrackButton,0,2);
    mainLayout.addWidget(&joystickButton,1,2);
    mainLayout.addWidget(&sensorButton,2,2);

    mainLayout.addWidget(&autoButton,0,3);
    mainLayout.addWidget(&setWayPointButton,1,3);
    mainLayout.addWidget(&manualControlButton,2,3);

    mainLayout.addWidget(&messageButton,2,0);

    this->setLayout(&mainLayout);
}

void VehicleManualControlWidget2::initButtons()
{
    clearTrackButton.setMaximumSize(300,300);
    clearTrackButton.setText("Очис. путь");

    messageButton.setMaximumSize(300,300);
    messageButton.setText("Сохр. лог");

    setSpeedButton.setMaximumSize(300,300);
    setSpeedButton.setText("Изменить скор.");

    setLoiterRadButton.setMaximumSize(300,300);
    setLoiterRadButton.setText("Уст. рад. безд.");

    joystickButton.setMaximumSize(300,300);
    joystickButton.setText("Джостик");

    autoButton.setMaximumSize(300,300);
    autoButton.setText("АВТО");

    setWayPointButton.setMaximumSize(300,300);
    setWayPointButton.setText("Уст. пут. т.");

    manualControlButton.setMaximumSize(300,300);
    manualControlButton.setText("РУЧНОЙ");

    sensorButton.setMaximumSize(300,300);
    sensorButton.setText("Датчики");
}

VehicleManualControlWidget2::~VehicleManualControlWidget2()
{
}
