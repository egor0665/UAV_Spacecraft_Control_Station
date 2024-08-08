#include "connectionhandler.h"


ConnectionHandler::ConnectionHandler(QObject *parent, LogerWidget *logerWidget)
    : QObject(parent)
{
    this->logerWidget = logerWidget;
    connect(&messageTimer, &QTimer::timeout, this, &ConnectionHandler::sendMessageFromBuffer);
}

void ConnectionHandler::sendMessageFromBuffer()
{
    if (!messageBuffer.isEmpty())
    {
        port->writeMessage(messageBuffer[0]);
        messageBuffer.remove(0);
    }
//    qDebug()<<QString::number(messageBuffer.length());
}

ConnectionHandler::~ConnectionHandler()
{
    switch(currentPort)
    {
    case PortEnum::SocketPort:
    {
        delete (qobject_cast<SocketPort*>(port));
        break;
    }
    case PortEnum::SerialPort:
    {
        //TODO
        break;
    }
    case PortEnum::UDPPort:
    {
        delete (qobject_cast<UDPPort*>(port));
        break;
    }
    case PortEnum::TCPPort:
    {
        //TODO
        //disconnect(qobject_cast<SocketPort*>(port), &SocketPort::resultMessageReceived, this, &ConnectionHandler::handleDataFromPort);
        break;
    }
    case PortEnum::NoPort:
    {
//        return false;
        break;
    }
    default:
        break;
    }

//    delete (logerWidget);
}

bool ConnectionHandler::disconnectFromPort()
{
    switch(currentPort)
    {
    case PortEnum::SocketPort:
    {
        disconnect(qobject_cast<SocketPort*>(port), &SocketPort::resultMessageReceived, this, &ConnectionHandler::handleDataFromPort);
        break;
    }
    case PortEnum::SerialPort:
    {
        //TODO
        break;
    }
    case PortEnum::UDPPort:
    {
        disconnect(qobject_cast<UDPPort*>(port), &UDPPort::resultMessageReceived, this, &ConnectionHandler::handleDataFromPort);
        break;
    }
    case PortEnum::TCPPort:
    {
        //TODO
        //disconnect(qobject_cast<SocketPort*>(port), &SocketPort::resultMessageReceived, this, &ConnectionHandler::handleDataFromPort);
        break;
    }
    case PortEnum::NoPort:
    {
        return false;
        break;
    }
    default:
        break;
    }
    port->stop();
    stopMessageTimer();
    bool deleted = !port->is_running();
    if (deleted)
    {
        logerWidget->addLog(QTime().currentTime(), SUCCESS_MESSAGE_TYPE ,"Аппарат отключен");
        currentPort = PortEnum::NoPort;
        delete port;
    }
    else
    {
        logerWidget->addLog(QTime().currentTime(), WARNING_MESSAGE_TYPE,"Не удалось отключиться от аппарата");
    }
    return deleted;
}

const int TCPTimerInterval = 100;
const int SerialTimerInterval = 300;

bool ConnectionHandler::connectToPort(QString ipAddress, PortEnum connectionType, int baudRate, int portNum)
{
    if (!(currentPort == PortEnum::NoPort))
        delete port;

    switch (connectionType){
    case PortEnum::SocketPort:
    {
        int targetPort = 4401;
        port = new SocketPort(portNum,targetPort);
        port->start();

        connect(qobject_cast<SocketPort*>(port), &SocketPort::resultMessageReceived, this, &ConnectionHandler::handleDataFromPort);

        startMessageTimer(TCPTimerInterval);
        break;
    }
    case PortEnum::SerialPort:
    {
        port = new SerialPortHandler(portNum,baudRate);
        port->start();

        connect(qobject_cast<SerialPortHandler*>(port), &SerialPortHandler::resultMessageReceived, this, &ConnectionHandler::handleDataFromPort);

        startMessageTimer(SerialTimerInterval);
        break;
    }
    case PortEnum::UDPPort:
    {
        port = new UDPPort(ipAddress, portNum);
        port->start();

        connect(qobject_cast<UDPPort*>(port), &UDPPort::resultMessageReceived, this, &ConnectionHandler::handleDataFromPort);

        startMessageTimer(TCPTimerInterval);
        break;
    }
    case PortEnum::TCPPort:
    {
        port = new TCPPort(ipAddress, portNum);
        port->start();
        connect(qobject_cast<TCPPort*>(port), &TCPPort::resultMessageReceived, this, &ConnectionHandler::handleDataFromPort);      
        startMessageTimer(TCPTimerInterval);
        break;
    }
    default:
        break;
    }
    bool opened = port->is_running();

    if (opened)
    {
        logerWidget->addLog(QTime().currentTime(), SUCCESS_MESSAGE_TYPE,"Удалось подключиться к порту");
        currentPort = connectionType;
    }
    else
    {
        currentPort = PortEnum::NoPort;
        logerWidget->addLog(QTime().currentTime(), WARNING_MESSAGE_TYPE,"Не удалось подключиться к порту");
    }
    return opened;
}

void ConnectionHandler::startMessageTimer(int interval)
{
    messageTimer.setInterval(interval);
    messageTimer.start();
}

void ConnectionHandler::stopMessageTimer()
{
     messageTimer.stop();
}

// =================================================================================================================================================================================================================
// ============================================================================== DATA FROM CONNECTION HANDLERS ====================================================================================================
// =================================================================================================================================================================================================================

int ConnectionHandler::writeMessage(mavlink_message_t message)
{
    messageBuffer.append(message);
    return messageBuffer.length();
}


void ConnectionHandler::handleDataFromPort(mavlink_message_t message)
{
//        qDebug()<<QString::number(message.msgid) + " " + QString::number(message.seq);
    if (message.sysid == 1 && message.compid == 1)
    {
        emit newMessageReceived(message);
//        int messageId = frameHandler->handleMessage(message);
//        emit newMessageDecoded(messageId);
    }
    else
    {
//        qDebug()<<QString::number(message.sysid)<<QString::number(message.compid);
    }
}

// =================================================================================================================================================================================================================
// ================================================================================ SEND DATA TO CONNECTIONS =======================================================================================================
// =================================================================================================================================================================================================================


//void ConnectionHandler::sendMessageToPort(QByteArray message)
//{
//    socketHandler->send(message);
//}
