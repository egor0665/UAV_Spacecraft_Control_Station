#include "choosevaluetofollowdialog.h"
#include "ui_choosevaluetofollowdialog.h"

#include <QCloseEvent>

ChooseValueToFollowDialog::ChooseValueToFollowDialog(QVector<ValueToFollow> values, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseValueToFollowDialog)
{
    ui->setupUi(this);
    chooseValueModel.init(values);
    ui->tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    ui->tableView->setModel(&chooseValueModel);
}

ChooseValueToFollowDialog::~ChooseValueToFollowDialog()
{
    delete ui;
}

void ChooseValueToFollowDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    this->hide();
    ValueToFollow selectedValue = chooseValueModel.getItem(index.row(),index.column());
    if (selectedValue.valueType!=-1)
    {
        emit gotDialogResult(selectedValue);
    }
}


void ChooseValueToFollowDialog::on_pushButton_clicked()
{
    this->hide();
    emit dialogClosed();
}

void ChooseValueToFollowDialog::closeEvent(QCloseEvent *event)
{
    this->hide();
    event->ignore();
    emit dialogClosed();
}

