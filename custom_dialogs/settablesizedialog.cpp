#include "settablesizedialog.h"
#include "ui_settablesizedialog.h"

#include <QCloseEvent>

SetTableSizeDialog::SetTableSizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetTableSizeDialog)
{
    ui->setupUi(this);
}

SetTableSizeDialog::~SetTableSizeDialog()
{
    delete ui;
}

void SetTableSizeDialog::on_pushButton_clicked()
{
    this->hide();
    emit gotDialogResult(ui->spinBox->value(),ui->spinBox_2->value());
}


void SetTableSizeDialog::on_pushButton_2_clicked()
{
    this->hide();
    emit dialogClosed();
}

void SetTableSizeDialog::closeEvent(QCloseEvent *event)
{
    this->hide();
    event->ignore();
    emit dialogClosed();
}
