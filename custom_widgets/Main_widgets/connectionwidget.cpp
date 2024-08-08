#include "connectionwidget.h"

#include <QGridLayout>
#include <QVariant>

ConnectionWidget::ConnectionWidget(QWidget *parent) : QWidget(parent)
{
    this->setMaximumWidth(200);
    this->setMaximumHeight(160);

//    statusCircles.append(QPixmap("C:/Qt/5.15.2/mingw81_32/GroundControlStation/resources/blueStatusCircle.png").scaled(15,15));
//    statusCircles.append(QPixmap("C:/Qt/5.15.2/mingw81_32/GroundControlStation/resources/orangeStatusCircle.png").scaled(15,15));
//    statusCircles.append(QPixmap("C:/Qt/5.15.2/mingw81_32/GroundControlStation/resources/greenStatusCircle.png").scaled(15,15));

    connectionTypeCB.addItem("UDP", int(PortEnum::UDPPort));
    connectionTypeCB.addItem("Socket", int(PortEnum::SocketPort));
    connectionTypeCB.addItem("Serial", int(PortEnum::SerialPort));
    connectionTypeCB.addItem("TCP", int(PortEnum::TCPPort));
    connect(&connectionTypeCB, SIGNAL(currentIndexChanged(int)), this, SLOT(on_connectionTypeCB_current_index_changed(int)));

    baudRateCB.setMinimumWidth(100);
    baudRateCB.addItem("9600", 9600);
    baudRateCB.addItem("19200", 19200);
    baudRateCB.addItem("38400", 38400);
    baudRateCB.addItem("57600", 57600);
    baudRateCB.addItem("115200", 115200);
    baudRateCB.setEnabled(false);

    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");
    QRegExpValidator ipValidator(ipRegex);
    ipAddressLE.setValidator(&ipValidator);
    ipAddressLE.setMaximumWidth(100);
    ipAddressLE.setText("127.0.0.1");

    vehicleCB.addItem("Новое подключение",-1);

    portNumSB.setMinimumWidth(100);
    portNumSB.setRange(0,65535);

    portNumSB.setEnabled(true);
    portNumSB.setValue(14551);

    connectButton.setText("Подключиться");
    connectButton.setMinimumWidth(200);
    connectButton.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    connectButton.setMaximumWidth(200);
    connect(&connectButton, &QPushButton::pressed, this, &ConnectionWidget::on_connectionButton_pressed);

    ipAddressLETitleLBL.setText("IP");
    vehicleCBTitleLBL.setText("Подключение");
    connectionTypeCBTitleLBL.setText("Тип подкл.");
    baudRateCBTitleLBL.setText("Скор. Перед.");
    portNumSBTitleLBL.setText("Порт / COM");

    mainLayout.addWidget(&vehicleCBTitleLBL,0,1,1,1);
    mainLayout.addWidget(&vehicleCB,0,2,1,1);
    mainLayout.addWidget(&connectionTypeCBTitleLBL,1,1,1,1);
    mainLayout.addWidget(&connectionTypeCB,1,2,1,1);
    mainLayout.addWidget(&ipAddressLETitleLBL,2,1,1,1);
    mainLayout.addWidget(&ipAddressLE,2,2,1,1);
    mainLayout.addWidget(&baudRateCBTitleLBL,3,1,1,1);
    mainLayout.addWidget(&baudRateCB,3,2,1,1);
    mainLayout.addWidget(&portNumSBTitleLBL,4,1,1,1);
    mainLayout.addWidget(&portNumSB,4,2,1,1);
    mainLayout.addWidget(&connectButton,5,1,1,2, Qt::AlignHCenter | Qt::AlignVCenter);

    mainLayout.setMargin(0);
    this->setLayout(&mainLayout);

    connect(&vehicleCB, SIGNAL(currentIndexChanged(int)), this, SLOT(on_vehicleCB_currentIndexChanged(int)));
}

ConnectionWidget::~ConnectionWidget()
{
}

void ConnectionWidget::on_vehicleCB_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ipAddressLE.setEnabled(true);
        connectionTypeCB.setEnabled(true);
        baudRateCB.setEnabled(true);
        portNumSB.setEnabled(true);
        connectButton.setText("Подключиться");
        disconnectOnButtonPress = false;
    }
    else
    {
        ipAddressLE.setEnabled(false);
        connectionTypeCB.setEnabled(false);
        baudRateCB.setEnabled(false);
        portNumSB.setEnabled(false);
        connectButton.setText("Отключиться");
        disconnectOnButtonPress = true;
    }
    emit currentVehicleChanged(vehicleCB.itemData(index).toInt());

}

void ConnectionWidget::on_connectionTypeCB_current_index_changed(int index)
{
    switch(connectionTypeCB.itemData(index).toInt())
    {
    case(int(PortEnum::UDPPort)):
    {
        ipAddressLE.setEnabled(true);
        ipAddressLE.setText("127.0.0.1");
        baudRateCB.setEnabled(false);
        portNumSB.setEnabled(true);
        portNumSB.setValue(14550);
        break;
    }
    case(int(PortEnum::SocketPort)):
    {
//        ipAddressLE.setText("127.0.0.1");
        ipAddressLE.setEnabled(false);
        baudRateCB.setEnabled(false);
        portNumSB.setEnabled(true);
        portNumSB.setValue(4400);
        break;
    }
    case(int(PortEnum::SerialPort)):
    {
        ipAddressLE.setEnabled(false);
        baudRateCB.setEnabled(true);
        portNumSB.setEnabled(true);
        portNumSB.setValue(1);
        break;
    }
    case(int(PortEnum::TCPPort)):
    {
        ipAddressLE.setEnabled(true);
        baudRateCB.setEnabled(false);
        portNumSB.setEnabled(true);
        portNumSB.setValue(5762);
        ipAddressLE.setText("127.0.0.1");
        break;
    }
    }

}

void ConnectionWidget::on_connectionButton_pressed()
{

    if (disconnectOnButtonPress)
    {
        qDebug()<<QString::number(vehicleCB.itemData(vehicleCB.currentIndex()).toInt());
        emit disconnectOnButtonPressed(vehicleCB.itemData(vehicleCB.currentIndex()).toInt());
    }
    else
        emit connectOnButtonPressed(ipAddressLE.text(), PortEnum(connectionTypeCB.currentData().toInt()), baudRateCB.currentData().toInt(), portNumSB.value());
}

void ConnectionWidget::onConnectStatusResult(bool result)
{
    if (result)
    {
        ipAddressLE.setEnabled(false);
        connectionTypeCB.setEnabled(false);
        baudRateCB.setEnabled(false);
        portNumSB.setEnabled(false);
        connectButton.setText("Отключиться");
        disconnectOnButtonPress = true;
    }
    else
    {
    }
}
void ConnectionWidget::onDisconnectStatusResult(int vehicleId, bool result)
{
    if (result)
    {
        ipAddressLE.setEnabled(true);
        connectionTypeCB.setEnabled(true);
        baudRateCB.setEnabled(true);
        portNumSB.setEnabled(true);

        connectButton.setText("Подключиться");
        disconnectOnButtonPress = false;

        for (int i=0;i<vehicleCB.count();i++)
            if (vehicleCB.itemData(i).toInt()==vehicleId)
                vehicleCB.removeItem(i);
    }
    else
    {
    }
}

void ConnectionWidget::addNewVehicleSetCurrent(int newVehicleId, PortEnum connectionType, QString ipAddress, int portNum)
{
    QString vehicleName;
    switch(connectionType)
    {
    case PortEnum::NoPort:
        break;
    case PortEnum::SerialPort:
    {
        vehicleName = "Serial " + QString::number(portNum);
        break;
    }
    case PortEnum::SocketPort:
    {
        vehicleName = "Socket" + QString::number(portNum);
        break;
    }
    case PortEnum::TCPPort:
    {
        vehicleName = "TCP " + ipAddress + ":" + QString::number(portNum);
        break;
    }
    case PortEnum::UDPPort:
    {
        vehicleName = "UDP " + ipAddress + ":" + QString::number(portNum);
        break;
    }
    }
    vehicleCB.addItem(vehicleName,newVehicleId);
    vehicleCB.setCurrentIndex(vehicleCB.count()-1);
}
