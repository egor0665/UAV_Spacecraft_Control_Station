#ifndef CONNECTIONWIDGET_H
#define CONNECTIONWIDGET_H
#include "custom_widgets/tabmodule.h"
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QGridLayout>
#include <connection/connectionhandler.h>

class ConnectionWidget: public QWidget, public tabModule
{
    Q_OBJECT
    QComboBox baudRateCB, connectionTypeCB;
    QSpinBox portNumSB;
    QLineEdit ipAddressLE;
    QPushButton connectButton;
//    QVector<QPixmap> statusCircles;
    QComboBox vehicleCB;

    QGridLayout mainLayout;

    QLabel ipAddressLETitleLBL;
    QLabel vehicleCBTitleLBL;
    QLabel connectionTypeCBTitleLBL;
    QLabel baudRateCBTitleLBL;
    QLabel portNumSBTitleLBL;

    bool disconnectOnButtonPress=false;
public:
    ConnectionWidget(QWidget *parent = nullptr);
    ~ConnectionWidget();
    void onConnectStatusResult(bool connected);
    void onDisconnectStatusResult(int vehicleId, bool connected);
    void addNewVehicleSetCurrent(int newVehicleId, PortEnum connectionType, QString ipAddress, int portNum);
protected slots:
    void on_connectionTypeCB_current_index_changed(int index);
    void on_connectionButton_pressed();
    void on_vehicleCB_currentIndexChanged(int index);
signals:
    void connectOnButtonPressed(QString ipAddress, PortEnum connectionType, int baudRate, int portNum);
    void disconnectOnButtonPressed(int vehicleId);
    void currentVehicleChanged(int vehicleId);
};

#endif // CONNECTIONWIDGET_H
