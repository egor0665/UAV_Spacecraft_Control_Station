#include "socketport.h"

SocketPort::SocketPort(int port_, int targetPort_)
{
    initializeDefaults();

    port = port_;
    targetPort = targetPort_;
    socket = new QUdpSocket();
    connect(socket, SIGNAL(readyRead()),this, SLOT(readMessage()));
}

// =================================================================================================================================================================================================================
// ============================================================================== CON/DE STRUCTORS =================================================================================================================
// =================================================================================================================================================================================================================

SocketPort::~SocketPort()
{
    delete(socket);
}

void SocketPort::initializeDefaults()
{
    isOpen = false;
}

// =================================================================================================================================================================================================================
// ============================================================================= OPEN CLOSE SOCKET PORT ============================================================================================================
// =================================================================================================================================================================================================================


bool SocketPort::start()
{
    isOpen = _openPort();
    return isOpen;
}

bool SocketPort::_openPort()
{
    bool openRes = socket->bind(QHostAddress::Any, port);
    if (openRes)
    {
        qDebug()<< "socket binded";
    }
    else
    {
        qDebug()<< "socket error";
    }
    return openRes;
}

bool SocketPort::stop()
{
    socket->close();
    isOpen = false;
    return !isOpen;
}

// =================================================================================================================================================================================================================
// ============================================================================== READ WRITE SOCKET ================================================================================================================
// =================================================================================================================================================================================================================

void SocketPort::readMessage() //mavlink_message_t &message
{
    uint8_t           cp;
    mavlink_status_t  status;
    uint8_t           msgReceived = false;
    mavlink_message_t message;

    QByteArray result = _readPort(&cp);

    // --------------------------------------------------------------------------
    //   PARSE MESSAGE
    // --------------------------------------------------------------------------
    if (result.length() > 0)
    {
        for (int pos = 0; pos < result.length(); ++pos)
            {
            msgReceived = mavlink_parse_char(MAVLINK_COMM_1, (uint8_t)result[pos], &message, &status);
            if (!msgReceived)
                continue;
            emit resultMessageReceived(message);
            }
    }
    else
    {
        qDebug()<< stderr<<"ERROR: Could not read from port";
    }
    return;
}

QByteArray SocketPort::_readPort(uint8_t *cp)
{
    QByteArray datagram;
    datagram.resize(socket->pendingDatagramSize());
    QHostAddress *address = new QHostAddress();
    socket->readDatagram(datagram.data(), datagram.size(), address);
    QDataStream in(&datagram, QIODevice::ReadOnly);
    QByteArray data;
    while (!in.atEnd())
    {
        int str;
        in >> str;
        data.append(str);
    }
    return data;
}

int SocketPort::writeMessage(const mavlink_message_t &message)
{
    char buf[300];

    // Translate message to buffer
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)buf, &message);

    // Write buffer to serial port, locks port while writing
    int bytesWritten = _writePort(buf,len,targetPort);

    return bytesWritten;
}

int SocketPort::_writePort(char *data, uint16_t len, int targetPort)
{
    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    for (int i=0;i<len;i++)
        out << data[i];
    out << qint64(len - sizeof(qint64));
    int resBytesWritten = socket->writeDatagram(byteArray, QHostAddress::Broadcast, targetPort);
    return resBytesWritten;
}
