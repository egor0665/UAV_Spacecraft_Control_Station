#include "vehicleparamsettingswidget.h"

VehicleParamSettingsWidget::VehicleParamSettingsWidget(QWidget *parent) : QWidget(parent)
{
    values = {};

    paramList.setStyleSheet("QListWidget::item { border: 1px solid grey }");
    refreshButton.setText("Обновить");
    refreshButton.setMaximumWidth(200);
    connect(&refreshButton, &QPushButton::clicked,this,&VehicleParamSettingsWidget::handleRefreshButtonClicked);
    writeParamsButton.setText("Записать");
    writeParamsButton.setMaximumWidth(200);
    connect(&writeParamsButton, &QPushButton::clicked,this,&VehicleParamSettingsWidget::handleWriteParamsButtonClicked);

    searchButton.setText("Найти");
    connect(&searchButton, &QPushButton::clicked,this,&VehicleParamSettingsWidget::handleSearchButtonClicked);

    mainLayout.addWidget(&writeParamsButton,0,0);
    mainLayout.addWidget(&refreshButton,0,1);
    mainLayout.addWidget(&searchLE,0,2);
    mainLayout.addWidget(&searchButton,0,3);
    mainLayout.addWidget(&paramList,1,0,1,4);

    mainLayout.setMargin(0);
    this->setLayout(&mainLayout);
    valuesToChange.clear();
}

VehicleParamSettingsWidget::~VehicleParamSettingsWidget()
{
}

void VehicleParamSettingsWidget::handleSearchButtonClicked()
{
    QString searchString = searchLE.text();
    displayDataBySearch(searchString);
}

void VehicleParamSettingsWidget::setSleep(bool sleep)
{
    this->sleep = sleep;
    if (!sleep)
        displayData();
    else
    {
        paramList.clear();
        valuesToChange.clear();
    }
}

void VehicleParamSettingsWidget::handleRefreshButtonClicked()
{
    emit refreshParams();
    valuesToChange.clear();
    paramList.clear();
}

void VehicleParamSettingsWidget::handleWriteParamsButtonClicked()
{
    emit writeParams(valuesToChange);
    valuesToChange.clear();
    clearItemsBackgrounds();
}
void VehicleParamSettingsWidget::clearItemsBackgrounds()
{
    for (int i=0;i<paramList.count() ;i++)
        qobject_cast<VehicleParamTableUnit*> (paramList.itemWidget(paramList.item(i)))->resetValueDSBBackgroundColor();
}


void VehicleParamSettingsWidget::init(QMap<QString, AutoPilotValue> values)
{
    this->values = values;
    if (!sleep)
        displayData();
}

void VehicleParamSettingsWidget::displayDataBySearch(QString searchText)
{
    for (int i=0;i<paramList.count();i++)
    {
        if (qobject_cast<VehicleParamTableUnit*> (paramList.itemWidget(paramList.item(i)))->getParamId().contains(searchText))
            paramList.item(i)->setHidden(false);
        else
            paramList.item(i)->setHidden(true);
    }
}

void VehicleParamSettingsWidget::displayData()
{
    QMap<QString, AutoPilotValue>::iterator it;
    for (it = values.begin(); it != values.end(); ++it) {
        VehicleParamTableUnit *newWidget = new VehicleParamTableUnit(this);
        newWidget->init(it.value().id, it.value().value.toFloat(), it.value().type, it.value().index, "");
        connect(newWidget, &VehicleParamTableUnit::widgetValueChanged, this ,&VehicleParamSettingsWidget::handleWidgetValueChanged);

        QListWidgetItem *tmpListItem = new QListWidgetItem();
        tmpListItem->setSizeHint(newWidget->sizeHint());

        paramList.addItem(tmpListItem);
        paramList.setItemWidget(tmpListItem, newWidget);

    }
}

void VehicleParamSettingsWidget::handleWidgetValueChanged(QString paramId, QVariant value, int paramType)
{
    for (int i=0;i<valuesToChange.length();i++)
        if (valuesToChange[i].param_id==paramId)
        {
            valuesToChange[i].param_value = value.toFloat();
            return;
        }
    mavlink_param_value_t newVal;

    QByteArray ba = paramId.toLocal8Bit();
    for (int i= 0;i<ba.length();i++)
         newVal.param_id[i]=ba[i];
    newVal.param_value = value.toFloat();
    newVal.param_type = paramType;
    valuesToChange.append(newVal);
}
