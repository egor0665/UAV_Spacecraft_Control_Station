#ifndef CHOOSEVALUEMODEL_H
#define CHOOSEVALUEMODEL_H

#include <QAbstractTableModel>
#include <structs.h>



class ChooseValueModel : public QAbstractTableModel
{
    Q_OBJECT
    QVector<ValueToFollow> values;
    int rows, columns;
public:
    explicit ChooseValueModel(QObject *parent = 0);
    void init(QVector<ValueToFollow> values);
    int rowCount (const QModelIndex & parent = QModelIndex()) const;
    int columnCount (const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index,const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    ValueToFollow getItem(int row, int column);
};

#endif // CHOOSEVALUEMODEL_H
