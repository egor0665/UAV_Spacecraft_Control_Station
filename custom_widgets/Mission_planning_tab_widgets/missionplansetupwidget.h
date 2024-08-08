#ifndef MISSIONPLANSETUPWIDGET_H
#define MISSIONPLANSETUPWIDGET_H

#include "custom_widgets/tabmodule.h"

#include "missionplanitem.h"
#include "missiontable.h"

#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <mavlink/ardupilotmega/mavlink.h>
#include <QLineEdit>
#include <QTableWidget>
#include <structs.h>
#include <QHeaderView>
#include <QDebug>
#include <QSpinBox>
#include <QGridLayout>
#include <exceptions/cantreadwritefileexception.h>

class MissionPlanSetupWidget: public QWidget, public tabModule
{
    Q_OBJECT
    QGridLayout mainLayout;
    QLabel formMarkerRouteLabel, distanceToRouteLabel;
    MissionTable missionTable;
    QPushButton addMissionItemButton, saveToFileButton, loadFromFileButton, writeToVehicleButton, readFromVehicleButton;

    QSpinBox routeEndMarkerIdSB;
    QDoubleSpinBox routeToMarkerDistanceSB;
    QPushButton formMarkerRouteButton;
//    QComboBox *missionType
public:
    MissionPlanSetupWidget(QWidget *parent = nullptr);
    void updatePlan(QVector<MissionPlanItem> newPlan);
    void updateMarkerIdSpinBox(int markerNum);
    //    ~MissionPlanSetupWidget();

protected slots:
    void handleUpdateVehicleDisplayWidgetMissionPlan(QVector<MissionPlanItem> planItems);
    void handleAddMissionItemButtonClicked();
    void handleSaveToFileButtonClicked();
    void handleLoadFromFileButtonClicked();
    void handleWritePlanToVehicleButtonClicked();
    void handleReadPlanFromVehicleButtonClicked();
    void handleFormMarkerRouteButtonClicked();
signals:
    void logError(CantReadWriteFileException e);
    void missionPlanSetupWidgetUpdateVehicleDisplayMissionPlan(QVector<MissionPlanItem> planItems);
    void missionPlanSetupWidgetWritePlanToVehicle(QVector<MissionPlanItem> planItems);
    void missionPlanSetupWidgetFormMarkerRoute(int endMarkerId, float distanceToMarker);
};

#endif // MISSIONPLANSETUPWIDGET_H
