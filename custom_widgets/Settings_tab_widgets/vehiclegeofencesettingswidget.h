#ifndef VEHICLEGEOFENCESETTINGSWIDGET_H
#define VEHICLEGEOFENCESETTINGSWIDGET_H

#include "custom_widgets/tabmodule.h"
#include <QWidget>



class VehicleGeoFenceSettingsWidget: public QWidget, public tabModule
{
public:
    VehicleGeoFenceSettingsWidget(QWidget *parent = nullptr);
};

#endif // VEHICLEGEOFENCESETTINGSWIDGET_H
