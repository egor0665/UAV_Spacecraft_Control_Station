#ifndef VALUEDISPLAYWIDGETUNIT_H
#define VALUEDISPLAYWIDGETUNIT_H

#include <custom_dialogs/comboboxdialog.h>
#include <QLabel>
#include <QTimer>
#include <QVariant>
#include <QWidget>
#include <structs.h>
#include <QGridLayout>
#include <custom_dialogs/ChooseValueToFollowDialog.h>

class ValueDisplayWidgetUnit: public QWidget
{
    Q_OBJECT

    bool temporary;

    int row, column;
    QGridLayout mainLayout;
    QLabel nameLBL;
    QLabel valueLBL;
    QTimer updateTimer;

    ValueToFollow toFollowValue;

    ChooseValueToFollowDialog *chooseValueToFollowDialog;

public:
    bool isTemporary();
    explicit ValueDisplayWidgetUnit(QWidget *parent = nullptr);
    ~ValueDisplayWidgetUnit();

    ValueDisplayWidgetUnit(ValueToFollow toFollowValue, int row, int column, bool temporary, QWidget *parent = nullptr);

    void changeCurrentVehicleValues(QVector<ValueToFollow> valuesToFollow);
    void updateValue(ValueToFollow value);
    const ValueToFollow &getToFollowValue() const;

protected:
    void updateValueByTimer();
    virtual void resizeEvent(QResizeEvent *resizeEvent);

protected slots:
    void ShowContextMenu(const QPoint &pos);
    void changeValue();
    void changeSize();
    void handleNewValue(ValueToFollow value);
    void handleDialogClosed();
signals:
    void getcurrentVehicleValuesToFollow(int row, int column); //
    void changeTableSize();
};

#endif // VALUEDISPLAYWIDGETUNIT_H
