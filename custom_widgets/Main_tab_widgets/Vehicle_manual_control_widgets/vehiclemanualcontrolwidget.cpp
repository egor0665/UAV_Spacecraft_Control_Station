#include "vehiclemanualcontrolwidget.h"

#include <QGridLayout>
#include "structs.h"


VehicleManualControlWidget::VehicleManualControlWidget(QWidget *parent) : QWidget(parent)
{
    initButtons();
    missionModeCB.setMaximumSize(300,300);
    for(auto e : SPECIAL_COMMANDS.toStdMap())
    {
        missionModeCB.addItem(e.second, e.first);
    }
    wayPointCB.setMaximumSize(300,300);
    modeCB.setMaximumSize(300,300);
    for(auto e : FLIGHT_MODES.toStdMap())
    {
        modeCB.addItem(e.second, e.first);
    }
    mountCB.setMaximumSize(300,300);

    flyToCordsXDSB.setMaximumSize(300,300);
    flyToCordsXDSB.setRange(-1000,1000);
    flyToCordsYDSB.setMaximumSize(300,300);
    flyToCordsYDSB.setRange(-1000,1000);
    flyToCordsZDSB.setMaximumSize(300,300);
    flyToCordsZDSB.setRange(-1000,1000);

    mainLayout.setSpacing(2);
    mainLayout.setContentsMargins(5, 5, 5, 5);

    mainLayout.addWidget(&missionModeCB,0,0);
    mainLayout.addWidget(&wayPointCB,1,0);
    mainLayout.addWidget(&modeCB,2,0);
    mainLayout.addWidget(&mountCB,3,0);

    mainLayout.addWidget(&executeButton,0,1);
    mainLayout.addWidget(&addWayPointButton,1,1);
    mainLayout.addWidget(&setModeButton,2,1);
    mainLayout.addWidget(&setMountButton,3,1);

    mainLayout.addWidget(&flyToCordsXDSB,0,2);
    mainLayout.addWidget(&flyToCordsYDSB,1,2);
    mainLayout.addWidget(&flyToCordsZDSB,2,2);

    mainLayout.addWidget(&flyToCordsButton,0,3);
    mainLayout.addWidget(&flyToAltCordsButton,1,3);
    mainLayout.addWidget(&homeButton,2,3);
    mainLayout.addWidget(&setHomeHereButton,3,3);

    mainLayout.addWidget(&armButton,0,4);
    mainLayout.addWidget(&disarmButton,1,4);
    mainLayout.addWidget(&takeOffButton,2,4);
    mainLayout.addWidget(&landButton,3,4);

    this->setLayout(&mainLayout);
}

VehicleManualControlWidget::~VehicleManualControlWidget()
{
}

void VehicleManualControlWidget::initButtons()
{
    executeButton.setMaximumSize(300,300);
    executeButton.setText("Выполнить");
    connect(&executeButton, &QPushButton::clicked,this,&VehicleManualControlWidget::handleExecuteButtonClicked);

    setModeButton.setMaximumSize(300,300);
    setModeButton.setText("Уст. режим");
    connect(&setModeButton, &QPushButton::clicked,this,&VehicleManualControlWidget::handleSetModeButtonClicked);

    homeButton.setMaximumSize(300,300);
    homeButton.setText("ДОМ");
    connect(&homeButton, &QPushButton::clicked,this,&VehicleManualControlWidget::handleHomeButtonClicked);

    setMountButton.setMaximumSize(300,300);
    setMountButton.setText("-");  //Уст. маунт
    connect(&setMountButton, &QPushButton::clicked,this,&VehicleManualControlWidget::handleSetMountButtonClicked);

    armButton.setMaximumSize(300,300);
    armButton.setText("Зап. двиг.");
    connect(&armButton, &QPushButton::clicked,this,&VehicleManualControlWidget::handleArmButtonClicked);

    disarmButton.setMaximumSize(300,300);
    disarmButton.setText("Ост. двиг.");
    connect(&disarmButton, &QPushButton::clicked,this,&VehicleManualControlWidget::handleDisarmButtonClicked);

    takeOffButton.setMaximumSize(300,300);
    takeOffButton.setText("Взлететь");
    connect(&takeOffButton, &QPushButton::clicked,this,&VehicleManualControlWidget::handleTakeOffButtonClicked);

    landButton.setMaximumSize(300,300);
    landButton.setText("Сесть");
    connect(&landButton, &QPushButton::clicked,this,&VehicleManualControlWidget::handleLandButtonClicked);

    flyToCordsButton.setMaximumSize(300,300);
    flyToCordsButton.setText("Лет. XZ");
    connect(&flyToCordsButton, &QPushButton::clicked,this,&VehicleManualControlWidget::handleFlyToCordsButtonClicked);

    flyToAltCordsButton.setMaximumSize(300,300);
    flyToAltCordsButton.setText("Лет. XYZ");
    connect(&flyToAltCordsButton, &QPushButton::clicked,this,&VehicleManualControlWidget::handleFlyToAltCordsButtonClicked);

    addWayPointButton.setMaximumSize(300,300);
    addWayPointButton.setText("Доб. точку");
    connect(&addWayPointButton, &QPushButton::clicked,this,&VehicleManualControlWidget::handleAddWayPointButtonClicked);

    setHomeHereButton.setMaximumSize(300,300);
    setHomeHereButton.setText("Уст. ДОМ");
    connect(&setHomeHereButton, &QPushButton::clicked,this,&VehicleManualControlWidget::handleSetHomeHereButtonClicked);
}

void VehicleManualControlWidget::setButtonStyle()
{

}

void VehicleManualControlWidget::handleExecuteButtonClicked()
{
    emit manualControlWidgetMissionSetMode(missionModeCB.itemData(mountCB.currentIndex()).toInt(), flyToCordsXDSB.value(), flyToCordsZDSB.value(), -flyToCordsYDSB.value());
}

void VehicleManualControlWidget::handleSetModeButtonClicked()
{
    emit manualControlWidgetSetMode(modeCB.itemData(modeCB.currentIndex()).toInt());
}

void VehicleManualControlWidget::handleHomeButtonClicked()
{
    emit manualControlWidgetHome();
}

void VehicleManualControlWidget::handleSetMountButtonClicked()
{
    emit manualControlWidgetSetMount(mountCB.itemData(mountCB.currentIndex()).toInt());
}

void VehicleManualControlWidget::handleArmButtonClicked()
{
    emit manualControlWidgetArm();
}

void VehicleManualControlWidget::handleDisarmButtonClicked()
{
    emit manualControlWidgetDisarm();
}

void VehicleManualControlWidget::handleTakeOffButtonClicked()
{
    attitudeDialog = new ValueDialog("Введите высоту", VALUE_TYPE_FLOAT, this);
    connect(attitudeDialog,&ValueDialog::gotDialogResult,this,&VehicleManualControlWidget::handleGotTakeOffAltitudeValue);
    attitudeDialog->show();
}

void VehicleManualControlWidget::handleGotTakeOffAltitudeValue(int result, QVariant value)
{
    disconnect(attitudeDialog,&ValueDialog::gotDialogResult,this,&VehicleManualControlWidget::handleGotTakeOffAltitudeValue);
    delete (attitudeDialog);
    if (result == VALUE_DIALOG_GOT_RESULT)
        emit manualControlWidgetTakeOff(value.toFloat());
    else
        return;
    return;
}

void VehicleManualControlWidget::handleLandButtonClicked()
{
    emit manualControlWidgetLand();
}

void VehicleManualControlWidget::handleFlyToCordsButtonClicked()
{
    emit manualControlWidgetFlyToCords(flyToCordsXDSB.value(), flyToCordsYDSB.value());
}

void VehicleManualControlWidget::handleFlyToAltCordsButtonClicked()
{
    emit manualControlWidgetFlyToAltCords(flyToCordsXDSB.value(), flyToCordsZDSB.value(), -flyToCordsYDSB.value());
}

void VehicleManualControlWidget::handleAddWayPointButtonClicked()
{
    emit manualControlWidgetAddWayPoint();
}

void VehicleManualControlWidget::handleSetHomeHereButtonClicked()
{
    emit manualControlWidgetSetHomeHere();
}

