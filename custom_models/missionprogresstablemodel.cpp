#include "missionprogresstablemodel.h"

#include <QDebug>

const QVector<PlanItem> &MissionProgressTableModel::getMissionPlan() const
{
    return missionPlan;
}

MissionProgressTableModel::MissionProgressTableModel()
{
    missionItemTimer.setInterval(1000);
    connect(&missionItemTimer,&QTimer::timeout,this,&MissionProgressTableModel::updateMissionItemTime);
}


int MissionProgressTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return missionPlan.length();
}

int MissionProgressTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant MissionProgressTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch(role){
    case Qt::DisplayRole: //0	The key data to be rendered in the form of text. (QString)
        switch(index.column()){
        case 0:
            return availableCommands[missionPlan[index.row()].command];
            break;
        case 1:
            return missionPlan[index.row()].executeTime.toString("mm:ss");
            break;
        case 2:
            return missionTableItemResults[missionPlan[index.row()].result];
            break;
        default:
            return QVariant();
        }

    case Qt:: DecorationRole: //1	The data to be rendered as a decoration in the form of an icon. (QColor, QIcon or QPixmap)
        return QVariant();
    case Qt::EditRole: //2 The data in a form suitable for editing in an editor. (QString)
        return QVariant();
    case Qt::ToolTipRole: //3	The data displayed in the item's tooltip. (QString)
        switch(index.column()){
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
        return QVariant();
    case Qt::BackgroundRole: //8	The background brush used for items rendered with the default delegate. (QBrush)
//            return QBrush(QColor("#2d3238"));
        return QVariant();
    case Qt::ForegroundRole: //9	The foreground brush (text color, typically) used for items rendered with the default delegate. (QBrush)
        if (missionPlan[index.row()].result == RESULT_SUCCESS)
            return QBrush(QColor(0,200,0));
        return QVariant();//QBrush(QColor("#E1E2E2"));;
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

bool MissionProgressTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        missionPlan.replace(index.row(),qvariant_cast<PlanItem>(value));
        return true;
    }
    return false;
}

QVariant MissionProgressTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(role){
    case Qt::DisplayRole:{
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return "Команда";
            case 1:
                return "Время вып.";
            case 2:
                return "Результат";
            default:
                return QVariant();
            } //#2d3238
        }
        else
            return QVariant();
    }
    case Qt::BackgroundRole:
        return QVariant();//QBrush(QColor("#2d3238"));
    default:
        return QVariant();
    }

}

void MissionProgressTableModel::setNewPlan(QVector<MissionPlanItem> newPlan)
{
    qDebug()<<"imin";
    beginResetModel();
    QVector<PlanItem> plan = {};
    for (int i = 0;i<newPlan.length();i++)
    {
        PlanItem curPlanItem(newPlan[i].missionItemType);
        plan.append(curPlanItem);
    }
    missionPlan = plan;
    endResetModel();
}
void MissionProgressTableModel::updateMissionProgress(mavlink_mission_item_reached_t missionItemReached)
{
    if (missionItemReached.seq-1 <= missionPlan.length()-1)
    {
        beginResetModel();
        missionPlan[missionItemReached.seq-1].result = RESULT_SUCCESS;
        endResetModel();
        if (missionItemReached.seq-1 < missionPlan.length()-1)
            setNewActivePlanItem(missionItemReached.seq);
    }
}

void MissionProgressTableModel::setNewActivePlanItem(int newItemIndex)
{
    currentMissionItemIndex = newItemIndex;
}

void MissionProgressTableModel::updateMissionItemTime()
{
    beginResetModel();
    missionPlan[currentMissionItemIndex].executeTime = missionPlan[currentMissionItemIndex].executeTime.addSecs(1);
    endResetModel();
}
void MissionProgressTableModel::startTimeCount()
{
    missionItemTimer.start();
}
void MissionProgressTableModel::stopTimeCount()
{
    missionItemTimer.stop();
}
