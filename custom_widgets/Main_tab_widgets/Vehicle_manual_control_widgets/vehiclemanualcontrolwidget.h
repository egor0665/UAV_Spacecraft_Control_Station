#ifndef VEHICLEMANUALCONTROLWIDGET_H
#define VEHICLEMANUALCONTROLWIDGET_H

#include "custom_widgets/tabmodule.h"
//#include <structs.h>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>
#include <custom_dialogs/valuedialog.h>



class VehicleManualControlWidget: public QWidget, public tabModule
{
    Q_OBJECT
    QPushButton executeButton, addWayPointButton,
                setModeButton, homeButton,
                setMountButton, armButton,
                disarmButton;

    QPushButton takeOffButton, landButton, flyToCordsButton,
                flyToAltCordsButton, setHomeHereButton;

    QComboBox modeCB, wayPointCB, missionModeCB, mountCB;

    QDoubleSpinBox flyToCordsXDSB, flyToCordsYDSB, flyToCordsZDSB;

    ValueDialog *attitudeDialog;

    QGridLayout mainLayout;
public:
    VehicleManualControlWidget(QWidget *parent = nullptr);
    ~VehicleManualControlWidget();
protected:
    void setButtonStyle();
    void initButtons();
protected slots:
    void handleExecuteButtonClicked();
    void handleSetModeButtonClicked();
    void handleHomeButtonClicked();
    void handleSetMountButtonClicked();
    void handleArmButtonClicked();
    void handleDisarmButtonClicked();
    void handleTakeOffButtonClicked();
    void handleLandButtonClicked();
    void handleFlyToCordsButtonClicked();
    void handleFlyToAltCordsButtonClicked();
    void handleAddWayPointButtonClicked();
    void handleSetHomeHereButtonClicked();
    void handleGotTakeOffAltitudeValue(int result, QVariant value);
signals:
    void manualControlWidgetMissionSetMode(int executeCommand, float x, float y, float z);
    void manualControlWidgetSetMode(int mode);
    void manualControlWidgetHome();
    void manualControlWidgetSetMount(int mount);
    void manualControlWidgetArm();
    void manualControlWidgetDisarm();
    void manualControlWidgetTakeOff(int altitude);
    void manualControlWidgetLand();
    void manualControlWidgetFlyToCords(float x, float z);
    void manualControlWidgetFlyToAltCords(float x, float y, float z);
    void manualControlWidgetAddWayPoint();
    void manualControlWidgetSetHomeHere();
};

#endif // VEHICLEMANUALCONTROLWIDGET_H
