#include "spacecraftstatusmodel.h"

#include <QBrush>
#include <QDebug>
#include <QFont>
#include <QVector>

SpacecraftStatusModel::SpacecraftStatusModel(QObject *parent, LogerWidget *logerWidget)
    :QAbstractTableModel(parent)
{
    this->logerWidget = logerWidget;

    statusCircles.append(QPixmap("C:/Qt/5.15.2/mingw81_32/GroundControlStation/resources/greenStatusCircle.png").scaled(15,15));
    statusCircles.append(QPixmap("C:/Qt/5.15.2/mingw81_32/GroundControlStation/resources/orangeStatusCircle.png").scaled(15,15));
    statusCircles.append(QPixmap("C:/Qt/5.15.2/mingw81_32/GroundControlStation/resources/blueStatusCircle.png").scaled(15,15));
}

// =================================================================================================================================================================================================================
// ========================================================================= DEFAULT MODEL OVERRIDED FUNCTIONS =====================================================================================================
// =================================================================================================================================================================================================================


int SpacecraftStatusModel::rowCount(const QModelIndex &parent) const
{
    return spacecraftList.length();
}

int SpacecraftStatusModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QVariant SpacecraftStatusModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch(role){
    case Qt::DisplayRole: //0	The key data to be rendered in the form of text. (QString)
        switch(index.column()){
        case 0:
            return spacecraftList[index.row()].name;
            break;
        case 1:
            return QVariant();
            break;
        case 2:
            return QVariant();
            break;
        case 3:
        {
            int hrs = spacecraftList[index.row()].estimateBatteryChargeHrs;
            int min = spacecraftList[index.row()].estimateBatteryChargeMin;
            QString hrsString = QString::number(hrs);
            if (hrs < 10)
                hrsString = "0" + QString::number(hrs);
            QString minString = QString::number(min);
            if (min < 10)
                minString = "0" + QString::number(min);
            return hrsString + ":" + minString;
            break;
        }
        case 4:
            return spacecraftList[index.row()].controller;
            break;
        default:
            return QVariant();
        }
    case Qt:: DecorationRole: //1	The data to be rendered as a decoration in the form of an icon. (QColor, QIcon or QPixmap)
        switch(index.column()){
        case 0:
            return QVariant();
        case 1:
            return statusCircles[spacecraftList[index.row()].activeStatus];
            break;
        case 2:
            return statusCircles[spacecraftList[index.row()].communicationStatus];
            break;
        case 3:
            return QVariant();
            break;
        case 4:
            return QVariant();
            break;
        default:
            return QVariant();
        }

    case Qt::EditRole: //2 The data in a form suitable for editing in an editor. (QString)
        return QVariant();
    case Qt::ToolTipRole: //3	The data displayed in the item's tooltip. (QString)
        switch(index.column()){
        case 0:
            return "Название КА";
        case 1:
            switch(spacecraftList[index.row()].activeStatus){
            case 0:
                return "КА подключен";
            case 2:
                return "КА не подключен";
            default:
                return "Некорректное состояние";
            }
        case 2:
            switch(spacecraftList[index.row()].communicationStatus){
            case 0:
                return "Системы функционируют корректно";
            case 1:
                return "Подсистемы КА отключены";
            case 2:
                return "КА не подключен";
            default:
                return "Некорректное состояние";
            }
        case 3:
            return "Примерное оставшееся время работы КА";
            break;
        case 4:
            return "Управляющее устройство";
            break;
        default:
            return QVariant();
        }
    case Qt::StatusTipRole: //4	The data displayed in the status bar. (QString)
        return "fasfasfa";
    case Qt::WhatsThisRole: //5	The data displayed for the item in "What's This?" mode. (QString)
        return QVariant();
    case Qt::FontRole: //6	The font used for items rendered with the default delegate. (QFont)
        return QVariant();
    case Qt::TextAlignmentRole: //7	The alignment of the text for items rendered with the default delegate. (Qt::Alignment)
        switch(index.column()){
        case 1:
            return int(Qt::AlignRight | Qt::AlignVCenter);
            break;
        case 2:
            return int(Qt::AlignRight | Qt::AlignVCenter);
            break;
        default:
            return QVariant();
        }
    case Qt::BackgroundRole: //8	The background brush used for items rendered with the default delegate. (QBrush)
        if (index.row()%2==0)
            return QBrush(QColor(240,240,240));
        return QVariant();
    case Qt::ForegroundRole: //9	The foreground brush (text color, typically) used for items rendered with the default delegate. (QBrush)
        return QBrush(QColor(0,0,0));;
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

bool SpacecraftStatusModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        spacecraftList.replace(index.row(),qvariant_cast<SpacecraftStatusData>(value));
    }
}

Qt::ItemFlags SpacecraftStatusModel::flags(const QModelIndex) const
{
    return Qt::NoItemFlags;
}

QVariant SpacecraftStatusModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return "Имя";
        case 1:
            return "Активен";
        case 2:
            return "Связь";
        case 3:
            return "Батарея";
        case 4:
            return "Контроллер";
        default:
            return QVariant();
        }
    }
    if (orientation == Qt::Vertical)
    {
        return section;
    }
    return QVariant();
}

// =================================================================================================================================================================================================================
// ============================================================================= CHANGE SPACECRAFT STATUS DATA =====================================================================================================
// =================================================================================================================================================================================================================

void SpacecraftStatusModel::appendSpaceCraftStatusData(SpacecraftStatusData dataItem)
{
    beginResetModel();
    spacecraftList.append(dataItem);
    endResetModel();
    emit spacecraftStatusChanged();
}

void SpacecraftStatusModel::updateSpaceCraftStatusData(SpacecraftStatusData dataItem)
{
    beginResetModel();
    unsigned int spacecraftId = dataItem.spacecraftId;
    int index=-1;
    for(int i=0;i<spacecraftList.length();i++)
    {
        if (spacecraftList[i].spacecraftId == spacecraftId)
        {
            index = i;
            logMessage(QTime().currentTime(), 0, {"Обновлены данные о", spacecraftList[index].name});
        }
    }
    spacecraftList[index] = dataItem;

    endResetModel();
    emit spacecraftStatusChanged();
}

// =================================================================================================================================================================================================================
// ======================================================================== CONNECTION STATUS BY TIMER HANDLER =====================================================================================================
// =================================================================================================================================================================================================================


void SpacecraftStatusModel::updateSpaceCraftLastPing(unsigned int spacecraftId, QTime time)
{
    for (int i=0;i<spacecraftList.length();i++)
    {
        if (spacecraftList[i].spacecraftId == spacecraftId)
        {
            spacecraftList[i].lastPing = time;
            emit spacecraftStatusChanged();
        }
    }
}

void SpacecraftStatusModel::updateStatusByTimer()
{
    bool updated = false;
    for (int i=0;i<spacecraftList.length();i++)
        if (spacecraftList[i].activeStatus != 2 && QTime().currentTime().msecsSinceStartOfDay() - spacecraftList[i].lastPing.msecsSinceStartOfDay() > 10000)
        {
            updated = true;
            beginResetModel();
            spacecraftList[i].activeStatus = 2;
            spacecraftList[i].communicationStatus = 2;
            logMessage(QTime().currentTime(), 2, {"Потеряна связь с", spacecraftList[i].name});
            endResetModel();
        }
        else if (spacecraftList[i].activeStatus == 2 && QTime().currentTime().msecsSinceStartOfDay() - spacecraftList[i].lastPing.msecsSinceStartOfDay() <= 10000)
        {
            updated = true;
            beginResetModel();
            spacecraftList[i].activeStatus = 0;
            logMessage(QTime().currentTime(), 1, {"Восстановлена связь с", spacecraftList[i].name});
            endResetModel();
        }
    if (updated) emit spacecraftStatusChanged();
}


// =================================================================================================================================================================================================================
// ========================================================================================== GETTER / CHECKER =====================================================================================================
// =================================================================================================================================================================================================================

QVector<SpacecraftStatusData> *SpacecraftStatusModel::getSpacecraftList()
{
    return &spacecraftList;
}


bool SpacecraftStatusModel::spacecraftInTable(unsigned int spacecraftId)
{
    for(int i=0;i<spacecraftList.length();i++)
    {
        if (spacecraftList[i].spacecraftId == spacecraftId)
            return true;
    }
    return false;
}
// =================================================================================================================================================================================================================
// ================================================================================================ LOGGER =========================================================================================================
// =================================================================================================================================================================================================================


void SpacecraftStatusModel::logMessage(QTime time, int logType, QVector<QString> logParts)
{
    QString log;
    for (int i=0;i<logParts.length();i++)
        log = log + " " + logParts[i];
    logerWidget->addLog(time, logType, log);
}
