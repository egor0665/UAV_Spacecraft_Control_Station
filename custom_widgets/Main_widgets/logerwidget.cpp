#include "logerwidget.h"

#include <QGridLayout>

LogerWidget::LogerWidget(QWidget *parent) : QWidget(parent)
{
    textField.setMaximumWidth(200);
//    this->setMaximumWidth(200);
//    this->setMinimumWidth(100);
    textField.setReadOnly(true);
    clearButton.setText("Очистить");
    connect(&clearButton,&QPushButton::clicked,this,&LogerWidget::handleClearButtonClicked);
    this->addLog(QTime().currentTime(),0,"Программа запущена");
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(&clearButton,1,0);
    mainLayout->addWidget(&textField,0,0);
    this->setLayout(mainLayout);
}

void LogerWidget::handleClearButtonClicked()
{
    textField.clear();
}

// =================================================================================================================================================================================================================
// =================================================================================== LOGER =======================================================================================================================
// =================================================================================================================================================================================================================


void LogerWidget::addLog(QTime time, int logType, QString log)
{
    QString logMessage;
    QString color;
    QString messageType;
    switch (logType)
    {
    case NORMAL_MESSAGE_TYPE:
    {
        color = "#E1E2E2";
        messageType = "INFO";
        break;
    }
    case SUCCESS_MESSAGE_TYPE:
    {
        color = "green";
        messageType = "SUCCESS";
        break;
    }
    case WARNING_MESSAGE_TYPE:
    {
        color = "red";
        messageType = "WARNING";
        break;
    }
    default:
        color = "#E1E2E2";
        break;
    }
    logMessage.append("<font color = " + color + ">");
    logMessage.append(time.toString("hh:mm:ss.zzz"));
    logMessage.append(" -- ");
    logMessage.append(messageType);
    logMessage.append(" -- ");
    logMessage.append(log);
    logMessage.append("<\\font>");
    textField.append(logMessage);

}
