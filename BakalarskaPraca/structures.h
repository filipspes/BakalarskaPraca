#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <QtMath>

struct FeatureVector{
    int Xparent;
    int Yparent;
    int Xchild;
    int Ychild;
    double distance;
    int typeOfChild;
    int typeOfParent;
    qreal angle1;
    qreal angle2;
    qreal angle3;
};
struct MTuples{
    double ratio;
    int angle;
};
struct Neighbour{
    int XPoint;
    int YPoint;
    double distance;
};
struct CartezianDim{
    int xPointMin;
    int yPointMin;
    int xPointMax;
    int yPointMax;
};
struct Dimensions{
    int position;
    int dimension;
};

struct VertexEdge{
    int pointX;
    int pointY;
    int distanceToNext;
};

#endif // STRUCTURES_H
