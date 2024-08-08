#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

#include <QString>
#include <QVector>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QtNetwork>

class SocketHandler: public QObject
{
    Q_OBJECT
    QUdpSocket *socket;
    int port;
public:
    SocketHandler();
    ~SocketHandler();
    void send(QByteArray str);
public slots:
    void read();
signals:
    void gotDataFromSpacecraft(QByteArray data);
};

#endif // SOCKETHANDLER_H



