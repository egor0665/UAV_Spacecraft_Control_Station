#ifndef SETTINGSMENULISTWIDGET_H
#define SETTINGSMENULISTWIDGET_H

#include "custom_widgets/tabmodule.h"

#include <QListWidget>
#include <custom_models/settingsmenulistmodel.h>



class SettingsMenuListWidget: public QListView, public tabModule
{
    Q_OBJECT
    SettingsMenuListModel model;
public:
    SettingsMenuListWidget(QWidget *parent = nullptr);
    ~SettingsMenuListWidget();
    void setSleep(bool sleep);
protected slots:
    void handleItemClicked(const QModelIndex index);
signals:
    void settingsMenuIndexChanged(int index);
};

#endif // SETTINGSMENULISTWIDGET_H
