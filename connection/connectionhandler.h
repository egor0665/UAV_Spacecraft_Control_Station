#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include "framehandler.h"
#include "serialporthandler.h"
#include "sockethandler.h"
#include "socketport.h"
#include <QWidget>
#include <custom_widgets/Main_widgets/logerwidget.h>
#include "udpport.h"
#include "tcpport.h"

enum class PortEnum
{
    SocketPort = 0,
    SerialPort = 1,
    UDPPort = 2,
    TCPPort = 3,
    NoPort = 4
};

class ConnectionHandler: public QObject
{
    Q_OBJECT
    GenericPort *port = nullptr;
    LogerWidget *logerWidget;
    PortEnum currentPort = PortEnum::NoPort;

    QVector<mavlink_message_t> messageBuffer;
    QTimer messageTimer;

public:
    ConnectionHandler(QObject *parent = nullptr, LogerWidget *logerWidget = nullptr);
    ~ConnectionHandler();

    bool connectToPort(QString ipAddress, PortEnum connectionType, int baudRate, int portNum);
    bool disconnectFromPort();
    int writeMessage(mavlink_message_t message);
protected slots:
    void handleDataFromPort(mavlink_message_t message);
    void sendMessageFromBuffer();
signals:
    void newMessageReceived(mavlink_message_t message);
protected:
    void startMessageTimer(int interval);
    void stopMessageTimer();
};

#endif // CONNECTIONHANDLER_H
