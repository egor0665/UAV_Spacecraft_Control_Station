#ifndef MISSIONPROGRESSWIDGET_H
#define MISSIONPROGRESSWIDGET_H

#include <QGridLayout>
#include <QLabel>
#include <QTableView>
#include <QWidget>

#include <custom_widgets/tabmodule.h>

#include <custom_models/missionprogresstablemodel.h>

class MissionProgressWidget : public QWidget, public tabModule
{
    Q_OBJECT
    QTableView missionTable;
    QTime missionTime;
    QLabel totalTimeNameLBL, totalTimeLBL, executeStateNameLBL, executeStateLBL;
    QGridLayout mainLayout;
    MissionProgressTableModel missionProgressTableModel;
    QTimer timeCounter;
public:
    explicit MissionProgressWidget(QWidget *parent = nullptr);
    void setPlan(QVector<MissionPlanItem> planItems);

    void startMissionTimeCount();

    void updateMissionProgress(mavlink_mission_item_reached_t missionItemReached);
    void stopMissionTimeCount();
signals:

protected slots:
    void handleTimeCounter();
};

#endif // MISSIONPROGRESSWIDGET_H
