#ifndef COMBOBOXDIALOG_H
#define COMBOBOXDIALOG_H

#include <QDialog>
#include <structs.h>

namespace Ui {
class ComboBoxDialog;
}

class ComboBoxDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComboBoxDialog(QWidget *parent = nullptr);
    ~ComboBoxDialog();

    ComboBoxDialog(QString text, QMap<QString, int> values, QWidget *parent = nullptr);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
signals:
//    void gotDialogResult(int result, QVariant value);

    void closeButtonPressed();

protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::ComboBoxDialog *ui;
};

#endif // COMBOBOXDIALOG_H
