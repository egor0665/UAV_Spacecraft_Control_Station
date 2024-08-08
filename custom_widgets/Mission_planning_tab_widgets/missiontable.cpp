#include "missiontable.h"

QVector<MissionPlanItem> MissionTable::getMissionPlanItems()
{
    QVector<MissionPlanItem> MissionPlanItems;
    for (int i=0;i<missionPlanItemWidgets.length();i++)
        MissionPlanItems.append(missionPlanItemWidgets[i]->planItem);
    return MissionPlanItems;
}

void MissionTable::updatePlan(QVector<MissionPlanItem> newPlan)
{
    resetTable();
    for (int i=0;i<newPlan.length();i++)
    {
        MissionPlanItemWidget *newMissionPlanItem = new MissionPlanItemWidget(newPlan[i].itemNum,
                                                 newPlan[i].missionItemType,
                                                 newPlan[i].frameType,
                                                 newPlan[i].param1,
                                                 newPlan[i].param2,
                                                 newPlan[i].param3,
                                                 newPlan[i].param4,
                                                 newPlan[i].param5X,
                                                 newPlan[i].param6Y,
                                                 newPlan[i].param7Z, this);

        missionPlanItemWidgets.append(newMissionPlanItem);
        connect(newMissionPlanItem, &MissionPlanItemWidget::itemDeleteButtonClicked,this,&MissionTable::handleItemDeleteButtonClicked);
        connect(newMissionPlanItem, &MissionPlanItemWidget::itemMoveUpwardsButtonClicked,this,&MissionTable::handleItemMoveUpwardsButtonClicked);
        connect(newMissionPlanItem, &MissionPlanItemWidget::itemMoveDownwardsButtonClicked,this,&MissionTable::handleItemMoveDownwardsButtonClicked);
        connect(newMissionPlanItem, &MissionPlanItemWidget::missionItemUpdateVehicleDisplayWidgetMissionPlan, this, &MissionTable::handleUpdateVehicleDisplayWidgetMissionPlan);
        int newRow = this->rowCount();
        this->setRowCount(newRow+1);
        this->setVerticalHeaderItem(newRow, new QTableWidgetItem(QString::number(newRow)));
        displayRow(newRow, newMissionPlanItem);
        missionItemCount++;
    }
    emit updateVehicleDisplayWidgetMissionPlan(formMissionPlanItemVector());
}

MissionTable::MissionTable(QWidget *parent) : QTableWidget(parent)
{
    resetTable();
//    connect(this,&MissionTable::cellActivated, this, &MissionTable::handleItemClicked); //(QTableWidgetItem *item)
connect(this,&MissionTable::currentCellChanged, this, &MissionTable::handleItemClicked);
    //currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
}

void MissionTable::handleItemClicked(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    Q_UNUSED( currentColumn) Q_UNUSED(previousRow) Q_UNUSED(previousColumn)

    if (currentRow!=-1)
    {
        QStringList headers = {"Команда"};
        headers.append(missionPlanItemWidgets[currentRow]->getParamInfo());
        headers.append("Система");
        headers.append("Удалить");
        headers.append("Вверх");
        headers.append("Вниз");
        headers.append("Инфо1");
        headers.append("Инфо2");
        headers.append("Инфо3");
        headers.append("Инфо4");

        this->setHorizontalHeaderLabels(headers);
    }
}
void MissionTable::resetTable()
{
    missionItemCount=0;
    missionPlanItemWidgets = {};
    this->clear();
    this->setRowCount(0);
    this->setColumnCount(MISSION_TABLE_COLUMN_COUNT);
    this->setHorizontalHeaderLabels(MISSION_TABLE_HORIZONTAL_HEADERS);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    //        this->resizeColumnsToContents();
    this->setWordWrap(true);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    emit updateVehicleDisplayWidgetMissionPlan(formMissionPlanItemVector());
}

QString MissionTable::formTextMissionPlan()
{
    int autocontinue = 1;

    QString missionPlan = "GCS WPL 1\n";
    for (int i=0;i<missionPlanItemWidgets.length();i++)
    {
        QString missionTextItem = "";
        missionTextItem += QString::number(i) + " ";
        if (i==0)
            missionTextItem += "1 ";
        else
            missionTextItem += "0 ";
        missionTextItem += QString::number(missionPlanItemWidgets[i]->planItem.frameType) + " ";
        missionTextItem += QString::number(missionPlanItemWidgets[i]->planItem.missionItemType) + " ";
        missionTextItem += QString::number(missionPlanItemWidgets[i]->planItem.param1) + " ";
        missionTextItem += QString::number(missionPlanItemWidgets[i]->planItem.param2) + " ";
        missionTextItem += QString::number(missionPlanItemWidgets[i]->planItem.param3) + " ";
        missionTextItem += QString::number(missionPlanItemWidgets[i]->planItem.param4) + " ";
        missionTextItem += QString::number(missionPlanItemWidgets[i]->planItem.param5X) + " ";
        missionTextItem += QString::number(missionPlanItemWidgets[i]->planItem.param6Y) + " ";
        missionTextItem += QString::number(missionPlanItemWidgets[i]->planItem.param7Z) + " ";
        missionTextItem += QString::number(autocontinue) + '\n';

        missionPlan += missionTextItem;
    }
    return missionPlan;
}

void MissionTable::parseTextMissionPlan(QString missionTextPlan)
{
    resetTable();
    QStringList missionItems = missionTextPlan.split('\n');

    for (int i=1;i<missionItems.length()-1;i++)
    {
        QStringList itemParams = missionItems[i].split(' ');
        MissionPlanItemWidget *newMissionPlanItem = new MissionPlanItemWidget(i-1,
                                                 itemParams[3].toInt(),
                                                 itemParams[2].toInt(),
                                                 itemParams[4],
                                                 itemParams[5],
                                                 itemParams[6],
                                                 itemParams[7],
                                                 itemParams[8],
                                                 itemParams[9],
                                                 itemParams[10], this);
        missionPlanItemWidgets.append(newMissionPlanItem);
        connect(newMissionPlanItem, &MissionPlanItemWidget::itemDeleteButtonClicked,this,&MissionTable::handleItemDeleteButtonClicked);
        connect(newMissionPlanItem, &MissionPlanItemWidget::itemMoveUpwardsButtonClicked,this,&MissionTable::handleItemMoveUpwardsButtonClicked);
        connect(newMissionPlanItem, &MissionPlanItemWidget::itemMoveDownwardsButtonClicked,this,&MissionTable::handleItemMoveDownwardsButtonClicked);
        connect(newMissionPlanItem, &MissionPlanItemWidget::missionItemUpdateVehicleDisplayWidgetMissionPlan, this, &MissionTable::handleUpdateVehicleDisplayWidgetMissionPlan);
        int newRow = this->rowCount();
        this->setRowCount(newRow+1);
        this->setVerticalHeaderItem(newRow, new QTableWidgetItem(QString::number(newRow)));
        displayRow(newRow, newMissionPlanItem);
        missionItemCount++;
    }

    emit updateVehicleDisplayWidgetMissionPlan(formMissionPlanItemVector());
}

void MissionTable::addNewMissionItem()
{
    MissionPlanItemWidget *newMissionPlanItem = new MissionPlanItemWidget(missionItemCount, this);

    connect(newMissionPlanItem, &MissionPlanItemWidget::itemDeleteButtonClicked,this,&MissionTable::handleItemDeleteButtonClicked);
    connect(newMissionPlanItem, &MissionPlanItemWidget::itemMoveUpwardsButtonClicked,this,&MissionTable::handleItemMoveUpwardsButtonClicked);
    connect(newMissionPlanItem, &MissionPlanItemWidget::itemMoveDownwardsButtonClicked,this,&MissionTable::handleItemMoveDownwardsButtonClicked);
    connect(newMissionPlanItem, &MissionPlanItemWidget::missionItemUpdateVehicleDisplayWidgetMissionPlan, this, &MissionTable::handleUpdateVehicleDisplayWidgetMissionPlan);


    missionPlanItemWidgets.append(newMissionPlanItem);
    missionItemCount++;

    int newRow = this->rowCount();
    this->setRowCount(newRow+1);
    this->setVerticalHeaderItem(newRow, new QTableWidgetItem(QString::number(newRow)));
    displayRow(newRow, newMissionPlanItem);

    emit updateVehicleDisplayWidgetMissionPlan(formMissionPlanItemVector());
}

void MissionTable::handleUpdateVehicleDisplayWidgetMissionPlan()
{
    emit updateVehicleDisplayWidgetMissionPlan(formMissionPlanItemVector());
}

void MissionTable::swapRows(int row1, int row2)
{

    //        qDebug()<<QString::number(row1) + " " + QString::number(row2)<<QString::number(missionPlanItems[row1]->itemNum) + " " + QString::number(missionPlanItems[row2]->itemNum);

    MissionPlanItemWidget *tmpRow2Item = new MissionPlanItemWidget(missionPlanItemWidgets[row2]->planItem.itemNum,
                                                       missionPlanItemWidgets[row1]->planItem.missionItemType,
                                                       missionPlanItemWidgets[row1]->planItem.frameType,
                                                       missionPlanItemWidgets[row1]->param1LE->text(),
                                                       missionPlanItemWidgets[row1]->param2LE->text(),
                                                       missionPlanItemWidgets[row1]->param3LE->text(),
                                                       missionPlanItemWidgets[row1]->param4LE->text(),
                                                       missionPlanItemWidgets[row1]->param5LE->text(),
                                                       missionPlanItemWidgets[row1]->param6LE->text(),
                                                       missionPlanItemWidgets[row1]->param7LE->text(),this);
    connect(tmpRow2Item, &MissionPlanItemWidget::itemDeleteButtonClicked,this,&MissionTable::handleItemDeleteButtonClicked);
    connect(tmpRow2Item, &MissionPlanItemWidget::itemMoveUpwardsButtonClicked,this,&MissionTable::handleItemMoveUpwardsButtonClicked);
    connect(tmpRow2Item, &MissionPlanItemWidget::itemMoveDownwardsButtonClicked,this,&MissionTable::handleItemMoveDownwardsButtonClicked);
    connect(tmpRow2Item, &MissionPlanItemWidget::missionItemUpdateVehicleDisplayWidgetMissionPlan, this, &MissionTable::handleUpdateVehicleDisplayWidgetMissionPlan);
    MissionPlanItemWidget *tmpRow1Item = new MissionPlanItemWidget(missionPlanItemWidgets[row1]->planItem.itemNum,
                                                       missionPlanItemWidgets[row2]->planItem.missionItemType,
                                                       missionPlanItemWidgets[row2]->planItem.frameType,
                                                       missionPlanItemWidgets[row2]->param1LE->text(),
                                                       missionPlanItemWidgets[row2]->param2LE->text(),
                                                       missionPlanItemWidgets[row2]->param3LE->text(),
                                                       missionPlanItemWidgets[row2]->param4LE->text(),
                                                       missionPlanItemWidgets[row2]->param5LE->text(),
                                                       missionPlanItemWidgets[row2]->param6LE->text(),
                                                       missionPlanItemWidgets[row2]->param7LE->text(),this);
    connect(tmpRow1Item, &MissionPlanItemWidget::itemDeleteButtonClicked,this,&MissionTable::handleItemDeleteButtonClicked);
    connect(tmpRow1Item, &MissionPlanItemWidget::itemMoveUpwardsButtonClicked,this,&MissionTable::handleItemMoveUpwardsButtonClicked);
    connect(tmpRow1Item, &MissionPlanItemWidget::itemMoveDownwardsButtonClicked,this,&MissionTable::handleItemMoveDownwardsButtonClicked);
    connect(tmpRow1Item, &MissionPlanItemWidget::missionItemUpdateVehicleDisplayWidgetMissionPlan, this, &MissionTable::handleUpdateVehicleDisplayWidgetMissionPlan);
//    delete(missionPlanItemWidgets[row1]);
    missionPlanItemWidgets.remove(row1);
    missionPlanItemWidgets.insert(row1,tmpRow1Item);
//    delete(missionPlanItemWidgets[row2]);
    missionPlanItemWidgets.remove(row2);
    missionPlanItemWidgets.insert(row2,tmpRow2Item);

    displayRow(row1, tmpRow1Item);
    displayRow(row2, tmpRow2Item);

    emit updateVehicleDisplayWidgetMissionPlan(formMissionPlanItemVector());
}

void MissionTable::displayRow(int row, MissionPlanItemWidget *item)
{
    this->setCellWidget(row,0,item->missionItemTypeCB);
    this->setCellWidget(row,1,item->param1LE);
    this->setCellWidget(row,2,item->param2LE);
    this->setCellWidget(row,3,item->param3LE);
    this->setCellWidget(row,4,item->param4LE);
    this->setCellWidget(row,5,item->param5LE);
    this->setCellWidget(row,6,item->param6LE);
    this->setCellWidget(row,7,item->param7LE);
    this->setCellWidget(row,8,item->frameTypeCB);
    this->setCellWidget(row,9,item->deleteItemButton);
    this->setCellWidget(row,10,item->moveUpwardsButton);
    this->setCellWidget(row,11,item->moveDownwardsButton);
    this->setCellWidget(row,12,item->info1LBL);
    this->setCellWidget(row,13,item->info2LBL);
    this->setCellWidget(row,14,item->info3LBL);
    this->setCellWidget(row,15,item->info4LBL);
}

void MissionTable::updateVerticalHeader()
{
    for (int i=0;i<this->rowCount();i++)
        this->verticalHeaderItem(i)->setText(QString::number(i));
}

void MissionTable::handleItemDeleteButtonClicked(int itemNum)
{
    for (int i=itemNum;i<this->rowCount();i++)
    {
        missionPlanItemWidgets[i]->planItem.itemNum -=1;
        this->verticalHeaderItem(i)->setText(QString::number(i));
    }

    this->removeRow(itemNum);
    missionPlanItemWidgets.remove(itemNum);
    missionItemCount--;
    updateVerticalHeader();

    emit updateVehicleDisplayWidgetMissionPlan(formMissionPlanItemVector());
}

QVector<MissionPlanItem> MissionTable::formMissionPlanItemVector()
{
    QVector<MissionPlanItem> result = {};
    for (int i=0;i<missionPlanItemWidgets.length();i++)
    {
        result.append(missionPlanItemWidgets[i]->planItem);
    }
    return result;
}
void MissionTable::handleItemMoveUpwardsButtonClicked(int itemNum)
{
    if (itemNum>0)
        swapRows(itemNum, itemNum-1);
}

void MissionTable::handleItemMoveDownwardsButtonClicked(int itemNum)
{
    if (itemNum<this->rowCount()-1)
        swapRows(itemNum, itemNum+1);
}
