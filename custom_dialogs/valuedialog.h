#ifndef VALUEDIALOG_H
#define VALUEDIALOG_H

#include <QDialog>
#include <QVariant>
#include <structs.h>

namespace Ui {
class ValueDialog;
}

class ValueDialog : public QDialog
{
    Q_OBJECT
    int valueType;

public:
    explicit ValueDialog(QString text, int valueType, QWidget *parent = nullptr);
    ~ValueDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
signals:
    void gotDialogResult(int result, QVariant value);

    void closeButtonPressed();

protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::ValueDialog *ui;
};

#endif // VALUEDIALOG_H
