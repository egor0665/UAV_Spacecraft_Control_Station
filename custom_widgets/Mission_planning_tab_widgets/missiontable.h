#ifndef MISSIONTABLE_H
#define MISSIONTABLE_H

#include "missionplanitem.h"

#include <QTableWidget>
#include <QObject>
#include <QHeaderView>

const int MISSION_TABLE_COLUMN_COUNT = 16;
const QStringList MISSION_TABLE_HORIZONTAL_HEADERS = {
    "Команда",
    "Парам1",
    "Парам2",
    "Парам3",
    "Парам4",
    "Парам5",
    "Парам6",
    "Парам7",
    "Система",
    "Удалить",
    "Вверх",
    "Вниз",
    "Инфо1",
    "Инфо2",
    "Инфо3",
    "Инфо4",
};

class MissionTable: public QTableWidget
{
    Q_OBJECT
    QVector<MissionPlanItemWidget*> missionPlanItemWidgets;
    int missionItemCount;
public:
    MissionTable(QWidget *parent = nullptr);
    void addNewMissionItem();
    void swapRows(int row1, int row2);

    void displayRow(int row, MissionPlanItemWidget *item);;

    void updateVerticalHeader();

    QString formTextMissionPlan();
    void parseTextMissionPlan(QString missionTextPlan);
    QVector<MissionPlanItem> getMissionPlanItems();

    void updatePlan(QVector<MissionPlanItem> newPlan);
protected:
    void resetTable();
    QVector<MissionPlanItem> formMissionPlanItemVector();
protected slots:
    void handleItemDeleteButtonClicked(int itemNum);
    void handleItemMoveUpwardsButtonClicked(int itemNum);
    void handleItemMoveDownwardsButtonClicked(int itemNum);
    void handleUpdateVehicleDisplayWidgetMissionPlan();
    void handleItemClicked(int currentRow, int currentColumn, int previousRow, int previousColumn);
signals:
    void updateVehicleDisplayWidgetMissionPlan(QVector<MissionPlanItem> missionPlanItems);
};

#endif // MISSIONTABLE_H
