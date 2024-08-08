#include "comboboxdialog.h"
#include "ui_comboboxdialog.h"

#include <QCloseEvent>

ComboBoxDialog::ComboBoxDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComboBoxDialog)
{
    ui->setupUi(this);
}

ComboBoxDialog::ComboBoxDialog(QString text, QMap<QString,int> values, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComboBoxDialog)
{
    ui->setupUi(this);
}

ComboBoxDialog::~ComboBoxDialog()
{
    delete ui;
}

void ComboBoxDialog::on_pushButton_clicked()
{
//    gotDialogResult(VALUE_DIALOG_GOT_RESULT, ui->comboBox->itemData(ui->comboBox->currentIndex()));
}

void ComboBoxDialog::on_pushButton_2_clicked()
{
    this->hide();
//    emit gotDialogResult(VALUE_DIALOG_CLOSED, -1);
}

void ComboBoxDialog::closeEvent(QCloseEvent *event)
{
    this->hide();
    event->ignore();
//    emit gotDialogResult(VALUE_DIALOG_CLOSED, -1);
}

