#ifndef MESSAGESTOTALLOGGERWIDGET_H
#define MESSAGESTOTALLOGGERWIDGET_H

#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QTableView>
#include <QTime>
#include <mavlink/ardupilotmega/mavlink.h>
#include <custom_models/totalmessagestablemodel.h>
#include "custom_widgets/tabmodule.h"


class MessagesTotalLoggerWidget: public QWidget, public tabModule
{
    QGridLayout mainLayout;
    TotalMessagesTableModel tableModel;
    int messagesTotal = 0;
    QTableView messagesTableTV;
    QLabel totalMessagesInfoLBL;
    QLabel totalMessagesInfoTitleLBL;
public:
    MessagesTotalLoggerWidget(QWidget *parent = nullptr);
    ~MessagesTotalLoggerWidget();
    void newMessageReceived(int messageId);
    void setSleep(bool sleep);
};


#endif // MESSAGESTOTALLOGGERWIDGET_H
