#include "customfilemanager.h"

#include <QException>
#include <QFile>
#include <QTextStream>

#include <exceptions/cantreadwritefileexception.h>

CustomFileManager::CustomFileManager()
{

}

void CustomFileManager::saveToFile(QString missionText, QString filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        CantReadWriteFileException e("Не удалось открыть файл на запись");
        e.raise();
        return;
    }
    QTextStream out(&file);
    out << missionText;
}

QString CustomFileManager::readFromFile(QString filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        CantReadWriteFileException e("Не удалось открыть файл на считывание");
        e.raise();
        return "";
    }
    QTextStream in(&file);
    QString missionText;
    while (!in.atEnd())
    {
         missionText += in.readLine();
         missionText += '\n';
    }

    return missionText;
}
