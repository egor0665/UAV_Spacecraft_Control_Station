#include "settingsmenulistwidget.h"

SettingsMenuListWidget::SettingsMenuListWidget(QWidget *parent) : QListView(parent)
{
    this->setMaximumWidth(200);
    this->setFrameShape(QFrame::NoFrame);
    this->setModel(&model);

    connect(this,&SettingsMenuListWidget::clicked, this, &SettingsMenuListWidget::handleItemClicked);
}

SettingsMenuListWidget::~SettingsMenuListWidget()
{
}

void SettingsMenuListWidget::handleItemClicked(const QModelIndex index)
{
    model.setCurrentIndex(index.row());
    emit settingsMenuIndexChanged(index.row());
}

void SettingsMenuListWidget::setSleep(bool sleep)
{
    this->sleep = sleep;
}
