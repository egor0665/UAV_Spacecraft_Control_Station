#include "valuedisplaywidget.h"

Q_DECLARE_METATYPE(uint8_t*)

ValueDisplayWidget::ValueDisplayWidget(QWidget *parent): QWidget(parent)
{
    QVariant temp;
    temp.setValue(&a);
    tempValue = new ValueToFollow(temp,UINT8_T_TYPE,"");
}

ValueDisplayWidget::~ValueDisplayWidget()
{
    delete(tempValue);
}

void ValueDisplayWidget::setValueWidget(int row, int column, ValueToFollow value, bool temp)
{
    ValueDisplayWidgetUnit *newUnit = new ValueDisplayWidgetUnit(value, row, column, temp, this);

    connect(newUnit,&ValueDisplayWidgetUnit::getcurrentVehicleValuesToFollow,
            this,&ValueDisplayWidget::handleGetCurrentVehicleValuesToFollow);
    connect(newUnit, &ValueDisplayWidgetUnit::changeTableSize,
            this, &ValueDisplayWidget::handleChangeTableSize);

    mainLayout.addWidget(newUnit, row, column);
    this->setLayout(&mainLayout);
}

void ValueDisplayWidget::setValuesToFollow(QVector<ValueToFollow> valuesToFollow)
{
    this->valuesToFollow = valuesToFollow;
    for (int i=0;i<rows;i++)
    {
        for (int j=0;j<columns;j++)
        {
            ValueDisplayWidgetUnit* currentWidget = qobject_cast<ValueDisplayWidgetUnit*>(mainLayout.itemAtPosition(i, j)->widget());
            if (!currentWidget->isTemporary())
            {
                ValueToFollow currentToFollowValue = currentWidget->getToFollowValue();
                int valuesToFollowIndex = findIndexValueToFollowByName(valuesToFollow, currentToFollowValue.name);;
                currentWidget->updateValue(valuesToFollow[valuesToFollowIndex]);
            }
        }
    }
}



void ValueDisplayWidget::handleGetCurrentVehicleValuesToFollow(int row, int column)
{
    ValueDisplayWidgetUnit* currentWidget = qobject_cast<ValueDisplayWidgetUnit*>(mainLayout.itemAtPosition(row, column)->widget());
    currentWidget->changeCurrentVehicleValues(valuesToFollow);
}

void ValueDisplayWidget::init(QVector<ValueToFollow> valuesToFollow)
{
    this->valuesToFollow = valuesToFollow;
    this->rows = 2;
    this->columns = 3;

    setValueWidget(0,0,valuesToFollow[15],false);
    setValueWidget(0,1,valuesToFollow[17],false);
    setValueWidget(0,2,valuesToFollow[19],false);
    setValueWidget(1,0,valuesToFollow[16],false);
    setValueWidget(1,1,valuesToFollow[18],false);
    setValueWidget(1,2,valuesToFollow[20],false);
}

void ValueDisplayWidget::handleChangeTableSize()
{
    dialog = new SetTableSizeDialog(this);

    connect(dialog,&SetTableSizeDialog::gotDialogResult, this, &ValueDisplayWidget::setRowColumnCount);
    connect(dialog,&SetTableSizeDialog::dialogClosed, this, &ValueDisplayWidget::handleDialogClosed);
    dialog->show();
}

void ValueDisplayWidget::handleDialogClosed()
{
    delete(dialog);
}

void ValueDisplayWidget::setRowColumnCount(int rows, int columns)
{
    delete(dialog);
    removeExtraWidgets(rows, columns);
    addEmptyWidgets(rows, columns);
    this->rows = rows;
    this->columns = columns;
}

void ValueDisplayWidget::removeExtraWidgets(int rows, int columns)
{
    int layoutRowCount = this->rows;
    int layoutColumnCount = this->columns;
    for (int i=0;i<layoutRowCount;i++)
    {
        for (int j=0;j<layoutColumnCount;j++)
        {
            ValueDisplayWidgetUnit* currentWidget = qobject_cast<ValueDisplayWidgetUnit*>(mainLayout.itemAtPosition(i, j)->widget());
            if (i>=rows || j>=columns)
            {
                mainLayout.removeWidget(currentWidget);
                delete(currentWidget);
            }
        }
    }
}

void ValueDisplayWidget::addEmptyWidgets(int rows, int columns)
{
    int layoutRowCount = this->rows;
    int layoutColumnCount = this->columns;
    for (int i=0;i<rows;i++)
    {
        for (int j=0;j<columns;j++)
        {
            if (i>=layoutRowCount || j>=layoutColumnCount)
                setValueWidget(i,j,*tempValue,true);
        }
    }
}

int findIndexValueToFollowByName(QVector<ValueToFollow> values, QString name)
{
    int valueToFollowIndex = 0;
    for (int k=0;k<values.length();k++)
    {
        if (values[k].name == name)
            valueToFollowIndex = k;
    }
    return valueToFollowIndex;
}
