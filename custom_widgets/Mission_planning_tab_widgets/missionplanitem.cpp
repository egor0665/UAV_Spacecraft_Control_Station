#include "missionplanitem.h"

#include <QDebug>
#include <QLocale>


MissionPlanItemWidget::~MissionPlanItemWidget()
{
    delete(missionItemTypeCB);
    delete(frameTypeCB);
    delete(param1LE);
    delete(param2LE);
    delete(param3LE);
    delete(param4LE);
    delete(param5LE);
    delete(param6LE);
    delete(param7LE);
    delete(deleteItemButton);
    delete(moveUpwardsButton);
    delete(moveDownwardsButton);
    delete(info1LBL);
    delete(info2LBL);
    delete(info3LBL);
    delete(info4LBL);
}


void MissionPlanItemWidget::initInfoLabels()
{
    info1LBL = new QLabel();
    info2LBL = new QLabel();
    info3LBL = new QLabel();
    info4LBL = new QLabel();
}
MissionPlanItemWidget::MissionPlanItemWidget(int itemNum, int missionItemType, int frameType, QString param1, QString param2, QString param3, QString param4, QString param5, QString param6, QString param7, QWidget *parent) : QWidget(parent)
{
    this->planItem.itemNum = itemNum;
    this->planItem.missionItemType = missionItemType;
    this->planItem.frameType = frameType;

    initComboBoxes();
    missionItemTypeCB->setCurrentIndex(missionItemTypeCB->findText(MISSION_ITEMS[missionItemType]));
    frameTypeCB->setCurrentIndex(frameTypeCB->findText(MISSION_PLAN_ITEM_FRAME_TYPES[frameType]));

    this->planItem.param1 = param1.toFloat();
    this->planItem.param2 = param2.toFloat();
    this->planItem.param3 = param3.toFloat();
    this->planItem.param4 = param4.toFloat();
    this->planItem.param5X = param5.toFloat();
    this->planItem.param6Y = param6.toFloat();
    this->planItem.param7Z = param7.toFloat();

    setParamInfo(missionItemType);

    initLineEdits();
    param1LE->setText(param1);
    param2LE->setText(param2);
    param3LE->setText(param3);
    param4LE->setText(param4);
    param5LE->setText(param5);
    param6LE->setText(param6);
    param7LE->setText(param7);

    initInfoLabels();
    initButtons();
}

MissionPlanItemWidget::MissionPlanItemWidget(int itemNum, int missionItemType, int frameType, float param1, float param2, float param3, float param4, float param5, float param6, float param7, QWidget *parent) : QWidget(parent)
{
    this->planItem.itemNum = itemNum;
    this->planItem.missionItemType = missionItemType;
    this->planItem.frameType = frameType;

    initComboBoxes();
    missionItemTypeCB->setCurrentIndex(missionItemTypeCB->findText(MISSION_ITEMS[missionItemType]));
    frameTypeCB->setCurrentIndex(frameTypeCB->findText(MISSION_PLAN_ITEM_FRAME_TYPES[frameType]));


    this->planItem.param1 = param1;
    this->planItem.param2 = param2;
    this->planItem.param3 = param3;
    this->planItem.param4 = param4;
    this->planItem.param5X = param5;
    this->planItem.param6Y = param6;
    this->planItem.param7Z = param7;

    setParamInfo(missionItemType);

    initLineEdits();
    param1LE->setText(QString::number(param1));
    param2LE->setText(QString::number(param2));
    param3LE->setText(QString::number(param3));
    param4LE->setText(QString::number(param4));
    param5LE->setText(QString::number(param5));
    param6LE->setText(QString::number(param6));
    param7LE->setText(QString::number(param7));

    initInfoLabels();
    initButtons();
}


MissionPlanItemWidget::MissionPlanItemWidget(int itemNum, QWidget *parent) : QWidget(parent)
{
    this->planItem.itemNum = itemNum;
    this->planItem.missionItemType = MAV_CMD_NAV_WAYPOINT;
    this->planItem.frameType = FRAME_TYPE_GLOBAL;

    initComboBoxes();
    missionItemTypeCB->setCurrentIndex(missionItemTypeCB->findText(MISSION_ITEMS[MAV_CMD_NAV_WAYPOINT]));
    frameTypeCB->setCurrentIndex(frameTypeCB->findText(MISSION_PLAN_ITEM_FRAME_TYPES[FRAME_TYPE_GLOBAL]));

    initComboBoxes();
    planItem.param1 = 0;
    planItem.param2 = 0;
    planItem.param3 = 0;
    planItem.param4 = 0;
    planItem.param5X = 0;
    planItem.param6Y = 0;
    planItem.param7Z = 0;

    planItem.param1Info = "Hold T.",
            planItem.param2Info = "Acc. R.",
            planItem.param3Info = "Pass R.",
            planItem.param4Info = "Yaw",
            planItem.param5Info = "X",
            planItem.param6Info = "Y",
            planItem.param7Info = "Z";

    initLineEdits();
    param1LE->setText("0");
    param2LE->setText("0");
    param3LE->setText("0");
    param4LE->setText("0");
    param5LE->setText("0");
    param6LE->setText("0");
    param7LE->setText("0");

    initInfoLabels();
    initButtons();
}

QStringList MissionPlanItemWidget::getParamInfo()
{
    QStringList result = {};
    result.append(planItem.param1Info);
    result.append(planItem.param2Info);
    result.append(planItem.param3Info);
    result.append(planItem.param4Info);
    result.append(planItem.param5Info);
    result.append(planItem.param6Info);
    result.append(planItem.param7Info);
    return result;
}

void MissionPlanItemWidget::handleParamValue1Changed(const QString &newVal)
{
    QLocale c(QLocale::German);
    if (abs(c.toFloat(newVal))>abs(newVal.toFloat()))
        planItem.param1 = c.toFloat(newVal);
    else
        planItem.param1 = newVal.toFloat();
    emit missionItemUpdateVehicleDisplayWidgetMissionPlan();
}
void MissionPlanItemWidget::handleParamValue2Changed(const QString &newVal)
{
    QLocale c(QLocale::German);
    if (abs(c.toFloat(newVal))>abs(newVal.toFloat()))
        planItem.param2 = c.toFloat(newVal);
    else
        planItem.param2 = newVal.toFloat();
    emit missionItemUpdateVehicleDisplayWidgetMissionPlan();
}
void MissionPlanItemWidget::handleParamValue3Changed(const QString &newVal)
{
    QLocale c(QLocale::German);
    if (abs(c.toFloat(newVal))>abs(newVal.toFloat()))
        planItem.param3 = c.toFloat(newVal);
    else
        planItem.param3 = newVal.toFloat();
    emit missionItemUpdateVehicleDisplayWidgetMissionPlan();
}
void MissionPlanItemWidget::handleParamValue4Changed(const QString &newVal)
{
    QLocale c(QLocale::German);
    if (abs(c.toFloat(newVal))>abs(newVal.toFloat()))
        planItem.param4 = c.toFloat(newVal);
    else
        planItem.param4 = newVal.toFloat();
    emit missionItemUpdateVehicleDisplayWidgetMissionPlan();
}
void MissionPlanItemWidget::handleParamValue5Changed(const QString &newVal)
{
    QLocale c(QLocale::German);
    if (abs(c.toFloat(newVal))>abs(newVal.toFloat()))
        planItem.param5X = c.toFloat(newVal);
    else
        planItem.param5X = newVal.toFloat();
    emit missionItemUpdateVehicleDisplayWidgetMissionPlan();
}
void MissionPlanItemWidget::handleParamValue6Changed(const QString &newVal)
{
    QLocale c(QLocale::German);
    if (abs(c.toFloat(newVal))>abs(newVal.toFloat()))
        planItem.param6Y = c.toFloat(newVal);
    else
        planItem.param6Y = newVal.toFloat();
    emit missionItemUpdateVehicleDisplayWidgetMissionPlan();
}
void MissionPlanItemWidget::handleParamValue7Changed(const QString &newVal)
{
    QLocale c(QLocale::German);
    if (abs(c.toFloat(newVal))>abs(newVal.toFloat()))
        planItem.param7Z = c.toFloat(newVal);
    else
        planItem.param7Z = newVal.toFloat();
    emit missionItemUpdateVehicleDisplayWidgetMissionPlan();
}

void MissionPlanItemWidget::handleFrameTypeChanged(int index)
{
    planItem.frameType = frameTypeCB->itemData(index).toInt();

    emit missionItemUpdateVehicleDisplayWidgetMissionPlan();
}

void MissionPlanItemWidget::handleMissionItemTypeChanged(int index)
{
    planItem.missionItemType = missionItemTypeCB->itemData(index).toInt();
    setParamInfo(missionItemTypeCB->itemData(index).toInt());
    emit missionItemUpdateVehicleDisplayWidgetMissionPlan();
}


void MissionPlanItemWidget::handleDeleteItemButtonClicked()
{
    emit itemDeleteButtonClicked(planItem.itemNum);
    delete(this);
}

void MissionPlanItemWidget::handleMoveUpwardsButtonClicked()
{
    emit itemMoveUpwardsButtonClicked(planItem.itemNum);
}

void MissionPlanItemWidget::handleMoveDownwardsButtonClicked()
{
    emit itemMoveDownwardsButtonClicked(planItem.itemNum);
}


void MissionPlanItemWidget::setParamInfo(int itemType)
{
    switch(itemType)
    {
    case (MAV_CMD_NAV_WAYPOINT):
    {
        planItem.param1Info = "Hold T.",
                planItem.param2Info = "Accept R.",
                planItem.param3Info = "Pass R.",
                planItem.param4Info = "Yaw",
                planItem.param5Info = "X",
                planItem.param6Info = "Y",
                planItem.param7Info = "Z";
        break;
    }
    case (MAV_CMD_NAV_RETURN_TO_LAUNCH):
    {
        planItem.param1Info = "-",
                planItem.param2Info = "-",
                planItem.param3Info = "-",
                planItem.param4Info = "-",
                planItem.param5Info = "-",
                planItem.param6Info = "-",
                planItem.param7Info = "-";
        break;
    }
    case (MAV_CMD_NAV_TAKEOFF):
    {
        planItem.param1Info = "Pitch",
                planItem.param2Info = "-",
                planItem.param3Info = "-",
                planItem.param4Info = "Yaw",
                planItem.param5Info = "X",
                planItem.param6Info = "Y",
                planItem.param7Info = "Z";
        break;
    }
    case (MAV_CMD_NAV_LAND):
    {
        planItem.param1Info = "Ab. Alt",
                planItem.param2Info = "Land M.",
                planItem.param3Info = "-",
                planItem.param4Info = "Yaw",
                planItem.param5Info = "X",
                planItem.param6Info = "Y",
                planItem.param7Info = "Z";
        break;
    }
    case (MAV_CMD_NAV_LOITER_TURNS):
    {
        planItem.param1Info = "Turns",
                planItem.param2Info = "Heading",
                planItem.param3Info = "Radius",
                planItem.param4Info = "Xtrack",
                planItem.param5Info = "X",
                planItem.param6Info = "Y",
                planItem.param7Info = "Z";
        break;
    }
    case (MAV_CMD_NAV_LOITER_TIME):
    {
        planItem.param1Info = "Time",
                planItem.param2Info = "Heading",
                planItem.param3Info = "Radius",
                planItem.param4Info = "Xtrack",
                planItem.param5Info = "X",
                planItem.param6Info = "Y",
                planItem.param7Info = "Z";
        break;
    }
    case (MAV_CMD_NAV_DELAY):
    {
        planItem.param1Info = "Delay",
                planItem.param2Info = "Hour",
                planItem.param3Info = "Minute",
                planItem.param4Info = "Second",
                planItem.param5Info = "-",
                planItem.param6Info = "-",
                planItem.param7Info = "-";
        break;
    }
    case (MAV_CMD_DO_CHANGE_SPEED):
    {
        planItem.param1Info = "Speed Type",
                planItem.param2Info = "Speed",
                planItem.param3Info = "Throttle",
                planItem.param4Info = "-",
                planItem.param5Info = "0",
                planItem.param6Info = "0",
                planItem.param7Info = "0";
        break;
    }
    case (MAV_CMD_DO_SET_HOME):
    {
        planItem.param1Info = "Use Current",
                planItem.param2Info = "Roll",
                planItem.param3Info = "Pitch",
                planItem.param4Info = "Yaw",
                planItem.param5Info = "X",
                planItem.param6Info = "Y",
                planItem.param7Info = "Z";
        break;
    }
    case (MAV_CMD_DO_FENCE_ENABLE):
    {
        planItem.param1Info = "Enable",
                planItem.param2Info = "-",
                planItem.param3Info = "-",
                planItem.param4Info = "-",
                planItem.param5Info = "-",
                planItem.param6Info = "-",
                planItem.param7Info = "-";
        break;
    }
    default:
    {
        planItem.param1Info = "Param1",
                planItem.param2Info = "Param2",
                planItem.param3Info = "Param3",
                planItem.param4Info = "Param4",
                planItem.param5Info = "Param5",
                planItem.param6Info = "Param6",
                planItem.param7Info = "Param7";
        break;
    }
    }
}

void MissionPlanItemWidget::initButtons()
{
    deleteItemButton = new QPushButton();
    deleteItemButton->setText("X");
    connect(deleteItemButton, &QPushButton::clicked, this, &MissionPlanItemWidget::handleDeleteItemButtonClicked);
    moveUpwardsButton = new QPushButton();
    moveUpwardsButton->setText("↑");
    connect(moveUpwardsButton, &QPushButton::clicked, this, &MissionPlanItemWidget::handleMoveUpwardsButtonClicked);
    moveDownwardsButton = new QPushButton();
    moveDownwardsButton->setText("↓");
    connect(moveDownwardsButton, &QPushButton::clicked, this, &MissionPlanItemWidget::handleMoveDownwardsButtonClicked);

}
void MissionPlanItemWidget::initComboBoxes()
{
    missionItemTypeCB = new QComboBox();
    for(auto e : MISSION_ITEMS.toStdMap())
    {
        missionItemTypeCB->addItem(e.second, e.first);
    }
    connect(missionItemTypeCB, SIGNAL(currentIndexChanged(int)), this, SLOT(handleMissionItemTypeChanged(int)));

    frameTypeCB = new QComboBox();
    for(auto e : MISSION_PLAN_ITEM_FRAME_TYPES.toStdMap())
    {
        frameTypeCB->addItem(e.second, e.first);
    }
    connect(frameTypeCB, SIGNAL(currentIndexChanged(int)), this, SLOT(handleFrameTypeChanged(int)));
}


void MissionPlanItemWidget::initLineEdits()
{
    QDoubleValidator validator(-100, 100, 2);
    validator.setLocale(QLocale::German);
    param1LE = new QLineEdit(this);
    param1LE->setValidator(&validator);
    connect(param1LE, SIGNAL(textChanged(const QString &)), this, SLOT(handleParamValue1Changed(const QString &)));
    param2LE = new QLineEdit(this);
    param2LE->setValidator(&validator);
    connect(param2LE, SIGNAL(textChanged(const QString &)), this, SLOT(handleParamValue2Changed(const QString &)));
    param3LE = new QLineEdit(this);
    param3LE->setValidator(&validator);
    connect(param3LE, SIGNAL(textChanged(const QString &)), this, SLOT(handleParamValue3Changed(const QString &)));
    param4LE = new QLineEdit(this);
    param4LE->setValidator(&validator);
    connect(param4LE, SIGNAL(textChanged(const QString &)), this, SLOT(handleParamValue4Changed(const QString &)));
    param5LE = new QLineEdit(this);
    param5LE->setValidator(&validator);
    connect(param5LE, SIGNAL(textChanged(const QString &)), this, SLOT(handleParamValue5Changed(const QString &)));
    param6LE = new QLineEdit(this);
    param6LE->setValidator(&validator);
    connect(param6LE, SIGNAL(textChanged(const QString &)), this, SLOT(handleParamValue6Changed(const QString &)));
    param7LE = new QLineEdit(this);
    param7LE->setValidator(&validator);
    connect(param7LE, SIGNAL(textChanged(const QString &)), this, SLOT(handleParamValue7Changed(const QString &)));
}


