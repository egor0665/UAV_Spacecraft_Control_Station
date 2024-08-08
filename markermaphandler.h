#ifndef MARKERMAPHANDLER_H
#define MARKERMAPHANDLER_H

#include <QObject>

#include <custom_widgets/Main_tab_widgets/Vehicle_display_widgets/vehiclepositiondisplaywidget.h>

//#include <custom_widgets/Main_tab_widgets/Vehicle_display_widgets/vehiclepositiondisplaywidget.h>


float getDistance(float x1, float y1, float z1, float x2, float y2, float z2);
float roundToDigit(float value, int digitNum);

class MarkerMapHandler : public QObject
{
    Q_OBJECT
public:
    explicit MarkerMapHandler(QObject *parent = nullptr);
    QVector<MissionPlanItem> formMarkerRoute(float vehicleX, float vehicleY, float vehicleZ, int endMarkerId, float distanceToMarker);
    void formMarkerMap();

signals:
    void markerMapHandlerVehicleDisplayWidgetSetMarkerMap(QVector<QVector<char>> markerMap, QVector<MarkerInfo> markerInfoVector);
protected:

    QVector<QVector<int>> markerPathMatrix;

    QVector<MarkerDirections> markerDirectionsVector = {};
    QVector<QVector<char>> markerCharMap = {};
    QVector<QVector<float>> adjacencyMatrix = {};
    QVector<MarkerInfo> markerInfoVector = {};


    void markerMapFloydWarshall();
    QVector<QVector<float>> formMarkerAdjacencyMatrix();
    int findClosestToVehicleMarker(float vehicleX, float vehicleY, float vehicleZ);
    MarkerInfo findMarkerById(int id);

    AttitudeInfo findVehicleAttitude(AttitudeInfo markerAttitude, float distanceToMarker);
    int parseMarkerMapTextFile(QString markersText);
    void formMarkerDirectionMap(int markerCount);
    void parseLineIntoMarkerInfoVector(QString line);
    void parsePathIntoMarkerDirectionsVector(QString line);
};

#endif // MARKERMAPHANDLER_H
