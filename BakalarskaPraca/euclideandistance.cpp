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
#include <QMessageBox>
#include "angles.h"
#include "nearestneighbour.h"
#include "filesoperations.h"
#include "structures.h"


EuclideanDistance::EuclideanDistance()
{

}

QList<QList<FeatureVector>> EuclideanDistance::EuklidDistance(EXTRACTION_RESULTS results, int label, QString dir){


    double distance;
    double tmp = 0;
    double value = 0;
    QList<int> listOftypes;
    FeatureVector data;
    QList<FeatureVector> allData;
    QList<QList<FeatureVector>> listOfData;
    QList<double> calculatedDistance;
    QMap<double, int> map;
    for(int i =0; i < results.minutiaePredictedFixed.length(); i++){
        for(int j = 0; j < results.minutiaePredictedFixed.length(); j++){
           value = qPow((results.minutiaePredictedFixed[i].xy.x() - results.minutiaePredictedFixed[j].xy.x()),2) + qPow((results.minutiaePredictedFixed[i].xy.y() - results.minutiaePredictedFixed[j].xy.y()),2);
        if(value < 0){
           tmp = value;
           value = value - tmp - tmp;
        }
           distance = qSqrt(value);

           if(distance != 0.0){
              data.Xchild = results.minutiaePredictedFixed[j].xy.x();
              data.Ychild = results.minutiaePredictedFixed[j].xy.y();
              data.Xparent = results.minutiaePredictedFixed[i].xy.x();
              data.Yparent = results.minutiaePredictedFixed[i].xy.y();
              data.distance = distance;
              data.typeOfChild = results.minutiaePredicted[j].type +10;
              data.typeOfParent = results.minutiaePredictedFixed[i].type + 10;
              allData.append(data);
           }
           else{
               continue;
           }
       }
       listOfData.append(neighbour.getThreeNearestMinutiae(allData));
       allData.clear();

    }

   QList<QList<FeatureVector>> finalData;
   for(int i = 0; i < listOfData.size(); i++){
       finalData.append(angle.getAllAngles(listOfData[i]));
   }
   files.printDataToFile(finalData,label-1, dir);
   return finalData;
}

 QList<QList<Neighbour>> EuclideanDistance::getAllEukclidianDistances(EXTRACTION_RESULTS results){
double distance, distance2;
double tmp = 0;
double value = 0;
QList<int> listOftypes;
Neighbour minutiae;

QList<Neighbour> calculatedDistances;
QList<QList<Neighbour>> finalDistances;
QMap<double, int> map;
for(int i =0; i < results.minutiaePredictedFixed.length(); i++){
    for(int j = 0; j < results.minutiaePredictedFixed.length(); j++){
        value = qPow((results.minutiaePredictedFixed[i].xy.x() - results.minutiaePredictedFixed[j].xy.x()),2) + qPow((results.minutiaePredictedFixed[i].xy.y() - results.minutiaePredictedFixed[j].xy.y()),2);
    if(value < 0){
       tmp = value;
       value = value - tmp - tmp;
    }
       distance = qSqrt(value);
       distance2 = (int)distance;

      // if(distance != 0.0){
            minutiae.distance = distance2;
            minutiae.XPoint = results.minutiaePredictedFixed[j].xy.x();
            minutiae.YPoint = results.minutiaePredictedFixed[j].xy.y();
            calculatedDistances.append(minutiae);
   }
   finalDistances.append(neighbour.getFiveNearesMinutiae(calculatedDistances));
   calculatedDistances.clear();
}
    return finalDistances;
}

