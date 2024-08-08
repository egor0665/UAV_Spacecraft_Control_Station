#include "udpport.h"

#include <QNetworkProxy>
#include <QTime>

UDPPort::UDPPort(QString target_ip_, int udp_port_)
{
    initialize_defaults();
    targetIP = target_ip_;
    targetPort  = udp_port_;
    isOpen = false;
    udpSocketRead  = new QUdpSocket(this);
    udpSocketWrite = new QUdpSocket(this);
    targetAddress = new QHostAddress(targetIP);
}

UDPPort::~UDPPort()
{
    delete(udpSocketWrite);
    delete(targetAddress);
}

void UDPPort::initialize_defaults()
{
    targetIP = "127.0.0.1";
    targetPort  = 5760;
    isOpen = false;
}

bool UDPPort::_openPort()
{
    bool openRes = udpSocketRead->bind(QHostAddress::Any, targetPort);
    connect(udpSocketRead, SIGNAL(readyRead()), this, SLOT(readMessage()));

    udpSocketWrite->connectToHost("127.0.0.1", targetPort);

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

// ------------------------------------------------------------------------------
//   Read from UDP
// ------------------------------------------------------------------------------
void UDPPort::readMessage()
{
        uint8_t          cp;
        mavlink_status_t status;
        uint8_t          msgReceived = false;
        mavlink_message_t message;


        // --------------------------------------------------------------------------
        //   READ FROM PORT
        // --------------------------------------------------------------------------
        QByteArray result = _readPort(&cp);
        if (result.length() > 0)
        {
            for (int pos = 0; pos < result.length(); ++pos)
                {
                if (!mavlink_parse_char(MAVLINK_COMM_1, (uint8_t)result[pos],
                                        &message, &status))
                    continue;
                if (message.sysid!=255)
                    emit resultMessageReceived(message);
                }
        }
        else
        {
            qDebug()<< stderr<<"ERROR: Could not read from port";
        }
        return;
}

// ------------------------------------------------------------------------------
//   Write to UDP
// ------------------------------------------------------------------------------
int UDPPort::writeMessage(const mavlink_message_t &message)
{
    char buf[300];
    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)buf, &message);
    int bytesWritten = _writePort(buf,len);
    return bytesWritten;
}


// ------------------------------------------------------------------------------
//   Open UDP Port
// ------------------------------------------------------------------------------

bool UDPPort::start()
{
    isOpen = _openPort();
    return isOpen;
}


// ------------------------------------------------------------------------------
//   Close UDP Port
// ------------------------------------------------------------------------------
bool UDPPort::stop()
{
    udpSocketRead->close();

    isOpen = false;
    return !isOpen;
}

// ------------------------------------------------------------------------------
//   Read Port with Lock
// ------------------------------------------------------------------------------
QByteArray UDPPort::_readPort(uint8_t *cp)
{
    QByteArray datagram;
    datagram.resize(udpSocketRead->pendingDatagramSize());
    QHostAddress *address = new QHostAddress();
    quint16 port = 0;
    udpSocketRead->readDatagram(datagram.data(), datagram.size(), address, &port);
    targetPort = port;
    qDebug() << datagram.length();
    return datagram;
}


// ------------------------------------------------------------------------------
//   Write Port with Lock
// ------------------------------------------------------------------------------
int UDPPort::_writePort(char *data, uint16_t len)
{
    int resBytesWritten;
    targetPort = 14550;
    resBytesWritten = udpSocketWrite->writeDatagram(data,len, QHostAddress::LocalHost, targetPort);
    qDebug()<<"res bytes written " + QString::number(resBytesWritten);
    return resBytesWritten;
}


