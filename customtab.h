#ifndef CUSTOMTAB_H
#define CUSTOMTAB_H

#include <QGridLayout>
#include <QObject>

class CustomTab
{
public:
    CustomTab(){};
    ~CustomTab()
    {
    };
    QGridLayout mainLayout;
    bool isCurrentTab;
    virtual void setCurrent(bool current) = 0;
};

#endif // CUSTOMTAB_H
