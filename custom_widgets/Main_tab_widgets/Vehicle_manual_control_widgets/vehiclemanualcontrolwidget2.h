#ifndef VEHICLEMANUALCONTROLWIDGET2_H
#define VEHICLEMANUALCONTROLWIDGET2_H

#include "custom_widgets/tabmodule.h"

#include <QDoubleSpinBox>
#include <QPushButton>
#include <QGridLayout>



class VehicleManualControlWidget2: public QWidget, public tabModule
{
    Q_OBJECT
    QGridLayout mainLayout;
    QPushButton clearTrackButton,
                messageButton,
                setSpeedButton,
                setLoiterRadButton,
                joystickButton,
                sensorButton,
                autoButton,
                setWayPointButton,
                manualControlButton;

    QDoubleSpinBox speedDSB, loiterRadDSB;
public:
    VehicleManualControlWidget2(QWidget *parent = nullptr);
    ~VehicleManualControlWidget2();
protected:
    void initButtons();
};

#endif // VEHICLEMANUALCONTROLWIDGET2_H
