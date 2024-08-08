#include "missionplansetupwidget.h"

#include <CustomFileManager.h>
#include <QFileDialog>
#include <QGridLayout>

#include <exceptions/cantreadwritefileexception.h>

MissionPlanSetupWidget::MissionPlanSetupWidget(QWidget *parent) : QWidget(parent)
{
//    missionTable = MissionTable(this);// = new MissionTable(this);

    connect(&missionTable, &MissionTable::updateVehicleDisplayWidgetMissionPlan, this, &MissionPlanSetupWidget::handleUpdateVehicleDisplayWidgetMissionPlan);

//    addMissionItemButton = new QPushButton(this);
    addMissionItemButton.setText("Добавить пункт");
    connect(&addMissionItemButton, &QPushButton::clicked, this, &MissionPlanSetupWidget::handleAddMissionItemButtonClicked);

//    saveToFileButton = new QPushButton(this);
    saveToFileButton.setText("Сохранить как...");
    connect(&saveToFileButton, &QPushButton::clicked, this, &MissionPlanSetupWidget::handleSaveToFileButtonClicked);

//    loadFromFileButton = new QPushButton(this);
    loadFromFileButton.setText("Открыть из файла");
    connect(&loadFromFileButton, &QPushButton::clicked, this, &MissionPlanSetupWidget::handleLoadFromFileButtonClicked);

//    writeToVehicleButton = new QPushButton(this);
    writeToVehicleButton.setText("Записать");
    connect(&writeToVehicleButton, &QPushButton::clicked, this, &MissionPlanSetupWidget::handleWritePlanToVehicleButtonClicked);

//    readFromVehicleButton = new QPushButton(this);
    readFromVehicleButton.setText("Считать");
    connect(&readFromVehicleButton, &QPushButton::clicked, this, &MissionPlanSetupWidget::handleReadPlanFromVehicleButtonClicked);

//    routeStartMarkerId = new QSpinBox();
//    routeStartMarkerId->setRange(0,0);
//    QLabel *formMarkerRouteLabel = new QLabel("Сформ. марш. до марк.", this);
    formMarkerRouteLabel.setText("Сформ. марш. до марк.");

//    routeEndMarkerIdSB = new QSpinBox(this);
    routeEndMarkerIdSB.setRange(0,0);

//    QLabel *distanceToRouteLabel = new QLabel("Дист. до марк.", this);
    distanceToRouteLabel.setText("Дист. до марк.");

//    routeToMarkerDistanceSB = new QDoubleSpinBox(this);
    routeToMarkerDistanceSB.setRange(0,10000);

//    formMarkerRouteButton = new QPushButton(this);
    formMarkerRouteButton.setText("Сформировать");
    connect(&formMarkerRouteButton, &QPushButton::clicked,this,&MissionPlanSetupWidget::handleFormMarkerRouteButtonClicked);

//    QGridLayout *mainLayout = new QGridLayout(this);

    mainLayout.addWidget(&addMissionItemButton,0,0);
    mainLayout.addWidget(&saveToFileButton,0,2);
    mainLayout.addWidget(&loadFromFileButton,0,3);
    mainLayout.addWidget(&writeToVehicleButton,0,5);
    mainLayout.addWidget(&readFromVehicleButton,0,6);


    mainLayout.addWidget(&missionTable,1,0,1,7);

    mainLayout.addWidget(&formMarkerRouteLabel, 2,0);
    mainLayout.addWidget(&routeEndMarkerIdSB, 2,2);
    mainLayout.addWidget(&distanceToRouteLabel, 2,3);
    mainLayout.addWidget(&routeToMarkerDistanceSB, 2,4);
    mainLayout.addWidget(&formMarkerRouteButton, 2,5);


    this->setLayout(&mainLayout);
}

void MissionPlanSetupWidget::updatePlan(QVector<MissionPlanItem> newPlan)
{
    missionTable.updatePlan(newPlan);
}

void MissionPlanSetupWidget::updateMarkerIdSpinBox(int markerNum)
{
    routeEndMarkerIdSB.setRange(0,markerNum-1);
}

void MissionPlanSetupWidget::handleFormMarkerRouteButtonClicked()
{
    emit missionPlanSetupWidgetFormMarkerRoute(routeEndMarkerIdSB.value(), routeToMarkerDistanceSB.value());
}

void MissionPlanSetupWidget::handleUpdateVehicleDisplayWidgetMissionPlan(QVector<MissionPlanItem> planItems)
{
    emit missionPlanSetupWidgetUpdateVehicleDisplayMissionPlan(planItems);
}

void MissionPlanSetupWidget::handleAddMissionItemButtonClicked()
{
    missionTable.addNewMissionItem();
}

const QString DEFAULT_FILE_DIRECTORY = "C:/Qt/5.15.2/mingw81_32/GroundControlStation";
void MissionPlanSetupWidget::handleSaveToFileButtonClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Выберите файл миссии"), DEFAULT_FILE_DIRECTORY, tr("Файлы планов миссий (*.mpf)"));

    QString missionTextPlan = missionTable.formTextMissionPlan();
    CustomFileManager cfm;
    try {
        cfm.saveToFile(missionTextPlan, fileName);
    }  catch (CantReadWriteFileException &e) {
        emit logError(e);
    }
}

void MissionPlanSetupWidget::handleLoadFromFileButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Выберите файл миссии"), DEFAULT_FILE_DIRECTORY, tr("Файлы планов миссий (*.mpf)"));

    try {
        CustomFileManager cfm;
        QString missionTextPlan = cfm.readFromFile(fileName);
        missionTable.parseTextMissionPlan(missionTextPlan);

    }  catch (CantReadWriteFileException &e) {
        emit logError(e);
    }
}
void MissionPlanSetupWidget::handleWritePlanToVehicleButtonClicked()
{
    emit missionPlanSetupWidgetWritePlanToVehicle(missionTable.getMissionPlanItems());
}
void MissionPlanSetupWidget::handleReadPlanFromVehicleButtonClicked()
{

}

