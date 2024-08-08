#include "tcpport.h"

#include "TCPPort.h"
#include <QNetworkProxy>

TCPPort::TCPPort(QString target_ip_, int tcp_port_)
{
    initialize_defaults();
    targetIP = target_ip_;
    targetPort  = tcp_port_;
    isOpen = false;
    tcpSocketRead  = new QTcpSocket(this);
    connect(tcpSocketRead, SIGNAL(readyRead()), this, SLOT(readMessage()));
}


TCPPort::~TCPPort()
{
    delete(tcpSocketRead);
}

void TCPPort::initialize_defaults()
{
    // Initialize attributes
    targetIP = "127.0.0.1";
    targetPort  = 5760;
    isOpen = false;
}

qint32 ArrayToInt(QByteArray source)
{
    qint32 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}

bool TCPPort::_openPort()
{
    tcpSocketRead->connectToHost(QHostAddress::LocalHost, targetPort);
    bool res = tcpSocketRead->waitForConnected();
    return res;
}

// ------------------------------------------------------------------------------
//   Read from UDP
// ------------------------------------------------------------------------------
void TCPPort::readMessage()
{
    uint8_t          cp;
    mavlink_status_t status;
    uint8_t          msgReceived = false;
    mavlink_message_t message;


    // --------------------------------------------------------------------------
    //   READ FROM PORT
    // --------------------------------------------------------------------------


    QByteArray result = _readPort(&cp);

//    qDebug()<<result;
//    qDebug()<<"serial incoming size " + QString::number(result.length());

//    if ((result.length()>0) && (result[result.length()-1] =='\n'))
//        result.remove(result.length()-1,1);
//    if ((result.length()>0) && (result[result.length()-1] =='\r'))
//        result.remove(result.length()-1,1);
//    if ((result.length()>0) && (result[0] =='?'))
//        result.remove(0,1);

//    std::string a = result.toStdString();
//    qDebug() << "serial incoming data: " +a;
//    QString resString = QString::fromStdString(a);


//    qDebug() << "serial incoming data: " + resString;
//    qDebug() << result.size() << result;

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

    emit resultMessageReceived(message);
    return;
}

// ------------------------------------------------------------------------------
//   Write to UDP
// ------------------------------------------------------------------------------
int TCPPort::writeMessage(const mavlink_message_t &message)
{
    char buf[300];

    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)buf, &message);
    int bytesWritten = _writePort(buf,len);
    return bytesWritten;
}


// ------------------------------------------------------------------------------
//   Open UDP Port
// ------------------------------------------------------------------------------

bool TCPPort::start()
{
    isOpen = _openPort();
    return isOpen;
}


// ------------------------------------------------------------------------------
//   Close UDP Port
// ------------------------------------------------------------------------------
bool TCPPort::stop()
{
    tcpSocketRead->close();

    isOpen = false;
    return isOpen;
}

// ------------------------------------------------------------------------------
//   Read Port with Lock
// ------------------------------------------------------------------------------
QByteArray TCPPort::_readPort(uint8_t *cp)
{
    QByteArray datagram;
    datagram = tcpSocketRead->readAll(); // readDatagram(datagram.data(), datagram.size(), address, &port);
    return datagram;
}


// ------------------------------------------------------------------------------
//   Write Port with Lock
// ------------------------------------------------------------------------------
int TCPPort::_writePort(char *data, uint16_t len)
{
    QVector<int> msg;
    for (int i=0;i<len;i++)
        msg.append(data[i]);
    qDebug()<< "sending message "<< msg;
    int resBytesWritten =  tcpSocketRead->write(data,len);
    return resBytesWritten;
}


