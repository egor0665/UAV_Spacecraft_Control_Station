#include "processdialog.h"
#include "ui_processdialog.h"

ProcessDialog::ProcessDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProcessDialog)
{
    ui->setupUi(this);
}

ProcessDialog::~ProcessDialog()
{
    delete ui;
}

void ProcessDialog::updateStatus(int progress, QString status)
{
    ui->progressBar->setValue(progress);
    ui->label->setText(status);
}

void ProcessDialog::on_pushButton_clicked()
{
    emit closeButtonPressed();
}

