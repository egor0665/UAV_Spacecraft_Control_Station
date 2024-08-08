#ifndef CHOOSEVALUETOFOLLOWDIALOG_H
#define CHOOSEVALUETOFOLLOWDIALOG_H

#include "structs.h"

#include <QDialog>

#include <custom_models/choosevaluemodel.h>

namespace Ui {
class ChooseValueToFollowDialog;
}

class ChooseValueToFollowDialog : public QDialog
{
    Q_OBJECT
    static QVector<QString> colors;
    ChooseValueModel chooseValueModel;
public:
    explicit ChooseValueToFollowDialog(QVector<ValueToFollow> values, QWidget *parent = nullptr);
    ~ChooseValueToFollowDialog();

private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::ChooseValueToFollowDialog *ui;
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void gotDialogResult(ValueToFollow);
    void dialogClosed();
};

#endif // CHOOSEVALUETOFOLLOWDIALOG_H
