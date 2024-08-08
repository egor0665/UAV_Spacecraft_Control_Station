#ifndef CUSTOMFILEMANAGER_H
#define CUSTOMFILEMANAGER_H

#include <QString>

class CustomFileManager
{
public:
    CustomFileManager();
    void saveToFile(QString missionText, QString filePath);
    QString readFromFile(QString filePath);
};

#endif // CUSTOMFILEMANAGER_H
