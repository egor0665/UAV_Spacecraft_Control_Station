#ifndef LOGERWIDGET_H
#define LOGERWIDGET_H

#include "custom_widgets/tabmodule.h"

#include <QPushButton>
#include <QTextEdit>
#include <QTime>
#include <QWidget>


typedef enum LOGGER_MESSAGE_TYPE
{
    NORMAL_MESSAGE_TYPE = 0,
    SUCCESS_MESSAGE_TYPE = 1,
    WARNING_MESSAGE_TYPE = 2,

} LOGGER_MESSAGE_TYPE;

class LogerWidget: public QWidget, public tabModule
{
    Q_OBJECT
    QPushButton clearButton;
    QTextEdit textField;
    unsigned int messagesCount = 0;
public:
    LogerWidget(QWidget *parent = nullptr);
    void addLog(QTime time, int logType, QString log);
public slots:

protected slots:
    void handleClearButtonClicked();
};

#endif // LOGERWIDGET_H
