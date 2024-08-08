#ifndef TCPPORT_H
#define TCPPORT_H

#include <mavlink/ardupilotmega/mavlink.h>
#include <QTcpSocket>
#include <QUdpSocket>
#include "genericport.h"

class TCPPort: public GenericPort
{
    Q_OBJECT
public:
    TCPPort(QString target_ip_, int udp_port_);
    ~TCPPort();


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

    QTcpSocket *tcpSocketRead;

    bool  _openPort();
    QByteArray _readPort(uint8_t *cp);
    int _writePort(char *data, uint16_t len);
private slots:
    void readMessage();
signals:
    void resultMessageReceived(mavlink_message_t message);
};

#endif // TCPPORT_H
