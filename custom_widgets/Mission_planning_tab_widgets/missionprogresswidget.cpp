#include "missionprogresswidget.h"
#include <QHeaderView>

MissionProgressWidget::MissionProgressWidget(QWidget *parent) : QWidget(parent)
{
    //totalTimeNameLBL, totalTimeLBL, executeStateNameLBL, executeStateLBL
    executeStateNameLBL.setText("Статус выполнения:");
    mainLayout.addWidget(&executeStateNameLBL,0,0);
    executeStateLBL.setText("Пауза");
    mainLayout.addWidget(&executeStateLBL,0,1);
    totalTimeNameLBL.setText("Время выполнения:");
    mainLayout.addWidget(&totalTimeNameLBL,1,0);

    missionTime.setHMS(0,0,0);
    totalTimeLBL.setText(missionTime.toString("hh:mm:ss"));

    mainLayout.addWidget(&totalTimeLBL,1,1);
    mainLayout.addWidget(&missionTable,2,0,1,2);

    missionTable.setModel(&missionProgressTableModel);
    missionTable.horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    missionTable.horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    missionTable.horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);

    timeCounter.setInterval(1000);
    connect(&timeCounter,&QTimer::timeout,this,&MissionProgressWidget::handleTimeCounter);

    this->setLayout(&mainLayout);

}

void MissionProgressWidget::setPlan(QVector<MissionPlanItem> planItems)
{
    missionProgressTableModel.setNewPlan(planItems);
}

void MissionProgressWidget::startMissionTimeCount()
{
    timeCounter.start();
    missionProgressTableModel.startTimeCount();
    executeStateLBL.setText("В процессе");
}
void MissionProgressWidget::stopMissionTimeCount()
{
    timeCounter.stop();
    missionProgressTableModel.stopTimeCount();
    executeStateLBL.setText("Пауза");
}

void MissionProgressWidget::updateMissionProgress(mavlink_mission_item_reached_t missionItemReached)
{
    if (missionItemReached.seq-1 <= missionProgressTableModel.getMissionPlan().length()-1)
    {
        if (!timeCounter.isActive())
        {
            startMissionTimeCount();
        }
        missionProgressTableModel.updateMissionProgress(missionItemReached);
        if (missionItemReached.seq-1 >= missionProgressTableModel.getMissionPlan().length()-1)
            stopMissionTimeCount();
    }
}

void MissionProgressWidget::handleTimeCounter()
{
    missionTime = missionTime.addSecs(1);
    totalTimeLBL.setText(missionTime.toString("hh:mm:ss"));
}
