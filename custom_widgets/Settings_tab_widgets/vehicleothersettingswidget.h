#ifndef VEHICLEOTHERSETTINGSWIDGET_H
#define VEHICLEOTHERSETTINGSWIDGET_H

#include "custom_widgets/tabmodule.h"
#include <QWidget>



class VehicleOtherSettingsWidget: public QWidget, public tabModule
{
public:
    VehicleOtherSettingsWidget(QWidget *parent = nullptr);
};

#endif // VEHICLEOTHERSETTINGSWIDGET_H
