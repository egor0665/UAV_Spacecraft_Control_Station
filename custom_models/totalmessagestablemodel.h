#ifndef TOTALMESSAGESTABLEMODEL_H
#define TOTALMESSAGESTABLEMODEL_H
#include <QAbstractTableModel>
#include <QMetaType>
#include <QPixmap>
#include <QTime>
#include <QTimer>
#include <QVector>

#include <custom_widgets/Main_widgets/logerwidget.h>
#include <mavlink/ardupilotmega/mavlink.h>

struct MessageInfo
{
    int messageCode;
    QString messageName;
    int messagesTotal;
    QTime lastMessage;
    MessageInfo(){};
    MessageInfo(int messageCode, QString messageName, int messagesTotal, QTime lastMessage)
    {
        this->messageCode = messageCode;
        this->messageName = messageName;
        this->messagesTotal = messagesTotal;
        this->lastMessage = lastMessage;
    };
};
Q_DECLARE_METATYPE(MessageInfo);

class TotalMessagesTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QTimer *updateViewTimer;

    bool sleep = false;

//    LogerWidget *logerWidget;
public:
    explicit TotalMessagesTableModel(QObject *parent = 0);
    ~TotalMessagesTableModel();
    int rowCount (const QModelIndex & parent = QModelIndex()) const;
    int columnCount (const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index,const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex) const;
//    void appendSpaceCraftStatusData(SpacecraftStatusData dataItem);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool spacecraftInTable(unsigned int spacecraftId);
//    void updateSpaceCraftStatusData(SpacecraftStatusData dataItem); // TODO переместить в модель
    void updateSpaceCraftLastPing(unsigned int spacecraftId, QTime time);

    //    QVector<SpacecraftStatusData> *getSpacecraftList();
    void newMessageReceived(int messageId);
    void setSleep(bool sleep);
private slots:
//    void updateStatusByTimer();
protected:
//    QString SecToMinHrsString(unsigned int sec);
//    void logMessage(QTime time, int logType, QVector<QString> logParts);
private:
    QVector<MessageInfo> messagesData;
//    QVector<SpacecraftStatusData> spacecraftList;
//    QVector<QPixmap> statusCircles;
signals:
    void spacecraftStatusChanged();
protected slots:
    void updateModel();
};



#endif // TOTALMESSAGESTABLEMODEL_H


