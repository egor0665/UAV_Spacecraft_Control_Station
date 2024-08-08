#include <QAbstractTableModel>
#include <QString>
#include <QTime>
#include <QTimer>

#include <custom_widgets/Mission_planning_tab_widgets/missionplanitem.h>

#ifndef MISSIONPROGRESSTABLEMODEL_H
#define MISSIONPROGRESSTABLEMODEL_H

typedef enum MISSION_TABLE_ITEM_RESULT
{
    RESULT_SUCCESS,
    RESULT_FAILURE,
    RESULT_ERROR,
    RESULT_IN_PROGRESS
} MISSION_TABLE_ITEM_RESULT;

const QMap<int,QString> missionTableItemResults
{
    {RESULT_SUCCESS,"Успешно"},
    {RESULT_FAILURE,"Не выполнено"},
    {RESULT_ERROR,"Ошибка"},
    {RESULT_IN_PROGRESS,"В процессе"},
};

struct PlanItem
{
    int command;
    QTime executeTime;
    int result;
    PlanItem(){};
    PlanItem(int command)
    {
        this->command = command;
        QTime time;
        time.setHMS(0,0,0);
        this->executeTime = time;
        this->result = RESULT_IN_PROGRESS;
    };
};
Q_DECLARE_METATYPE(PlanItem);

class MissionProgressTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QTimer missionItemTimer;
    QVector<PlanItem> missionPlan;
    int currentMissionItemIndex = 0;

public:
    MissionProgressTableModel();
    int rowCount (const QModelIndex & parent = QModelIndex()) const;
    int columnCount (const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index,const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setNewPlan(QVector<MissionPlanItem>);
    void updateCurrentMissionItemTime();
    void updateCurrentMissionItemResult();
    void updateMissionProgress(mavlink_mission_item_reached_t missionItemReached);
    void startTimeCount();
    void stopTimeCount();
    const QVector<PlanItem> &getMissionPlan() const;

protected:
    void setNewActivePlanItem(int newItemIndex);
protected slots:
    void updateMissionItemTime();
};

#endif // MISSIONPROGRESSTABLEMODEL_H
