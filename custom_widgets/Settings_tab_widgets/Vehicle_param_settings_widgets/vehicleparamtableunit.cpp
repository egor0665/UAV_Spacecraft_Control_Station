#include "vehicleparamtableunit.h"

const QString &VehicleParamTableUnit::getParamId() const
{
    return paramId;
}

VehicleParamTableUnit::VehicleParamTableUnit(QWidget *parent) : QWidget(parent)
{
}

VehicleParamTableUnit::~VehicleParamTableUnit()
{
}


void VehicleParamTableUnit::init(QString paramId, QVariant paramValue, int paramType, int paramIndex, QString paramInfoString)
{
    switch(paramType)
    {
    case (MAV_PARAM_TYPE_UINT8):
    {
        this->paramValue = paramValue.toUInt();
        break;
    }
    case (MAV_PARAM_TYPE_INT8):
    {
        this->paramValue = paramValue.toInt();
        break;
    }
    case (MAV_PARAM_TYPE_UINT16):
    {
        this->paramValue = paramValue.toUInt();
        break;
    }
    case (MAV_PARAM_TYPE_INT16):
    {
        this->paramValue = paramValue.toInt();
        break;
    }
    case (MAV_PARAM_TYPE_UINT32):
    {
        this->paramValue = paramValue.toUInt();
        break;
    }
    case (MAV_PARAM_TYPE_INT32):
    {
        this->paramValue = paramValue.toInt();
        break;
    }
    case (MAV_PARAM_TYPE_UINT64):
    {
        this->paramValue = paramValue.toULongLong();
        break;
    }
    case (MAV_PARAM_TYPE_INT64):
    {
        this->paramValue = paramValue.toLongLong();
        break;
    }
    case (MAV_PARAM_TYPE_REAL32):
    {
        this->paramValue = paramValue.toFloat();
        break;
    }
    case (MAV_PARAM_TYPE_REAL64):
    {
        this->paramValue = paramValue.toDouble();
        break;
    }
    }

    this->paramId = paramId;

    this->paramType = paramType;
    this->paramIndex = paramIndex;

    valueDSB.setDecimals(5);
    valueDSB.setMaximum(1000000);
    valueDSB.setMinimum(-1000000);
    valueDSB.setValue(this->paramValue);

    paramName.setText(paramId);
    if (paramInfoString=="")
        paramInfo.setText("Нет информации о параметре");
    else
        paramInfo.setText(paramInfoString);
    paramInfo.setFont(QFont("MS Shell Dlg 2", 8));
    paramInfo.setStyleSheet("QLabel { color : rgb(100, 100, 100); }");

    mainLayout.addWidget(&paramName,0,0);
    mainLayout.addWidget(&valueDSB,0,2);
    mainLayout.addWidget(&paramInfo,1,0,1,3);

    mainLayout.setMargin(0);
    this->setLayout(&mainLayout);

    connect(&valueDSB, SIGNAL(valueChanged(double)), this, SLOT(valueChangedHandle(double)));
}

void VehicleParamTableUnit::resetValueDSBBackgroundColor()
{
    valueDSB.setStyleSheet("background-color: #1d2228 ; color: #E1E2E2;");
}

void VehicleParamTableUnit::setValueDSBBackgroundColor()
{
    valueDSB.setStyleSheet("background-color: #E1E2E2; color: #1d2228;");
}

void VehicleParamTableUnit::valueChangedHandle(double newValue)
{
    setValueDSBBackgroundColor();
    QVariant value;
    switch(paramType)
    {
    case (MAV_PARAM_TYPE_UINT8):
    {
        value = uint8_t(newValue);
        break;
    }
    case (MAV_PARAM_TYPE_INT8):
    {
        value = int8_t(newValue);
        break;
    }
    case (MAV_PARAM_TYPE_UINT16):
    {
        value = uint16_t(newValue);
        break;
    }
    case (MAV_PARAM_TYPE_INT16):
    {
        value = int16_t(newValue);
        break;
    }
    case (MAV_PARAM_TYPE_UINT32):
    {
        value = uint32_t(newValue);
        break;
    }
    case (MAV_PARAM_TYPE_INT32):
    {
        value = int32_t(newValue);
        break;
    }
    case (MAV_PARAM_TYPE_UINT64):
    {
        value = uint64_t(newValue);
        break;
    }
    case (MAV_PARAM_TYPE_INT64):
    {
        value = int64_t(newValue);
        break;
    }
    case (MAV_PARAM_TYPE_REAL32):
    {
        value = float(newValue);
        break;
    }
    case (MAV_PARAM_TYPE_REAL64):
    {
        value = newValue;
        break;
    }
    }
    emit widgetValueChanged(paramId, value, paramType);
}
