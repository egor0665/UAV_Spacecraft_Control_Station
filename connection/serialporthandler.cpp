#include "serialporthandler.h"
#include <QDebug>
#include <string>

SerialPortHandler::SerialPortHandler(int targetPort, int baudRate)
{
    initialize_defaults();
    this->targetPort = "COM" + QString::number(targetPort);
    this->baudRate = baudRate;
    serialPort = new QSerialPort();
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(readMessage()));
    openSerialPort();
}

void SerialPortHandler::initialize_defaults()
{
    // Initialize attributes
    targetPort = "COM1";
    baudRate = QSerialPort::Baud9600;
    isOpen = false;
}


SerialPortHandler::~SerialPortHandler()
{
    delete(serialPort);
}

// =================================================================================================================================================================================================================
// =========================================================================================== OPEN CONNECTION =====================================================================================================
// =================================================================================================================================================================================================================

void SerialPortHandler::openSerialPort()
{
    serialPort->setPortName(targetPort);
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (serialPort->open(QIODevice::ReadWrite))
    {
        qDebug()<< "serial opened";
//        this->start();
    }
    else
    {
        qDebug()<< "serial error";
        serialPort->error();
    }
}

bool SerialPortHandler::_openPort()
{
    serialPort->open(QIODevice::ReadWrite);
    return serialPort->isOpen();
}


// =================================================================================================================================================================================================================
// =========================================================================================== READER / WRITER =====================================================================================================
// =================================================================================================================================================================================================================


void SerialPortHandler::readMessage()
{
    uint8_t          cp;
    uint8_t          msgReceived = false;

    char buffer[1];

    QVector<uint8_t> msg;

    while(serialPort->bytesAvailable()>0)
    {
        serialPort->read(buffer,1);
        msg.append(buffer[0]);
        if (mavlink_parse_char(MAVLINK_COMM_1, (uint8_t)buffer[0], &message, &status))
        {
//            qDebug()<<message.sysid;
            emit resultMessageReceived(message);
//            break;

        }
    }
    //qDebug()<<msg;



//    emit resultMessageReceived(message);

//    QByteArray result = _readPort(&cp);


//    qDebug()<<result;
//    qDebug()<<"serial incoming size " + QString::number(result.length());


//    if ((result.length()>0) && (result[result.length()-1] =='\n'))
//        result.remove(result.length()-1,1);
//    if ((result.length()>0) && (result[result.length()-1] =='\r'))
//        result.remove(result.length()-1,1);

//    std::string a = result.toStdString();
//    QString resString = QString::fromStdString(a);

//    qDebug() << "serial incoming data: " + resString;


//    if (result.length() > 0)
//    {
//        for (int pos = 0; pos < result.length(); ++pos)
//            {
//            msgReceived = mavlink_parse_char(MAVLINK_COMM_1, (uint8_t)result[pos], &message, &status);
//            if (!msgReceived)
//                continue;
//            emit resultMessageReceived(message);
//            }
//    }
//    else
//    {
//        qDebug()<< stderr<<"ERROR: Could not read from port";
//    }

//    emit resultMessageReceived(message);
    return;
}

int SerialPortHandler::writeMessage(const mavlink_message_t &message)
{
    char buf[300];
    int len = mavlink_msg_to_send_buffer((uint8_t*)buf, &message);
    int bytesWritten = _writePort(buf,len);
    return bytesWritten;

}


QByteArray SerialPortHandler::_readPort(uint8_t *cp)
{

    return serialPort->readAll();
}

int SerialPortHandler::_writePort(char *data, uint16_t len)
{
    //qDebug()<<len;
//    QVector<int> msg;
//    for (int i=0;i<len;i++)
//        msg.append(data[i]);
    //qDebug()<< "sending message "<< msg;
    int resBytesWritten = serialPort->write(data,len);
    //qDebug()<<resBytesWritten;
    return resBytesWritten;
}


bool SerialPortHandler::start()
{
    isOpen = _openPort();
    return isOpen;
}

bool SerialPortHandler::stop()
{
    serialPort->close();

    isOpen = false;
    return isOpen;
}
