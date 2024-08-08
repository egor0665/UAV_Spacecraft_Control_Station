#include "valuedisplaywidgetunit.h"
#include <QFont>
#include <QMenu>
#include <QResizeEvent>
#include <QWidget>
#include <QStyle>

ValueDisplayWidgetUnit::ValueDisplayWidgetUnit(QWidget *parent): QWidget(parent)
{
}

ValueDisplayWidgetUnit::~ValueDisplayWidgetUnit()
{

}

ValueDisplayWidgetUnit::ValueDisplayWidgetUnit(ValueToFollow value, int row, int column, bool temporary, QWidget *parent) : QWidget(parent)
{
    this->temporary = temporary;
    this->row = row;
    this->column = column;
    this->nameLBL.setText(value.name);
    this->valueLBL.setText("0");
    this->toFollowValue = value;

    nameLBL.setAlignment(Qt::AlignCenter);
    nameLBL.setFont(QFont("MS Shell Dlg 2", 10));

    valueLBL.setAlignment(Qt::AlignCenter);
    valueLBL.setFont(QFont("MS Shell Dlg 2", 20));
    int rColor = (row * 100 + 150) % 256, gColor = (column * 100 + 150) % 256, bColor = (row * column + 150) * 100 %256;
    QString color = "rgb( " + QString::number(rColor) + "," + QString::number(gColor) + "," + QString::number(bColor) + " )";
    valueLBL.setStyleSheet("QLabel { color : " + color + "; }");

    mainLayout.addWidget(&nameLBL,0,0);
    mainLayout.addWidget(&valueLBL,1,0);
    this->setLayout(&mainLayout);

    connect(&updateTimer,&QTimer::timeout,this,&ValueDisplayWidgetUnit::updateValueByTimer);
    updateTimer.start(1000);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &ValueDisplayWidgetUnit::customContextMenuRequested, this, &ValueDisplayWidgetUnit::ShowContextMenu);
}

void ValueDisplayWidgetUnit::changeCurrentVehicleValues(QVector<ValueToFollow> valuesToFollow)
{
    chooseValueToFollowDialog = new ChooseValueToFollowDialog(valuesToFollow, this);
    connect(chooseValueToFollowDialog, &ChooseValueToFollowDialog::gotDialogResult, this, &ValueDisplayWidgetUnit::handleNewValue);
    connect(chooseValueToFollowDialog, &ChooseValueToFollowDialog::dialogClosed, this, &ValueDisplayWidgetUnit::handleDialogClosed);//gotDialogResult(selectedValue);
    chooseValueToFollowDialog->show();
}

void ValueDisplayWidgetUnit::updateValue(ValueToFollow value)
{
    this->temporary = false;
    this->nameLBL.setText(value.name);
    this->valueLBL.setText("0");
    this->toFollowValue = value;
}

void ValueDisplayWidgetUnit::handleNewValue(ValueToFollow value)
{
    chooseValueToFollowDialog->hide();
    delete(chooseValueToFollowDialog);

    this->temporary = false;
    this->nameLBL.setText(value.name);
    this->valueLBL.setText("0");
    this->toFollowValue = value;
}

void ValueDisplayWidgetUnit::handleDialogClosed()
{
    chooseValueToFollowDialog->hide();
    delete(chooseValueToFollowDialog);
}
void ValueDisplayWidgetUnit::ShowContextMenu(const QPoint &pos)
{
   QMenu contextMenu(tr("Контекстное меню"), this);

   QAction action1("Выбрать показатель", this);
   connect(&action1, SIGNAL(triggered()), this, SLOT(changeValue()));
   contextMenu.addAction(&action1);

   QAction action2("Изменить размер", this);
   connect(&action2, SIGNAL(triggered()), this, SLOT(changeSize()));
   contextMenu.addAction(&action2);

   contextMenu.exec(mapToGlobal(pos));
}
void ValueDisplayWidgetUnit::changeValue()
{
    emit getcurrentVehicleValuesToFollow(row, column); //
}

void ValueDisplayWidgetUnit::changeSize()
{
    emit changeTableSize();
}

Q_DECLARE_METATYPE(float*)
Q_DECLARE_METATYPE(uint8_t*)
Q_DECLARE_METATYPE(int8_t*)
Q_DECLARE_METATYPE(uint16_t*)
Q_DECLARE_METATYPE(int16_t*)
Q_DECLARE_METATYPE(uint32_t*)
Q_DECLARE_METATYPE(int32_t*)
Q_DECLARE_METATYPE(uint64_t*)

void ValueDisplayWidgetUnit::updateValueByTimer()
{

    switch (toFollowValue.valueType)
    {
    case(FLOAT_TYPE):
    {
        valueLBL.setText(QString::number(*toFollowValue.valuePointer.value<float*>(),'f',2));
        break;
    }
    case(UINT8_T_TYPE):
    {
        valueLBL.setText(QString::number(*toFollowValue.valuePointer.value<uint8_t*>(),'f',2));
        break;
    }
    case(INT8_T_TYPE):
    {
        valueLBL.setText(QString::number(*toFollowValue.valuePointer.value<int8_t*>(),'f',2));
        break;
    }
    case(UINT16_T_TYPE):
    {
        valueLBL.setText(QString::number(*toFollowValue.valuePointer.value<uint16_t*>(),'f',2));
        break;
    }
    case(INT16_T_TYPE):
    {
        valueLBL.setText(QString::number(*toFollowValue.valuePointer.value<int16_t*>(),'f',2));
        break;
    }
    case(UINT32_T_TYPE):
    {
        valueLBL.setText(QString::number(*toFollowValue.valuePointer.value<uint32_t*>(),'f',2));
        break;
    }
    case(INT32_T_TYPE):
    {
        valueLBL.setText(QString::number(*toFollowValue.valuePointer.value<int32_t*>(),'f',2));
        break;
    }
    case(UINT64_T_TYPE):
    {
        valueLBL.setText(QString::number(*toFollowValue.valuePointer.value<uint64_t*>(),'f',2));
        break;
    }
    }
}

void ValueDisplayWidgetUnit::resizeEvent(QResizeEvent *resizeEvent)
{
    int button_margin = style()->pixelMetric(QStyle::PM_ButtonMargin);
    int mainSize = resizeEvent->size().height();
    int newSize = mainSize / button_margin;
    valueLBL.setFont(QFont("MS Shell Dlg 2", newSize * 1.5));
    nameLBL.setFont(QFont("MS Shell Dlg 2", newSize));
}

const ValueToFollow &ValueDisplayWidgetUnit::getToFollowValue() const
{
    return toFollowValue;
}

bool ValueDisplayWidgetUnit::isTemporary()
{
    return temporary;
}

