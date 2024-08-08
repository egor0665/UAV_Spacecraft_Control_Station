#ifndef TABMODULE_H
#define TABMODULE_H

#include <QLabel>
#include <mavlink/ardupilotmega/mavlink.h>

class tabModule
{
public:
    bool sleep = false;
    void setSleep(bool sleep)
    {
        this->sleep = sleep;
    }
    tabModule();
};


#endif // TABMODULE_H
