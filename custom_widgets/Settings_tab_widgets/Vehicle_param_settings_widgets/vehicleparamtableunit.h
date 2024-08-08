#ifndef VEHICLEPARAMTABLEUNIT_H
#define VEHICLEPARAMTABLEUNIT_H


#include "custom_widgets/tabmodule.h"

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QWidget>
#include <mavlink/ardupilotmega/mavlink.h>

enum ParamType{
    ParamInt = 1,
    ParamFloat = 2
};

class VehicleParamTableUnit: public QWidget
{
    Q_OBJECT
    QGridLayout mainLayout;
    QString paramId;
    double paramValue;
    int paramType;
    int paramIndex;
    QLabel paramName;
    QLabel paramInfo;

    QDoubleSpinBox valueDSB;
public:
    VehicleParamTableUnit(QWidget *parent = nullptr);
    ~VehicleParamTableUnit();
    void init(QString paramId, QVariant paramValue, int paramType, int paramIndex, QString paramInfo);
    const QString &getParamId() const;

    void resetValueDSBBackgroundColor();
protected slots:
    void valueChangedHandle(double newValue);
signals:
    void widgetValueChanged(QString paramId, QVariant paramValue, int paramType);
protected:
    void setValueDSBBackgroundColor();
};

#endif // VEHICLEPARAMTABLEUNIT_H
