#ifndef VEHICLEPARAMSETTINGSWIDGET_H
#define VEHICLEPARAMSETTINGSWIDGET_H

#include "vehicleparamtableunit.h"
#include "custom_widgets/tabmodule.h"
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QSpacerItem>
#include <QWidget>
#include <connectedvehicle.h>

class VehicleParamSettingsWidget: public QWidget, public tabModule
{
    Q_OBJECT
    QGridLayout mainLayout;
    QVector<mavlink_param_value_t> valuesToChange;
    QMap<QString, AutoPilotValue> values;
    QListWidget paramList;
    QPushButton refreshButton, writeParamsButton, searchButton;

    QLineEdit searchLE;
public:
    VehicleParamSettingsWidget(QWidget *parent = nullptr);
    ~VehicleParamSettingsWidget();
    void init(QMap<QString,AutoPilotValue> values);
    void setSleep(bool sleep);
protected slots:
    void handleWidgetValueChanged(QString paramId, QVariant value, int paramType);
    void handleRefreshButtonClicked();
    void handleWriteParamsButtonClicked();
    void handleSearchButtonClicked();
signals:
    void refreshParams();
    void writeParams(QVector<mavlink_param_value_t> paramsToChange);
protected:
    void displayData();
    void displayDataBySearch(QString searchText);
    void clearItemsBackgrounds();
};

#endif // VEHICLEPARAMSETTINGSWIDGET_H
