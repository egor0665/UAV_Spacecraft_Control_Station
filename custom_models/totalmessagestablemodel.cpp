#include "totalmessagestablemodel.h"

#include <QBrush>
#include <QDebug>
#include <QFont>
#include <QFont>
#include <QVector>
#include <structs.h>

TotalMessagesTableModel::TotalMessagesTableModel(QObject *parent)
    :QAbstractTableModel(parent)
{
    for(auto i : AVAILABLE_MESSAGES.toStdMap())
    {
        messagesData.append(MessageInfo(i.first,i.second,0,QTime().fromMSecsSinceStartOfDay(0)));
    }
    updateViewTimer = new QTimer(this);
    connect(updateViewTimer, &QTimer::timeout, this, &TotalMessagesTableModel::updateModel);
    updateViewTimer->start(1000);
}

TotalMessagesTableModel::~TotalMessagesTableModel()
{
    delete(updateViewTimer);
}

void TotalMessagesTableModel::updateModel()
{
    beginResetModel();
    QVector<MessageInfo> tmpVector;
    QVector<bool> usedValues;
    for (int i=0;i<messagesData.length();i++)
        usedValues.append(false);
    for (int i=0;i<messagesData.length();i++)
        if (QTime().currentTime().msecsSinceStartOfDay() - messagesData[i].lastMessage.msecsSinceStartOfDay() <= 1000)
        {
            tmpVector.append(messagesData[i]);
            usedValues[i]=true;
        }
    for (int i=0;i<messagesData.length();i++)
        if (usedValues[i]==false)
            tmpVector.append(messagesData[i]);
    messagesData = tmpVector;
    emit dataChanged(index(0,0),index(messagesData.length(),2));
    endResetModel();
}

void TotalMessagesTableModel::setSleep(bool sleep)
{
    this->sleep = sleep;
}

// =================================================================================================================================================================================================================
// ========================================================================= DEFAULT MODEL OVERRIDED FUNCTIONS =====================================================================================================
// =================================================================================================================================================================================================================


int TotalMessagesTableModel::rowCount(const QModelIndex &parent) const
{
    return messagesData.length();
}

int TotalMessagesTableModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant TotalMessagesTableModel::data(const QModelIndex &index, int role) const
{
    if(!sleep)
    {
        if (!index.isValid())
            return QVariant();
        //    if (messagesData[index.row()].messagesTotal==0)
        //        return QVariant();
        //    else
        //    {
        switch(role){
        case Qt::DisplayRole: //0	The key data to be rendered in the form of text. (QString)
            switch(index.column()){
            case 0:
                return messagesData[index.row()].messageName;
                break;
            case 1:
                return messagesData[index.row()].messagesTotal;
                break;
            case 2:
                return messagesData[index.row()].lastMessage;
                break;
            default:
                return QVariant();
            }

        case Qt:: DecorationRole: //1	The data to be rendered as a decoration in the form of an icon. (QColor, QIcon or QPixmap)
            switch(index.column()){
            //        case 0:
            //            return QVariant();
            //        case 1:
            //            return statusCircles[spacecraftList[index.row()].activeStatus];
            //            break;
            //        case 2:
            //            return statusCircles[spacecraftList[index.row()].communicationStatus];
            //            break;
            //        case 3:
            //            return QVariant();
            //            break;
            //        case 4:
            //            return QVariant();
            //            break;
            default:
                return QVariant();
            }

        case Qt::EditRole: //2 The data in a form suitable for editing in an editor. (QString)
            return QVariant();
        case Qt::ToolTipRole: //3	The data displayed in the item's tooltip. (QString)
            switch(index.column()){
            //        case 0:
            //            return "Название КА";
            //        case 1:
            //            switch(spacecraftList[index.row()].activeStatus){
            //            case 0:
            //                return "КА подключен";
            //            case 2:
            //                return "КА не подключен";
            //            default:
            //                return "Некорректное состояние";
            //            }
            //        case 2:
            //            switch(spacecraftList[index.row()].communicationStatus){
            //            case 0:
            //                return "Системы функционируют корректно";
            //            case 1:
            //                return "Подсистемы КА отключены";
            //            case 2:
            //                return "КА не подключен";
            //            default:
            //                return "Некорректное состояние";
            //            }
            //        case 3:
            //            return "Примерное оставшееся время работы КА";
            //            break;
            //        case 4:
            //            return "Управляющее устройство";
            //            break;
            default:
                return QVariant();
            }
        case Qt::StatusTipRole: //4	The data displayed in the status bar. (QString)
            return "fasfasfa";
        case Qt::WhatsThisRole: //5	The data displayed for the item in "What's This?" mode. (QString)
            return QVariant();
        case Qt::FontRole: //6	The font used for items rendered with the default delegate. (QFont)
            return QFont("MS Shell Dlg 2", 8);
        case Qt::TextAlignmentRole: //7	The alignment of the text for items rendered with the default delegate. (Qt::Alignment)
            switch(index.column()){
            //        case 1:
            //            return int(Qt::AlignRight | Qt::AlignVCenter);
            //            break;
            //        case 2:
            //            return int(Qt::AlignRight | Qt::AlignVCenter);
            //            break;
            default:
                return QVariant();
            }
        case Qt::BackgroundRole: //8	The background brush used for items rendered with the default delegate. (QBrush)
                return QBrush(QColor("#2d3238"));

            return QVariant();
        case Qt::ForegroundRole: //9	The foreground brush (text color, typically) used for items rendered with the default delegate. (QBrush)
            if (QTime().currentTime().msecsSinceStartOfDay() - messagesData[index.row()].lastMessage.msecsSinceStartOfDay() <= 1000)
                return QBrush(QColor(0,200,0));
            return QBrush(QColor("#E1E2E2"));;
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
        //    }
    }
    else
        return QVariant();

}

bool TotalMessagesTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!sleep)
    {
        if (role == Qt::EditRole) {
            messagesData.replace(index.row(),qvariant_cast<MessageInfo>(value));
            return true;
        }
    }
    else
        return false;
}

Qt::ItemFlags TotalMessagesTableModel::flags(const QModelIndex) const
{
    return Qt::NoItemFlags;
}

QVariant TotalMessagesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(role){
    case Qt::DisplayRole:{
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return "Сообщение";
            case 1:
                return "Кол-во";
            case 2:
                return "Последнее";
            default:
                return QVariant();
            } //#2d3238
        }
        else
            return QVariant();
    }
    case Qt::BackgroundRole:
        return QBrush(QColor("#2d3238"));
    default:
        return QVariant();
    }

}

void TotalMessagesTableModel::newMessageReceived(int messageId)
{
    for (int i=0;i<messagesData.length();i++)
    {

        if (messagesData[i].messageCode == messageId)
        {
            messagesData[i].lastMessage = QTime().currentTime();
            messagesData[i].messagesTotal+=1;
            return;
        }
    }
}

// =================================================================================================================================================================================================================
// ============================================================================= CHANGE SPACECRAFT STATUS DATA =====================================================================================================
// =================================================================================================================================================================================================================

//void TotalMessagesTableModel::appendSpaceCraftStatusData(SpacecraftStatusData dataItem)
//{
//    beginResetModel();
//    spacecraftList.append(dataItem);
//    endResetModel();
//    emit spacecraftStatusChanged();
//}

//void SpacecraftStatusModel::updateSpaceCraftStatusData(SpacecraftStatusData dataItem)
//{
//    beginResetModel();
//    unsigned int spacecraftId = dataItem.spacecraftId;
//    int index=-1;
//    for(int i=0;i<spacecraftList.length();i++)
//    {
//        if (spacecraftList[i].spacecraftId == spacecraftId)
//        {
//            index = i;
//            logMessage(QTime().currentTime(), 0, {"Обновлены данные о", spacecraftList[index].name});
//        }
//    }
//    spacecraftList[index] = dataItem;

//    endResetModel();
//    emit spacecraftStatusChanged();
//}

// =================================================================================================================================================================================================================
// ======================================================================== CONNECTION STATUS BY TIMER HANDLER =====================================================================================================
// =================================================================================================================================================================================================================


//void SpacecraftStatusModel::updateSpaceCraftLastPing(unsigned int spacecraftId, QTime time)
//{
//    for (int i=0;i<spacecraftList.length();i++)
//    {
//        if (spacecraftList[i].spacecraftId == spacecraftId)
//        {
//            spacecraftList[i].lastPing = time;
//            emit spacecraftStatusChanged();
//        }
//    }
//}

//void SpacecraftStatusModel::updateStatusByTimer()
//{
//    bool updated = false;
//    for (int i=0;i<spacecraftList.length();i++)
//        if (spacecraftList[i].activeStatus != 2 && QTime().currentTime().msecsSinceStartOfDay() - spacecraftList[i].lastPing.msecsSinceStartOfDay() > 10000)
//        {
//            updated = true;
//            beginResetModel();
//            spacecraftList[i].activeStatus = 2;
//            spacecraftList[i].communicationStatus = 2;
//            logMessage(QTime().currentTime(), 2, {"Потеряна связь с", spacecraftList[i].name});
//            endResetModel();
//        }
//        else if (spacecraftList[i].activeStatus == 2 && QTime().currentTime().msecsSinceStartOfDay() - spacecraftList[i].lastPing.msecsSinceStartOfDay() <= 10000)
//        {
//            updated = true;
//            beginResetModel();
//            spacecraftList[i].activeStatus = 0;
//            logMessage(QTime().currentTime(), 1, {"Восстановлена связь с", spacecraftList[i].name});
//            endResetModel();
//        }
//    if (updated) emit spacecraftStatusChanged();
//}


// =================================================================================================================================================================================================================
// ========================================================================================== GETTER / CHECKER =====================================================================================================
// =================================================================================================================================================================================================================

//QVector<SpacecraftStatusData> *SpacecraftStatusModel::getSpacecraftList()
//{
//    return &spacecraftList;
//}


//bool SpacecraftStatusModel::spacecraftInTable(unsigned int spacecraftId)
//{
//    for(int i=0;i<spacecraftList.length();i++)
//    {
//        if (spacecraftList[i].spacecraftId == spacecraftId)
//            return true;
//    }
//    return false;
//}
// =================================================================================================================================================================================================================
// ================================================================================================ LOGGER =========================================================================================================
// =================================================================================================================================================================================================================


//void TotalMessagesTableModel::logMessage(QTime time, int logType, QVector<QString> logParts)
//{
//    QString log;
//    for (int i=0;i<logParts.length();i++)
//        log = log + " " + logParts[i];
//    logerWidget->addLog(time, logType, log);
//}
