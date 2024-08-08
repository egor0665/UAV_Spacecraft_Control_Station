#include "valuedialog.h"
#include "ui_valuedialog.h"

#include <QCloseEvent>
#include <QRegExpValidator>
#include <structs.h>

ValueDialog::ValueDialog(QString text, int valueType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ValueDialog)
{
    ui->setupUi(this);
    ui->label->setText(text);
    this->valueType = valueType;


    switch(valueType)
    {
    case(VALUE_TYPE_INT):
    {
        ui->lineEdit->setValidator( new QIntValidator(0, 100, this) );
        break;
    }
    case (VALUE_TYPE_FLOAT):
    {
        ui->lineEdit->setValidator( new QDoubleValidator(0, 100, 2, this) );
        break;
    }
    default:
    {break;}
    }

}

ValueDialog::~ValueDialog()
{
    delete ui;
}

void ValueDialog::on_pushButton_clicked()
{
    this->hide();
    switch(valueType)
    {
    case(VALUE_TYPE_INT):
    {
        emit gotDialogResult(VALUE_DIALOG_GOT_RESULT, ui->lineEdit->text().toInt());
        break;
    }
    case (VALUE_TYPE_FLOAT):
    {
        emit gotDialogResult(VALUE_DIALOG_GOT_RESULT, ui->lineEdit->text().toFloat());
        break;
    }
    case (VALUE_TYPE_STRING):
    {
        emit gotDialogResult(VALUE_DIALOG_GOT_RESULT, ui->lineEdit->text());
        break;
    }
    default:
    {break;}
    }

}

void ValueDialog::on_pushButton_2_clicked()
{
    this->hide();
    emit gotDialogResult(VALUE_DIALOG_CLOSED, -1);

}

void ValueDialog::closeEvent(QCloseEvent *event)
{
    this->hide();
    event->ignore();
    emit gotDialogResult(VALUE_DIALOG_CLOSED, -1);
}

