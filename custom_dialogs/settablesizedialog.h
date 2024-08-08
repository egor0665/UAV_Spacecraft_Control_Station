#ifndef SETTABLESIZEDIALOG_H
#define SETTABLESIZEDIALOG_H

#include <QDialog>

namespace Ui {
class SetTableSizeDialog;
}

class SetTableSizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetTableSizeDialog(QWidget *parent = nullptr);
    ~SetTableSizeDialog();

private:
    Ui::SetTableSizeDialog *ui;
signals:
    void gotDialogResult(int row, int column);
    void dialogClosed();
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // SETTABLESIZEDIALOG_H
