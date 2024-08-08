#include "markermaphandler.h"

#include <CustomFileManager.h>

#include <custom_widgets/Main_tab_widgets/Vehicle_display_widgets/vehiclepositiondisplaywidget.h>

MarkerMapHandler::MarkerMapHandler(QObject *parent) : QObject(parent)
{

}

const QString markerMapPath = "C:/Qt/5.15.2/mingw81_32/GroundControlStation/marker2.mmap";

void MarkerMapHandler::formMarkerMap()
{
    int markerCount = parseMarkerMapTextFile(markerMapPath);
    formMarkerDirectionMap(markerCount);
    markerMapFloydWarshall();
    emit markerMapHandlerVehicleDisplayWidgetSetMarkerMap(markerCharMap, markerInfoVector);
}

int MarkerMapHandler::parseMarkerMapTextFile(QString filePath)
{
    CustomFileManager cfm;
    QString markersText = cfm.readFromFile(filePath);
    QStringList markerFileLines = markersText.split('\n');
    int i=0;

    while(i<markerFileLines.length())
    {
        if (markerFileLines[i].startsWith("//"))
            markerFileLines.removeAt(i);
        else
            i++;
    }

    int markerCount = 0;

    for (int i=0;i<markerFileLines.length();i++)
    {
        if (markerFileLines[i].startsWith("m@"))
        {
            QString line = markerFileLines[i];
            parseLineIntoMarkerInfoVector(line);
            markerCount++;
        }
        else if (markerFileLines[i].startsWith("mc@"))
        {
            QString line = markerFileLines[i];
            parsePathIntoMarkerDirectionsVector(line);
        }
    }
    return markerCount;
}

void MarkerMapHandler::parseLineIntoMarkerInfoVector(QString line)
{
    int idStart = line.indexOf('@')+1;
    int idEnd = line.indexOf(':');
    int id = line.mid(idStart,idEnd-idStart).toInt();

    int coordStart = line.indexOf(':')+1;
    int coordEnd = line.length();

    QString coordSubString = line.mid(coordStart,coordEnd-coordStart);
    QStringList coords = coordSubString.split(';');

    float x = coords[0].toFloat(),
            y = coords[1].toFloat(),
            z = coords[2].toFloat(),
            roll = coords[3].toFloat(),
            pitch = coords[4].toFloat(),
            yaw = coords[5].toFloat();

    qDebug() << " x: " + QString::number(x) + " y: " + QString::number(y) + " z: " + QString::number(z);

    MarkerInfo markerInfo(x,y,z,roll,pitch,yaw,id);
    markerInfoVector.append(markerInfo);
}

void MarkerMapHandler::parsePathIntoMarkerDirectionsVector(QString line)
{
    int idStart = line.indexOf('@')+1;
    int idEnd = line.indexOf(':');
    int id = line.mid(idStart,idEnd-idStart).toInt();

    int directionsStart = line.indexOf(':')+1;
    int directionsEnd = line.length();

    QString directionsSubString = line.mid(directionsStart, directionsEnd-directionsStart);
    QStringList directions = directionsSubString.split(';');

    int topMarker = directions[0].toInt(),
            bottomMarker = directions[1].toInt(),
            leftMarker = directions[2].toInt(),
            rightMarker = directions[3].toInt();
    MarkerDirections markerDirections(topMarker, bottomMarker, leftMarker, rightMarker, id);
    markerDirectionsVector.append(markerDirections);
}

void MarkerMapHandler::formMarkerDirectionMap(int markerCount)
{
    for (int i=0;i<markerCount;i++)
    {
        markerCharMap.append(QVector<char>(markerCount));
    }

    for (int i=0;i<markerDirectionsVector.length();i++)
    {
        if (markerDirectionsVector[i].idTop!=-1)
            markerCharMap[markerDirectionsVector[i].id][markerDirectionsVector[i].idTop] = 'T';
        if (markerDirectionsVector[i].idBottom!=-1)
            markerCharMap[markerDirectionsVector[i].id][markerDirectionsVector[i].idBottom] = 'B';
        if (markerDirectionsVector[i].idLeft!=-1)
            markerCharMap[markerDirectionsVector[i].id][markerDirectionsVector[i].idLeft] = 'L';
        if (markerDirectionsVector[i].idRight!=-1)
            markerCharMap[markerDirectionsVector[i].id][markerDirectionsVector[i].idRight] = 'R';
    }
}


const float inf = 3.4e+38;

void MarkerMapHandler::markerMapFloydWarshall()
{
    QVector<QVector<float>> adjacencyMatrix = formMarkerAdjacencyMatrix();
    this->adjacencyMatrix = adjacencyMatrix;

    int matrixSize = adjacencyMatrix.length();

    QVector<QVector<int>> pathMatrix (matrixSize);
    for (int i=0;i<matrixSize;i++)
    {
        pathMatrix[i].append(QVector<int>(matrixSize));
        for (int j=0;j<matrixSize;j++)
        {
            pathMatrix[i][j] = j;
        }
    }

    for(int k = 0; k < matrixSize; k++)
    {
        for(int i = 0; i < matrixSize; i++)
        {
            for(int j = 0; j < matrixSize; j++)
            {
                if ((adjacencyMatrix[i][k]!=inf) && (adjacencyMatrix[k][j]!=inf))
                {
                    if(adjacencyMatrix[i][j]>adjacencyMatrix[i][k]+adjacencyMatrix[k][j])
                    {
                        adjacencyMatrix[i][j]=adjacencyMatrix[i][k]+adjacencyMatrix[k][j];
                        pathMatrix[i][j]=pathMatrix[i][k];
                    }
                }
            }
        }
    }
    markerPathMatrix = pathMatrix;
}


QVector<QVector<float>> MarkerMapHandler::formMarkerAdjacencyMatrix() //QVector<QVector<int>>* pathMatrix)
{
    int matrixSize = markerCharMap.length();
    QVector<QVector<float>> resultMatrix(matrixSize);
    for (int i=0;i<matrixSize;i++)
    {
        resultMatrix[i].append(QVector<float>(matrixSize));
        for (int j=0;j<matrixSize;j++)
        {
            if (i==j)
            {
                resultMatrix[i][j] = 0;
            }
            else if ((markerCharMap[i][j]=='T') || (markerCharMap[i][j]=='B') || (markerCharMap[i][j]=='L') || (markerCharMap[i][j]=='R'))
            {
                AttitudeInfo marker1Attitude = findMarkerById(i).attitude;
                AttitudeInfo marker2Attitude = findMarkerById(j).attitude;
                float distance = getDistance(marker1Attitude.x, marker1Attitude.y, marker1Attitude.z, marker2Attitude.x, marker2Attitude.y, marker2Attitude.z);
                resultMatrix[i][j] = distance;
            }
            else
            {
                resultMatrix[i][j] = inf;
            }
        }
    }
    return resultMatrix;
}


QVector<MissionPlanItem> MarkerMapHandler::formMarkerRoute(float vehicleX, float vehicleY, float vehicleZ, int endMarkerId, float distanceToMarker)
{
    int startMarkerId = findClosestToVehicleMarker(vehicleX, vehicleY, vehicleZ);
    QVector<MissionPlanItem> newPlan;
    AttitudeInfo startMarkerAttitude = findMarkerById(startMarkerId).attitude;
    AttitudeInfo vehicleToStartAttitude = findVehicleAttitude(startMarkerAttitude, distanceToMarker);;
    newPlan.append(MissionPlanItem(0,MAV_CMD_NAV_WAYPOINT,0,0,0,0,0,roundToDigit(vehicleToStartAttitude.x,2), roundToDigit(vehicleToStartAttitude.y,2), roundToDigit(vehicleToStartAttitude.z,2),"-","-","-","-","-","-","-","-","-","-","-"));

    int cnt = 1;
    int i = startMarkerId;
    float totalDist = 0;
    while (i!=endMarkerId)
    {
        totalDist += adjacencyMatrix[i][markerPathMatrix[i][endMarkerId]];
        qDebug()<<QString::number(totalDist);
        i = markerPathMatrix[i][endMarkerId];
        AttitudeInfo currentMarkerAttitude = findMarkerById(i).attitude;

        AttitudeInfo vehicleAttitude = findVehicleAttitude(currentMarkerAttitude, distanceToMarker);
        newPlan.append(MissionPlanItem(cnt,MAV_CMD_NAV_WAYPOINT,0,0,0,0,0,roundToDigit(vehicleAttitude.x,2), roundToDigit(vehicleAttitude.y,2), roundToDigit(vehicleAttitude.z,2),"-","-","-","-","-","-","-","-","-","-","-"));
        cnt++;
    }
    return newPlan;

}

float roundToDigit(float value, int digitNum)
{
    int ratio = pow(10,digitNum);
    return floor(value*ratio)/(float)ratio;
}

AttitudeInfo MarkerMapHandler::findVehicleAttitude(AttitudeInfo markerAttitude, float distanceToMarker)
{
    float xStart = 0;
    float yStart = distanceToMarker;
    float zStart = 0;

    float xRotatedZ = xStart * cos(-markerAttitude.zRot * 3.14159 / 180) + yStart * sin(-markerAttitude.zRot* 3.14159 / 180);
    float yRotatedZ = - xStart * sin(-markerAttitude.zRot* 3.14159 / 180) + yStart * cos(-markerAttitude.zRot* 3.14159 / 180);
    float zRotatedZ = zStart;

    float xRotatedZY = xRotatedZ * cos(-markerAttitude.yRot* 3.14159 / 180) - zRotatedZ * sin(-markerAttitude.yRot* 3.14159 / 180);
    float yRotatedZY = yRotatedZ;
    float zRotatedZY = xRotatedZ * sin(-markerAttitude.yRot* 3.14159 / 180) + zRotatedZ * cos(-markerAttitude.yRot* 3.14159 / 180);

    float xRotatedZYX = xRotatedZY;
    float yRotatedZYX = yRotatedZY * cos(-markerAttitude.xRot* 3.14159 / 180) + zRotatedZY * sin(-markerAttitude.xRot* 3.14159 / 180);
    float zRotatedZYX = - yRotatedZY * sin(-markerAttitude.xRot* 3.14159 / 180) + zRotatedZY * cos(-markerAttitude.xRot* 3.14159 / 180);

    float xVehicle = markerAttitude.x + xRotatedZYX;
    float yVehicle = markerAttitude.y + yRotatedZYX;
    float zVehicle = markerAttitude.z + zRotatedZYX;

    return AttitudeInfo(xVehicle,
                        yVehicle,
                        zVehicle,
                        markerAttitude.xRot,
                        - markerAttitude.yRot,
                        markerAttitude.zRot);
}

int MarkerMapHandler::findClosestToVehicleMarker(float vehicleX, float vehicleY, float vehicleZ)
{
    int closestMarkerId = 0;
    float distanceToClosestMarker = inf;
    for (int i=0;i<markerInfoVector.length();i++)
    {
        AttitudeInfo markerAttitude = markerInfoVector[i].attitude;
        float distanceToMarker = getDistance(markerAttitude.x, markerAttitude.y, markerAttitude.z, vehicleX, vehicleY, vehicleZ);
        if (distanceToMarker < distanceToClosestMarker)
        {
            distanceToClosestMarker = distanceToMarker;
            closestMarkerId = i;
        }
    }
    return closestMarkerId;

}

MarkerInfo MarkerMapHandler::findMarkerById(int id)
{
    for (int i=0;i<markerInfoVector.length();i++)
    {
        if (markerInfoVector[i].id==id)
        {
            return markerInfoVector[i];
        }
    }
    return MarkerInfo();
}

float getDistance(float x1, float y1, float z1, float x2, float y2, float z2)
{
    return sqrt(pow(x1 - x2,2) + pow(y1 - y2,2) + pow(z1 - z2,2));
}
