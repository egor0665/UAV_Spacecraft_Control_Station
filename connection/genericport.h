#ifndef GENERICPORT_H
#define GENERICPORT_H

#include <mavlink/ardupilotmega/mavlink.h>
#include <QWidget>

class GenericPort :public QObject
{
    Q_OBJECT
public:
    GenericPort(){};
    virtual ~GenericPort(){};
//    virtual readMessage(mavlink_message_t &message)=0;
    virtual int writeMessage(const mavlink_message_t &message)=0;
    virtual bool is_running()=0;
    virtual bool start()=0;
    virtual bool stop()=0;
private slots:
    virtual void readMessage()=0;
signals:
    virtual void resultMessageReceived(mavlink_message_t)=0;
};

#endif // GENERICPORT_H
