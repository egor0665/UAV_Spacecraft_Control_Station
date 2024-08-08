#ifndef SPACECRAFTSTATUSMODEL_H
#define SPACECRAFTSTATUSMODEL_H

#include <QAbstractTableModel>
#include <QMetaType>
#include <QPixmap>
#include <QTime>
#include <QTimer>
#include <QVector>

#include <custom_widgets/logerwidget.h>

//enum SpacecraftCommunicationStatus {
//    Connected = 0,
//    Disconnected = 1,
//};

//enum SpacecraftHealthStatus {
//    Functional = 0,
//    Disabled = 1,
//    Disconnected = 2
//};


struct SpacecraftStatusData
{
    unsigned int spacecraftId;
    QString name;

    unsigned int communicationStatus;
    unsigned int activeStatus;
    unsigned int estimateBatteryChargeHrs;
    unsigned int estimateBatteryChargeMin;
    QString controller;

    QTime lastPing;
    SpacecraftStatusData(unsigned int spacecraftId,
                         QString name,
                         unsigned int communicationStatus,
                         unsigned int activeStatus,
                         unsigned int estimateBatteryChargeHrs,
                         unsigned int estimateBatteryChargeMin,
                         QString controller,
                         QTime lastPing)
    {
        this->spacecraftId = spacecraftId;
        this->name = name;
        this->communicationStatus = communicationStatus;
        this->activeStatus = activeStatus;
        this->estimateBatteryChargeHrs = estimateBatteryChargeHrs;
        this->estimateBatteryChargeMin = estimateBatteryChargeMin;
        this->controller = controller;
        this->lastPing = lastPing;
    }
    SpacecraftStatusData(){};
};
Q_DECLARE_METATYPE(SpacecraftStatusData);

class SpacecraftStatusModel : public QAbstractTableModel
{
    Q_OBJECT
    LogerWidget *logerWidget;
public:
    explicit SpacecraftStatusModel(QObject *parent = 0, LogerWidget* logerWidget = nullptr);

    int rowCount (const QModelIndex & parent = QModelIndex()) const;
    int columnCount (const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index,const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex) const;
    void appendSpaceCraftStatusData(SpacecraftStatusData dataItem);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool spacecraftInTable(unsigned int spacecraftId);
    void updateSpaceCraftStatusData(SpacecraftStatusData dataItem); // TODO переместить в модель
    void updateSpaceCraftLastPing(unsigned int spacecraftId, QTime time);

    QVector<SpacecraftStatusData> *getSpacecraftList();
private slots:
    void updateStatusByTimer();
protected:
    QString SecToMinHrsString(unsigned int sec);
    void logMessage(QTime time, int logType, QVector<QString> logParts);
private:
    QVector<SpacecraftStatusData> spacecraftList;
    QVector<QPixmap> statusCircles;
signals:
    void spacecraftStatusChanged();
};

#endif // SPACECRAFTSTATUSMODEL_H
