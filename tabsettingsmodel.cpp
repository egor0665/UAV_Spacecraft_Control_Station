#include "tabsettingsmodel.h"


TabSettingsModel::TabSettingsModel(QWidget *parent) : QWidget(parent)
{
    initUI();
    initVehicleParamSettingsWidgetConnections();
    initSettingsMenuListWidget();
}

TabSettingsModel::~TabSettingsModel()
{
}

void TabSettingsModel::initUI()
{
    widgetLayout.addWidget(&vehicleParamSettingsWidget);
    widgetLayout.addWidget(&vehicleGeoFenceSettingsWidget);
    widgetLayout.addWidget(&vehicleOtherSettingsWidget);

    mainLayout.addWidget(&settingsMenuListWidget,0,0);
    mainLayout.addLayout(&widgetLayout,0,1,1,2);
    this->setLayout(&mainLayout);
}

void TabSettingsModel::initSettingsMenuListWidget()
{
    connect(&settingsMenuListWidget, &SettingsMenuListWidget::settingsMenuIndexChanged, this, &TabSettingsModel::handleSettingsMenuIndexChanged);
}

void TabSettingsModel::initVehicleParamSettingsWidgetConnections()
{
//    connect(&vehicleParamSettingsWidget, &VehicleParamSettingsWidget::refreshParams, this, &TabSettingsModel::handleRefreshParams);
//        connect(&vehicleParamSettingsWidget, &VehicleParamSettingsWidget::writeParams, this, &TabSettingsModel::handleWriteParams);
    connect(&vehicleParamSettingsWidget, &VehicleParamSettingsWidget::refreshParams, this,
            [this](){
        emit refreshParams();
    });
    connect(&vehicleParamSettingsWidget, &VehicleParamSettingsWidget::writeParams, this,
            [this](QVector<mavlink_param_value_t> valuesToChange){
        emit writeParams(valuesToChange);
    });
}

void TabSettingsModel::setCurrent(bool current)
{
    isCurrentTab = current;
    vehicleParamSettingsWidget.setSleep(!current);
    vehicleGeoFenceSettingsWidget.setSleep(!current);
    vehicleOtherSettingsWidget.setSleep(!current);
    settingsMenuListWidget.setSleep(!current);
}

void TabSettingsModel::handleSettingsMenuIndexChanged(int index)
{
    switch(index)
    {
    case -1:
    {
        widgetLayout.itemAt(1)->widget()->hide();
        widgetLayout.itemAt(2)->widget()->hide();
        widgetLayout.itemAt(0)->widget()->setVisible(true);
        break;
    }
    case 0:
    {
        widgetLayout.itemAt(1)->widget()->hide();
        widgetLayout.itemAt(2)->widget()->hide();
        widgetLayout.itemAt(0)->widget()->setVisible(true);
        break;
    }
    case 1:
    {
        widgetLayout.itemAt(0)->widget()->hide();
        widgetLayout.itemAt(2)->widget()->hide();
        widgetLayout.itemAt(1)->widget()->setVisible(true);
        break;
    }
    case 2:
    {
        widgetLayout.itemAt(1)->widget()->hide();
        widgetLayout.itemAt(0)->widget()->hide();
        widgetLayout.itemAt(2)->widget()->setVisible(true);
        break;
    }
    }
}

void TabSettingsModel::handleAllParamsReceived(QMap<QString,AutoPilotValue> autopilotValues)
{
//    tabSettingsModel->handleAllParamsReceived(autopilotValues);
    vehicleParamSettingsWidget.init(autopilotValues);
}

QGridLayout &TabSettingsModel::getMainLayout()
{
    return mainLayout;
}

//void TabSettingsModel::handleRefreshParams()
//{
//    // TODO CHECK ON TAB LEVEL IF POSSIBLE
//    emit refreshParams();
//}

//void TabSettingsModel::handleWriteParams(QVector<mavlink_param_value_t> valuesToChange)
//{
//    // TODO CHECK ON TAB LEVEL IF POSSIBLE
//    emit writeParams(valuesToChange);
//}

//void MainModel::handleWriteParams(QVector<mavlink_param_value_t> paramsToChange)
//{
//    connectedVehicles[currentVehicleId]->writeParams(paramsToChange);
//}
