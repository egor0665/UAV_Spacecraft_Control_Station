#ifndef SETTINGSMENULISTMODEL_H
#define SETTINGSMENULISTMODEL_H

#include <QAbstractListModel>

struct MenuItem
{
    QString itemName;
    int index;
    MenuItem(QString itemName, int index)
    {
        this->itemName = itemName;
        this->index = index;
    }
    MenuItem(){};
};
Q_DECLARE_METATYPE(MenuItem);

class SettingsMenuListModel: public QAbstractListModel
{   
    Q_OBJECT
public:
    explicit SettingsMenuListModel(QObject *parent=0);

    int rowCount (const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index,const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setCurrentIndex(int index);
protected:
    int currentItemIndex;
    QVector<MenuItem> menuVector;
signals:
    void spacecraftStatusChanged();
protected slots:
//    void updateModel();

};

#endif // SETTINGSMENULISTMODEL_H
