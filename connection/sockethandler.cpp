#include "sockethandler.h"

#include <QDataStream>
#include <QIODevice>
#include <QString>

SocketHandler::SocketHandler()
{
    port = 4400;


    socket = new QUdpSocket();
    socket->bind(QHostAddress::Any, port);

    connect(socket, SIGNAL(readyRead()), SLOT(read()));
}

SocketHandler::~SocketHandler()
{
    delete(socket);
}

// =================================================================================================================================================================================================================
// =========================================================================================== READER / WRITER =====================================================================================================
// =================================================================================================================================================================================================================

void SocketHandler::send(QByteArray str) {
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);
  out << qint64(0);
  for (int i=0;i<str.length();i++)
      out << str[i];
  out.device()->seek(qint64(0));
  out << qint64(data.size() - sizeof(qint64));
  socket->writeDatagram(data, QHostAddress::Broadcast, 4401);
}

void SocketHandler::read() {
    QByteArray datagram;
    datagram.resize(socket->pendingDatagramSize());
    QHostAddress *address = new QHostAddress();
    socket->readDatagram(datagram.data(), datagram.size(), address);

    QDataStream in(&datagram, QIODevice::ReadOnly);

    qint64 size = -1;
    if(in.device()->size() > sizeof(qint64)) {
        in >> size;
    } else return;
    if (in.device()->size() - sizeof(qint64) < size) return;
    QByteArray data;
    while (!in.atEnd())
    {
        int str;
        in >> str;
        data.append(str);
    }
    for (int i=0;i<data.length();i++)
        qDebug()<<QString::number(data[i]);
    emit gotDataFromSpacecraft(data);
}
