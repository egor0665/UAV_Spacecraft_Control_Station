#ifndef UDPPORT_H
#define UDPPORT_H

#include <mavlink/ardupilotmega/mavlink.h>
#include <QUdpSocket>
#include "genericport.h"

class UDPPort: public GenericPort
{
    Q_OBJECT
public:
//    UDPPort();
    UDPPort(QString target_ip_, int udp_port_);
    ~UDPPort();


    int writeMessage(const mavlink_message_t &message);

    bool is_running(){
        return isOpen;
    }
    bool start();
    bool stop();
private:

    void initialize_defaults();

    QString targetIP;
    int targetPort;
    bool isOpen;

    QUdpSocket *udpSocketRead;
    QUdpSocket *udpSocketWrite;
    QHostAddress *targetAddress;

    bool  _openPort();
    QByteArray _readPort(uint8_t *cp);
    int _writePort(char *data, uint16_t len);
private slots:
    void readMessage();
signals:
    void resultMessageReceived(mavlink_message_t message);
};

#endif // UDPPORT_H
