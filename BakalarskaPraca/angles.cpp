#include "angles.h"
#include "euclideandistance.h"
#include <QFileDialog>
#include "opencv4/opencv2/highgui.hpp"
#include "opencv4/opencv2/core.hpp"
#include "opencv4/opencv2/imgcodecs.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QDebug>
#include <QMouseEvent>
#include <iostream>
#include <QList>
#include <QtMath>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include "ftrScanAPI.h"
#include <pythonrun.h>
#include <QMessageBox>
#include "structures.h"


Angles::Angles()
{

}

QList<FeatureVector> Angles::getAllAngles(QList<FeatureVector> listOfFeatureVectorsWithoutAngles){
    QList<FeatureVector>::iterator it1;
    QList<double> distancesToChilds;
    QList<int> coordsOfChilds;
    qreal angle1_2, angle2_3, angle1_3;
    int i = 0;
    int tmp = 0;
    double distanceBetweenNearestMinutiae[3];
    QList<FeatureVector> listOfFeatureVectorsWithAngles = listOfFeatureVectorsWithoutAngles;

    int dist1, dist2, dist3;
    QList<int> distances;
        for(it1 = listOfFeatureVectorsWithoutAngles.begin(); it1!=listOfFeatureVectorsWithoutAngles.end(); ++it1){
            coordsOfChilds.append(it1->Xchild);
            coordsOfChilds.append(it1->Ychild);
        }

    dist1 = qPow((coordsOfChilds.at(0) - coordsOfChilds.at(2)),2) + qPow((coordsOfChilds.at(1) - coordsOfChilds.at(3)),2);
    if(dist1 < 0){
       tmp = dist1;
       dist1 = dist1 - tmp - tmp;
    }
    distancesToChilds.append(qSqrt(dist1));

    dist2 = qPow((coordsOfChilds.at(2) - coordsOfChilds.at(4)),2) + qPow((coordsOfChilds.at(3) - coordsOfChilds.at(5)),2);
    if(dist2 < 0){
       tmp = dist2;
       dist2 = dist2 - tmp - tmp;
    }
    distancesToChilds.append(qSqrt(dist2));

    dist3 = qPow((coordsOfChilds.at(0) - coordsOfChilds.at(4)),2) + qPow((coordsOfChilds.at(1) - coordsOfChilds.at(5)),2);
    if(dist3 < 0){
       tmp = dist3;
       dist3 = dist3 - tmp - tmp;
    }
    distancesToChilds.append(qSqrt(dist3));

    for(it1 = listOfFeatureVectorsWithoutAngles.begin(); it1!=listOfFeatureVectorsWithoutAngles.end(); it1++){
           distanceBetweenNearestMinutiae[i] = it1->distance;
           i++;
    }
    angle1_2 = qAcos((qPow((distanceBetweenNearestMinutiae[1]),2) +qPow((distanceBetweenNearestMinutiae[0]),2) - qPow((distancesToChilds[0]),2))/(2*distanceBetweenNearestMinutiae[0]*distanceBetweenNearestMinutiae[1]));
    if(qIsNaN(angle1_2)){
        angle1_2 = 0;
    }
    angle2_3 = qAcos((qPow((distanceBetweenNearestMinutiae[2]),2) +qPow((distanceBetweenNearestMinutiae[1]),2) - qPow((distancesToChilds[1]),2))/(2*distanceBetweenNearestMinutiae[1]*distanceBetweenNearestMinutiae[2]));
    if(qIsNaN(angle2_3)){
        angle2_3 = 0;
    }
    angle1_3 = qAcos((qPow((distanceBetweenNearestMinutiae[2]),2) +qPow((distanceBetweenNearestMinutiae[0]),2) - qPow((distancesToChilds[2]),2))/(2*distanceBetweenNearestMinutiae[0]*distanceBetweenNearestMinutiae[2]));
    if(qIsNaN(angle1_3)){
        angle1_3 = 0;
    }

    listOfFeatureVectorsWithAngles[0].angle1 = qRadiansToDegrees(angle1_2);
    listOfFeatureVectorsWithAngles[0].angle2 = qRadiansToDegrees(angle2_3);
    listOfFeatureVectorsWithAngles[0].angle3 = qRadiansToDegrees(angle1_3);
    listOfFeatureVectorsWithAngles[1].angle1 = qRadiansToDegrees(angle2_3);
    listOfFeatureVectorsWithAngles[1].angle2 = qRadiansToDegrees(angle1_2);
    listOfFeatureVectorsWithAngles[1].angle3 = qRadiansToDegrees(angle1_3);
    listOfFeatureVectorsWithAngles[2].angle1 = qRadiansToDegrees(angle1_3);
    listOfFeatureVectorsWithAngles[2].angle2 = qRadiansToDegrees(angle2_3);
    listOfFeatureVectorsWithAngles[2].angle3 = qRadiansToDegrees(angle1_2);

    return listOfFeatureVectorsWithAngles;
}

int Angles::getAngleBetweenTwoEdges(QList<Neighbour> dataFromFingerpint, int positionOfFirtsEdge, int positionOfSecondsEdge){
    QList<double> distancesToChilds;
    QList<int> coordsOfChilds;
    qreal computedAngleBetweenTwoEdges;
    double distBetweenNearestMinutiae;

    distBetweenNearestMinutiae = qPow((dataFromFingerpint.at(positionOfFirtsEdge).XPoint - dataFromFingerpint.at(positionOfSecondsEdge).XPoint),2) + qPow((dataFromFingerpint.at(positionOfFirtsEdge).YPoint - dataFromFingerpint.at(positionOfSecondsEdge).YPoint),2);
    if(distBetweenNearestMinutiae < 0){
       int tmp = distBetweenNearestMinutiae;
       distBetweenNearestMinutiae = distBetweenNearestMinutiae - tmp - tmp;
    }
    distancesToChilds.append(qSqrt(distBetweenNearestMinutiae));
    double dist = qSqrt(distBetweenNearestMinutiae);

    computedAngleBetweenTwoEdges = qAcos((qPow((dataFromFingerpint[positionOfFirtsEdge].distance),2) +qPow((dataFromFingerpint[positionOfSecondsEdge].distance),2) - qPow((dist),2))/(2*dataFromFingerpint[positionOfFirtsEdge].distance*dataFromFingerpint[positionOfSecondsEdge].distance));
    if(qIsNaN(computedAngleBetweenTwoEdges)){
        computedAngleBetweenTwoEdges = 0;
    }
    return qRadiansToDegrees(computedAngleBetweenTwoEdges);
}
