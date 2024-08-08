#ifndef VALUEDISPLAYWIDGET_H
#define VALUEDISPLAYWIDGET_H

#include "valuedisplaywidgetunit.h"
#include <QGridLayout>
//#include <QObject>
#include <QWidget>
#include <custom_dialogs/settablesizedialog.h>

#include <custom_widgets/tabmodule.h>

int findIndexValueToFollowByName(QVector<ValueToFollow> values, QString name);


class ValueDisplayWidget: public QWidget //, public tabModule
{
    Q_OBJECT
    QGridLayout mainLayout;
    ValueToFollow *tempValue = nullptr;
    uint8_t a = 0;
    QVector<ValueToFollow> valuesToFollow;
    int rows, columns;

    SetTableSizeDialog *dialog;
public:
    explicit ValueDisplayWidget(QWidget *parent = nullptr);
    ~ValueDisplayWidget();
    void setValueWidget(int row, int column, ValueToFollow value, bool temp);
    void setValuesToFollow(QVector<ValueToFollow> valuesToFollow);
    void init(QVector<ValueToFollow> valuesToFollow);
protected:

    void addEmptyWidgets(int rows, int columns);
    void removeExtraWidgets(int rows, int columns);
signals:

protected slots:
    void handleGetCurrentVehicleValuesToFollow(int row, int column);
    void setRowColumnCount(int rows, int columns);
    void handleChangeTableSize();
    void handleDialogClosed();
};

#endif // VALUEDISPLAYWIDGET_H
