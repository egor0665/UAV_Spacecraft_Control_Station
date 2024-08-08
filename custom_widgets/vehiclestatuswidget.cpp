//#include "vehiclestatuswidget.h"

//#include <structs.h>
//#include <QGridLayout>

//VehicleStatusWidget::VehicleStatusWidget()
//{
//    xPos = 0, yPos = 0, zPos = 0;
//    armed = false;
//    vehicleMode = "AUTO";
//    systemStatus = "UNINT";


//    xPosLabel = new QLabel("0");
//    initMainLabel(xPosLabel, 40,10,"rgb(128, 0, 0)");
//    yPosLabel = new QLabel("0");
//    initMainLabel(yPosLabel, 40,10,"rgb(0, 128, 0)");
//    zPosLabel = new QLabel("0");
//    initMainLabel(zPosLabel, 40,10,"rgb(0, 0, 128)");

//    armedLabel = new QLabel("Выключен");
//    initMainLabel(armedLabel, 12,1,"rgb(0, 0, 0)");
//    vehicleModeLabel = new QLabel("AUTO");
//    initMainLabel(vehicleModeLabel, 12,1,"rgb(0, 0, 0)");
//    statusLabel = new QLabel("UNINT");
//    initMainLabel(statusLabel, 12,1,"rgb(0, 0, 0)");

//    QGridLayout *posLayout = new QGridLayout;
//    QLabel *xPosTitleLabel = new QLabel("Лок. X");
//    initMainLabel(xPosTitleLabel, 20,10,"rgb(0, 0, 0)");
//    QLabel *yPosTitleLabel = new QLabel("Лок. Y");
//    initMainLabel(yPosTitleLabel, 20,10,"rgb(0, 0, 0)");
//    QLabel *zPosTitleLabel = new QLabel("Лок. Z");
//    initMainLabel(zPosTitleLabel, 20,10,"rgb(0, 0, 0)");

//    posLayout->addWidget(xPosTitleLabel,0,0);
//    posLayout->addWidget(xPosLabel,1,0);

//    posLayout->addWidget(yPosTitleLabel,0,1);
//    posLayout->addWidget(yPosLabel,1,1);

//    posLayout->addWidget(zPosTitleLabel,0,2);
//    posLayout->addWidget(zPosLabel,1,2);

//    QGridLayout *mainLayout = new QGridLayout();

//    QLabel *armedTitleLabel = new QLabel("Моторы");
//    initMainLabel(armedTitleLabel, 12,1,"rgb(0, 0, 0)");

//    QLabel *vehicleModeTitleLabel = new QLabel("Режим");
//    initMainLabel(vehicleModeTitleLabel, 12,1,"rgb(0, 0, 0)");

//    QLabel *statusTitleLabel = new QLabel("Статус");
//    initMainLabel(statusTitleLabel, 12,1,"rgb(0, 0, 0)");

//    mainLayout->addLayout(posLayout,0,0,1,2);

//    mainLayout->addWidget(vehicleModeTitleLabel,1,0);
//    mainLayout->addWidget(vehicleModeLabel,1,1);

//    mainLayout->addWidget(statusTitleLabel,2,0);
//    mainLayout->addWidget(statusLabel,2,1);

//    mainLayout->addWidget(armedTitleLabel,3,0);
//    mainLayout->addWidget(armedLabel,3,1);

//    QSpacerItem * spacer = new QSpacerItem(1,1,QSizePolicy::Minimum, QSizePolicy::Expanding);

//    mainLayout->addItem(spacer,4,0);
//    this->setLayout(mainLayout);
//}

//VehicleStatusWidget::~VehicleStatusWidget()
//{
//    delete(xPosLabel);
//    delete(yPosLabel);
//    delete(zPosLabel);
//    delete(armedLabel);
//    delete(vehicleModeLabel);
//    delete(statusLabel);
//}

//void VehicleStatusWidget::updateHeartBeat(mavlink_heartbeat_t message)
//{
//    vehicleMode = CUSTOM_MODES[message.custom_mode];
//    systemStatus = SYSTEM_STATUSES[message.system_status];

//    armed = message.base_mode >= 128;
//    if(!sleep)
//        displayData();
//}

//void VehicleStatusWidget::updateLocalPosition(float x, float y, float z)
//{
//    xPos = x;
//    yPos = y;
//    zPos = z;
////    displayData()
//}

//void VehicleStatusWidget::displayData()
//{
//    xPosLabel->setText(QString::number(xPos,'f',2));
//    yPosLabel->setText(QString::number(yPos,'f',2));
//    zPosLabel->setText(QString::number(zPos,'f',2));

//    if (armed)
//        armedLabel->setText("Включен");
//    else
//        armedLabel->setText("Выключен");

//    vehicleModeLabel->setText(vehicleMode);
//    statusLabel->setText(systemStatus);
//}
