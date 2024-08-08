#ifndef SERIALPORTHANDLER_H
#define SERIALPORTHANDLER_H

#include <windows.h>
#include <QtSerialPort/QSerialPort>
#include <mavlink/ardupilotmega/mavlink.h>
#include "genericport.h"


class SerialPortHandler: public GenericPort
{
    Q_OBJECT

    mavlink_status_t status;
    mavlink_message_t message;


    QSerialPort *serialPort;
    QString targetPort;
    int baudRate;
    bool isOpen;

    int writeMessage(const mavlink_message_t &message);

    bool is_running(){
        return isOpen;
    }
    bool start();
    bool stop();

public:
    SerialPortHandler(int targetPort, int baudRate);
    ~SerialPortHandler();
    void openSerialPort();

protected:
    void initialize_defaults();
    bool _openPort();
    QByteArray _readPort(uint8_t *cp);
    int _writePort(char *data, uint16_t len);

private slots:
    void readMessage();
signals:
    void resultMessageReceived(mavlink_message_t message);
};

#endif // SERIALPORTHANDLER_H
