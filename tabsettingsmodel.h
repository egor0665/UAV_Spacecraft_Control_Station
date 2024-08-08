#ifndef TABSETTINGSMODEL_H
#define TABSETTINGSMODEL_H

#include <custom_widgets/Settings_tab_widgets/settingsmenulistwidget.h>
#include <custom_widgets/Settings_tab_widgets/vehiclegeofencesettingswidget.h>
#include <custom_widgets/Settings_tab_widgets/vehicleothersettingswidget.h>
#include <custom_widgets/Settings_tab_widgets/Vehicle_param_settings_widgets/vehicleparamsettingswidget.h>

#include <custom_models/settingsmenulistmodel.h>

#include <customtab.h>



class TabSettingsModel: public QWidget, public CustomTab
{
    Q_OBJECT
    VehicleParamSettingsWidget vehicleParamSettingsWidget;
    VehicleGeoFenceSettingsWidget vehicleGeoFenceSettingsWidget;
    VehicleOtherSettingsWidget vehicleOtherSettingsWidget;
    SettingsMenuListWidget settingsMenuListWidget;
    QVBoxLayout widgetLayout;

public:
    TabSettingsModel(QWidget *parent = nullptr);
    ~TabSettingsModel();
    void handleAllParamsReceived(QMap<QString,AutoPilotValue> autopilotValues);
    QGridLayout &getMainLayout();

    void setCurrent(bool current);
protected slots:
//    void handleWriteParams(QVector<mavlink_param_value_t> valuesToChange);
//    void handleRefreshParams();
    void handleSettingsMenuIndexChanged(int index);
signals:
    void writeParams(QVector<mavlink_param_value_t> valuesToChange);
    void refreshParams();
protected:
    void initVehicleParamSettingsWidgetConnections();
    void initUI();
    void initSettingsMenuListWidget();
};

#endif // TABSETTINGSMODEL_H
