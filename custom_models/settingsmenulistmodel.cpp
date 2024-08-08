#include "settingsmenulistmodel.h"

#include <QBrush>
#include <QDebug>
#include <QFont>
#include <QFont>
#include <QVector>
#include <structs.h>

SettingsMenuListModel::SettingsMenuListModel(QObject *parent)
    :QAbstractListModel(parent)
{
    menuVector.append(MenuItem("Параметры",0));
    menuVector.append(MenuItem("Геозона",1));
    menuVector.append(MenuItem("Другое",2));
    currentItemIndex = 0;
}

void SettingsMenuListModel::setCurrentIndex(int index)
{
    beginResetModel();
    currentItemIndex = index;
    endResetModel();
}

// =================================================================================================================================================================================================================
// ========================================================================= DEFAULT MODEL OVERRIDED FUNCTIONS =====================================================================================================
// =================================================================================================================================================================================================================


int SettingsMenuListModel::rowCount(const QModelIndex &parent) const
{
    return menuVector.length();
}


QVariant SettingsMenuListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch(role){
    case Qt::DisplayRole: //0	The key data to be rendered in the form of text. (QString)
    {
        return menuVector[index.row()].itemName;
        break;
    }

    case Qt:: DecorationRole: //1	The data to be rendered as a decoration in the form of an icon. (QColor, QIcon or QPixmap)
        return QVariant();
    case Qt::EditRole: //2 The data in a form suitable for editing in an editor. (QString)
        return QVariant();
    case Qt::ToolTipRole:
        return QVariant();
    case Qt::StatusTipRole: //4	The data displayed in the status bar. (QString)
        return  QVariant();
    case Qt::WhatsThisRole: //5	The data displayed for the item in "What's This?" mode. (QString)
        return QVariant();
    case Qt::FontRole: //6	The font used for items rendered with the default delegate. (QFont)
        return QFont("MS Shell Dlg 2", 14);
    case Qt::TextAlignmentRole: //7	The alignment of the text for items rendered with the default delegate. (Qt::Alignment)
        switch(index.column()){
            return QVariant();
        }
    case Qt::BackgroundRole: //8	The background brush used for items rendered with the default delegate. (QBrush)
    {
        if (currentItemIndex == index.row())
            return QBrush(QColor("#2d3238"));
        else
            return QBrush(QColor("#1d2228"));
    }
    case Qt::ForegroundRole: //9	The foreground brush (text color, typically) used for items rendered with the default delegate. (QBrush)
        return QVariant();
    case Qt::CheckStateRole: //10	This role is used to obtain the checked state of an item. (Qt::CheckState)
        return QVariant();
    case Qt::AccessibleTextRole: // 11	The text to be used by accessibility extensions and plugins, such as screen readers. (QString)
        return QVariant();
    case Qt::AccessibleDescriptionRole: //12	A description of the item for accessibility purposes. (QString)
        return QVariant();
    case Qt::SizeHintRole: //13 The size hint for the item that will be supplied to views. (QSize)
        return QVariant();
    case Qt::InitialSortOrderRole: //14	This role is used to obtain the initial sort order of a header view section. (Qt::SortOrder). This role was introduced in Qt 4.8.
        return QVariant();
    default:
        return QVariant();

    }

}

bool SettingsMenuListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        menuVector.replace(index.row(),qvariant_cast<MenuItem>(value));
    }
}

Qt::ItemFlags SettingsMenuListModel::flags(const QModelIndex) const
{
    return Qt::NoItemFlags;
}

QVariant SettingsMenuListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
        return QVariant();
    if (orientation == Qt::Vertical)
        return QVariant();
    return QVariant();
}
