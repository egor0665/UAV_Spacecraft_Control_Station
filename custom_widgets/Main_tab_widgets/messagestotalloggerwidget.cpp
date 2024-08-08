#include "messagestotalloggerwidget.h"

#include <qboxlayout.h>
#include <QHeaderView>

MessagesTotalLoggerWidget::MessagesTotalLoggerWidget(QWidget *parent) : QWidget(parent)
{
    messagesTotal = 0;
    totalMessagesInfoTitleLBL.setText("Всего принято сообщений");

    messagesTableTV.setModel(&tableModel);
    messagesTableTV.horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    messagesTableTV.horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    messagesTableTV.horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
    messagesTableTV.verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    mainLayout.addWidget(&totalMessagesInfoTitleLBL,0,0);
    mainLayout.addWidget(&totalMessagesInfoLBL,0,1);
    mainLayout.addWidget(&messagesTableTV,1,0,1,2);
    this->setLayout(&mainLayout);
}

MessagesTotalLoggerWidget::~MessagesTotalLoggerWidget()
{
}

void MessagesTotalLoggerWidget::setSleep(bool sleep)
{
    this->sleep = sleep;
    tableModel.setSleep(sleep);
}

void MessagesTotalLoggerWidget::newMessageReceived(int messageId)
{
    tableModel.newMessageReceived(messageId);
    messagesTotal++;
    totalMessagesInfoLBL.setText(QString::number(messagesTotal));
}
