#ifndef MISSIONPLANITEM_H
#define MISSIONPLANITEM_H

#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <structs.h>

typedef enum MISSION_PLAN_ITEM_FRAME_TYPE
{
    FRAME_TYPE_GLOBAL = 0,
    FRAME_TYPE_LOCAL = 1,

} MISSION_PLAN_ITEM_FRAME_TYPE;

const QMap<int,QString> MISSION_PLAN_ITEM_FRAME_TYPES = {
    {FRAME_TYPE_LOCAL, "Относительный"},
    {FRAME_TYPE_GLOBAL, "Абсолютный"}
};
struct MissionPlanItem {
    int itemNum;
    int missionItemType;
    int frameType;
    float param1, param2,
        param3, param4, param5X,
        param6Y,param7Z;

    QString param1Info, param2Info,
            param3Info, param4Info, param5Info,
            param6Info,param7Info;

    QString info1, info2, info3, info4;
    MissionPlanItem(){};
    MissionPlanItem(int itemNum, int missionItemType, int frameType,
                    float param1, float param2, float param3, float param4,
                    float param5X, float param6Y, float param7Z,
                    const QString &param1Info, const QString &param2Info,
                    const QString &param3Info, const QString &param4Info,
                    const QString &param5Info, const QString &param6Info,
                    const QString &param7Info, const QString &info1,
                    const QString &info2, const QString &info3,
                    const QString &info4) :
        itemNum(itemNum),
        missionItemType(missionItemType),
        frameType(frameType),
        param1(param1),
        param2(param2),
        param3(param3),
        param4(param4),
        param5X(param5X),
        param6Y(param6Y),
        param7Z(param7Z),
        param1Info(param1Info),
        param2Info(param2Info),
        param3Info(param3Info),
        param4Info(param4Info),
        param5Info(param5Info),
        param6Info(param6Info),
        param7Info(param7Info),
        info1(info1),
        info2(info2),
        info3(info3),
        info4(info4)
    {}
//public:
//    MissionPlanItem(int itemNum, int missionItemType, int frameType, float param1, float param2, float param3, float param4, float param5X, float param6Y, float param7Z, const QString &param1Info, const QString &param2Info, const QString &param3Info, const QString &param4Info, const QString &param5Info, const QString &param6Info, const QString &param7Info, const QString &info1, const QString &info2, const QString &info3, const QString &info4);
};

class MissionPlanItemWidget: public QWidget
{
    Q_OBJECT
public:
    MissionPlanItem planItem;

    QComboBox *missionItemTypeCB, *frameTypeCB;

    QLineEdit *param1LE, *param2LE, *param3LE,
    *param4LE, *param5LE, *param6LE, *param7LE;

    QPushButton *deleteItemButton;
    QPushButton *moveUpwardsButton, *moveDownwardsButton;

    QLabel *info1LBL, *info2LBL, *info3LBL, *info4LBL;
    ~MissionPlanItemWidget();
    MissionPlanItemWidget(int itemNum, int missionItemType, int frameType, QString param1, QString param2, QString param3, QString param4, QString param5, QString param6, QString param7, QWidget *parent = nullptr);
    MissionPlanItemWidget(int itemNum, QWidget *parent = nullptr);
    QStringList getParamInfo();
    MissionPlanItemWidget(int itemNum, int missionItemType, int frameType, float param1, float param2, float param3, float param4, float param5, float param6, float param7, QWidget *parent = nullptr);

    void initInfoLabels();
protected slots:
    void handleMissionItemTypeChanged(int index);

    void handleDeleteItemButtonClicked();
    void handleMoveUpwardsButtonClicked();
    void handleMoveDownwardsButtonClicked();
    void handleParamValue1Changed(const QString &newVal);
    void handleParamValue2Changed(const QString &newVal);
    void handleParamValue3Changed(const QString &newVal);
    void handleParamValue4Changed(const QString &newVal);
    void handleParamValue5Changed(const QString &newVal);
    void handleParamValue6Changed(const QString &newVal);
    void handleParamValue7Changed(const QString &newVal);
    void handleFrameTypeChanged(int index);
signals:
    void itemDeleteButtonClicked(int itemNum);
    void itemMoveUpwardsButtonClicked(int itemNum);
    void itemMoveDownwardsButtonClicked(int itemNum);
    void missionItemUpdateVehicleDisplayWidgetMissionPlan();

protected:
    void setParamInfo(int itemType);
    void initButtons();
    void initComboBoxes();
    void initLineEdits();
};

#endif // MISSIONPLANITEM_H
