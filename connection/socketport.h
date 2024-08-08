#ifndef SOCKETPORT_H
#define SOCKETPORT_H

#include <mavlink/ardupilotmega/mavlink.h>
#include <QtSerialPort/qserialport.h>
#include <QtNetwork/QUdpSocket>
#include "genericport.h"
#include <pthread.h>
#include <QtNetwork/QtNetwork>

class SocketPort: public GenericPort
{
    Q_OBJECT
public:
    SocketPort(int port_, int targetPort);
    ~SocketPort();
    int writeMessage(const mavlink_message_t &message);

    bool is_running(){
        return isOpen;
    }
    bool start();
    bool stop();
private:

    void initializeDefaults();
    int port;
    int targetPort;

    bool isOpen;
    QUdpSocket *socket;

    bool  _openPort();
    bool _setupPort(int baud, int data_bits, int stop_bits, bool parity, bool hardware_control);
    QByteArray _readPort(uint8_t *cp);
    int _writePort(char *data, uint16_t len, int targetPort);
private slots:
    void readMessage();
signals:
    void resultMessageReceived(mavlink_message_t message);
};

#endif // SOCKETPORT_H
