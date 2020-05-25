#include "tuples.h"
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

Tuples::Tuples()
{

}
QList<QList<MTuples>> Tuples::createTuples(QList<QList<Neighbour>> datafromFingerprint)
{
    QList<MTuples> ratios;
    MTuples mTuple;
    QList<QList<MTuples>> allRatiosFromFingerPrint;

    for(int i = 0; i < datafromFingerprint.size(); i++){
            if(datafromFingerprint[i].at(1).distance >= datafromFingerprint[i].at(2).distance){
                mTuple.ratio = round((datafromFingerprint[i].at(1).distance/datafromFingerprint[i].at(2).distance)*100)/100;
            }
            else{
                mTuple.ratio = round((datafromFingerprint[i].at(2).distance/datafromFingerprint[i].at(1).distance)*100)/100;
            }
            mTuple.angle = angle.getAngleBetweenTwoEdges(datafromFingerprint[i], 1,2);
            ratios.append(mTuple);

            if(datafromFingerprint[i].at(1).distance > datafromFingerprint[i].at(3).distance){
                mTuple.ratio = round((datafromFingerprint[i].at(1).distance/datafromFingerprint[i].at(3).distance)*100)/100;
            }
            else{
                mTuple.ratio = round((datafromFingerprint[i].at(3).distance/datafromFingerprint[i].at(1).distance)*100)/100;
            }
            mTuple.angle = angle.getAngleBetweenTwoEdges(datafromFingerprint[i], 1,3);
            ratios.append(mTuple);

            if(datafromFingerprint[i].at(1).distance > datafromFingerprint[i].at(4).distance){
                mTuple.ratio = round((datafromFingerprint[i].at(1).distance/datafromFingerprint[i].at(4).distance)*100)/100;
            }
            else{
                mTuple.ratio = round((datafromFingerprint[i].at(4).distance/datafromFingerprint[i].at(1).distance)*100)/100;
            }
            mTuple.angle = angle.getAngleBetweenTwoEdges(datafromFingerprint[i], 1,4);
            ratios.append(mTuple);

            if(datafromFingerprint[i].at(1).distance > datafromFingerprint[i].at(5).distance){
                mTuple.ratio = round((datafromFingerprint[i].at(1).distance/datafromFingerprint[i].at(5).distance)*100)/100;
            }
            else{
                mTuple.ratio = round((datafromFingerprint[i].at(5).distance/datafromFingerprint[i].at(1).distance)*100)/100;
            }
            mTuple.angle = angle.getAngleBetweenTwoEdges(datafromFingerprint[i], 1,5);
            ratios.append(mTuple);

            if(datafromFingerprint[i].at(2).distance > datafromFingerprint[i].at(3).distance){
                mTuple.ratio = round((datafromFingerprint[i].at(2).distance/datafromFingerprint[i].at(3).distance)*100)/100;
            }
            else{
                mTuple.ratio = round((datafromFingerprint[i].at(3).distance/datafromFingerprint[i].at(2).distance)*100)/100;
            }
            mTuple.angle = angle.getAngleBetweenTwoEdges(datafromFingerprint[i], 2,3);
            ratios.append(mTuple);

            if(datafromFingerprint[i].at(2).distance > datafromFingerprint[i].at(4).distance){
                mTuple.ratio = round((datafromFingerprint[i].at(2).distance/datafromFingerprint[i].at(4).distance)*100)/100;
            }
            else{
                mTuple.ratio = round((datafromFingerprint[i].at(4).distance/datafromFingerprint[i].at(2).distance)*100)/100;
            }
            mTuple.angle = angle.getAngleBetweenTwoEdges(datafromFingerprint[i], 2,4);
            ratios.append(mTuple);

            if(datafromFingerprint[i].at(2).distance > datafromFingerprint[i].at(5).distance){
                mTuple.ratio = round((datafromFingerprint[i].at(2).distance/datafromFingerprint[i].at(5).distance)*100)/100;
            }
            else{
                mTuple.ratio = round((datafromFingerprint[i].at(5).distance/datafromFingerprint[i].at(2).distance)*100)/100;
            }
            mTuple.angle = angle.getAngleBetweenTwoEdges(datafromFingerprint[i], 2,5);
            ratios.append(mTuple);

            if(datafromFingerprint[i].at(3).distance > datafromFingerprint[i].at(4).distance){
                mTuple.ratio = round((datafromFingerprint[i].at(3).distance/datafromFingerprint[i].at(4).distance)*100)/100;
            }
            else{
                mTuple.ratio = round((datafromFingerprint[i].at(4).distance/datafromFingerprint[i].at(3).distance)*100)/100;
            }
            mTuple.angle = angle.getAngleBetweenTwoEdges(datafromFingerprint[i], 3,4);
            ratios.append(mTuple);

            if(datafromFingerprint[i].at(3).distance > datafromFingerprint[i].at(5).distance){
                mTuple.ratio = round((datafromFingerprint[i].at(3).distance/datafromFingerprint[i].at(5).distance)*100)/100;
            }
            else{
                mTuple.ratio = round((datafromFingerprint[i].at(5).distance/datafromFingerprint[i].at(3).distance)*100)/100;
            }
            mTuple.angle = angle.getAngleBetweenTwoEdges(datafromFingerprint[i], 3,4);
            ratios.append(mTuple);

            if(datafromFingerprint[i].at(4).distance > datafromFingerprint[i].at(5).distance){
                mTuple.ratio = round((datafromFingerprint[i].at(4).distance/datafromFingerprint[i].at(5).distance)*100)/100;
            }
            else{
                mTuple.ratio = round((datafromFingerprint[i].at(5).distance/datafromFingerprint[i].at(4).distance)*100)/100;
            }
            mTuple.angle = angle.getAngleBetweenTwoEdges(datafromFingerprint[i], 4,5);
            ratios.append(mTuple);

            allRatiosFromFingerPrint.append(ratios);
            ratios.clear();
        }
    return allRatiosFromFingerPrint;
}

int Tuples::matchPairOfTuples(QList<MTuples> tuplesFromFirst, QList<MTuples> tuplesFromSecond)
{
    int numberOfSimilarItemsInTuple = 0;
    for(int i = 0; i < tuplesFromFirst.size(); i++){
        for(int j = 0; j < tuplesFromSecond.size(); j++){
            if((tuplesFromFirst[i].ratio == tuplesFromSecond[j].ratio) || ((tuplesFromFirst[i].ratio < tuplesFromSecond[j].ratio) && (tuplesFromFirst[i].ratio > ((tuplesFromSecond[j].ratio)-0.03))) || ((tuplesFromFirst[i].ratio > tuplesFromSecond[j].ratio) && (tuplesFromFirst[i].ratio < (tuplesFromSecond[j].ratio)+0.03))){
                if((tuplesFromFirst[i].angle == tuplesFromSecond[j].angle) || ((tuplesFromFirst[i].angle < tuplesFromSecond[j].angle) && (tuplesFromFirst[i].angle > ((tuplesFromSecond[j].angle)-3.5))) || ((tuplesFromFirst[i].angle > tuplesFromSecond[j].angle) && (tuplesFromFirst[i].angle < (tuplesFromSecond[j].angle)-3.5))){
                        numberOfSimilarItemsInTuple++;
                }
             }
        }
    }
    return numberOfSimilarItemsInTuple;
}

int Tuples::checkMatched(QList<int> isMatched, int positionToSkip){
    int mostSimilar = 2;
    int positionOfMostSimilar = 0;
    QList<int> retVal;
    bool duplicityBool = false;
    if(positionToSkip > 0){
        duplicityBool = true;
    }
    for(int k = 0; k < isMatched.size(); k++){
        if(duplicityBool == true && k == positionToSkip){
            continue;
        }
        else{
            if(isMatched.at(k) >= mostSimilar){
                mostSimilar = isMatched.at(k);
                positionOfMostSimilar = k;
                retVal.append(mostSimilar);
                retVal.append(positionOfMostSimilar);
                return positionOfMostSimilar;
            }
        }
    }
    return 0;
}

QMap<int,int> Tuples::matchAllTuples(QList<QList<MTuples>> tuplesFromFirstFingerprint, QList<QList<MTuples>> tuplesFromSecondFingerprint)
{
    QMap<int,int> SimilarTuples;
    QMap<int,int>::Iterator iterator;

    QList<int> isMatched;
    for(int i = 0; i < tuplesFromFirstFingerprint.size(); i++){
        for(int j = 0; j < tuplesFromSecondFingerprint.size(); j++){
            isMatched.append(matchPairOfTuples(tuplesFromFirstFingerprint[i], tuplesFromSecondFingerprint[j]));
        }
        int retVal = checkMatched(isMatched, -1);
        int positionToSkip = retVal;
        isMatched.clear();
        for(iterator = SimilarTuples.begin(); iterator != SimilarTuples.end(); ++iterator){
           if(iterator.value() == retVal){
           retVal = checkMatched(isMatched, positionToSkip);
           }
        }
        if(retVal != 0){
            SimilarTuples.insert(i,retVal);
        }
    }
    return SimilarTuples;
}

