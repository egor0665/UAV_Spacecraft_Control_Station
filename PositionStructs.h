#ifndef POSITIONSTRUCTS_H
#define POSITIONSTRUCTS_H


struct AttitudeInfo
{
    float x=0,y=0,z=0,xRot=0,yRot=0,zRot=0;
    AttitudeInfo(float x,float y,float z, float xRot,float yRot,float zRot)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->xRot = xRot;
        this->yRot = yRot;
        this->zRot = zRot;
    }
    AttitudeInfo(){};
};


struct PositionInfo
{
    float x=0,y=0,z=0;
    PositionInfo(float x,float y,float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};



struct MarkerInfo
{
    AttitudeInfo attitude;
    int id;
    MarkerInfo(AttitudeInfo attitude, int id)
    {
        this->attitude = attitude;
        this->id = id;
    }
    MarkerInfo(float x,float y,float z, float xRot,float yRot,float zRot, int id)
    {
        this->attitude = AttitudeInfo(x,y,z,xRot,yRot,zRot);
        this->id = id;
    }
    MarkerInfo(){}
};

struct Offset
{
    float xOffset;
    float yOffset;
    float zOffset;
    Offset(){};
    Offset(float xOffset, float yOffset, float zOffset)
    {
        this->xOffset = xOffset;
        this->yOffset = yOffset;
        this->zOffset = zOffset;
    }
};



struct MarkerDirections
{
    int id;
    int idTop;
    int idBottom;
    int idLeft;
    int idRight;
    MarkerDirections(int idTop,int idBottom,int idLeft,int idRight,int id)
    {
        this->id = id;
        this->idTop = idTop;
        this->idLeft = idLeft;
        this->idBottom = idBottom;
        this->idRight = idRight;
    }
};
#endif // POSITIONSTRUCTS_H
