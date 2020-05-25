#include "nearestneighbour.h"

NearestNeighbour::NearestNeighbour()
{

}


QList<FeatureVector> NearestNeighbour::getThreeNearestMinutiae(QList<FeatureVector> allMinutiaeFromFingerprints){
    QList<FeatureVector> threeNearestMinutiae;
    double firstMin = MAX_DISTANCE;
    double secondMin = MAX_DISTANCE;
    double thirdMin = MAX_DISTANCE;
    QList<double> minimalDistances;
    QList<FeatureVector>::iterator it1;
    QList<double>::iterator it;

    for (it1 = allMinutiaeFromFingerprints.begin(); it1 != allMinutiaeFromFingerprints.end(); ++it1){

        if(it1->distance < firstMin){
            thirdMin = secondMin;
            secondMin = firstMin;
            firstMin = it1->distance;
        }
        else if(it1->distance < secondMin){
            thirdMin = secondMin;
            secondMin = it1->distance;
        }
        else if(it1->distance < thirdMin){
            thirdMin = it1->distance;
        }
    }
    minimalDistances.append(firstMin);
    minimalDistances.append(secondMin);
    minimalDistances.append(thirdMin);
    for(it = minimalDistances.begin(); it != minimalDistances.end(); ++it){
        for (it1 = allMinutiaeFromFingerprints.begin(); it1 != allMinutiaeFromFingerprints.end(); ++it1){
            if(*it == it1->distance){
                if(threeNearestMinutiae.size() == 3){
                    break;
                }
                threeNearestMinutiae.append(*it1);
                continue;
            }
         }
    }
    return threeNearestMinutiae;
}
QList<Neighbour> NearestNeighbour::getFiveNearesMinutiae(QList<Neighbour> allMinutiaeFromFingerprints){
    QList<double> triplet;
    Neighbour firstMin;
    Neighbour secondMin;
    Neighbour thirdMin;
    Neighbour fourthMin;
    Neighbour fifthMin;
    Neighbour sixthMin;
    firstMin.distance = MAX_DISTANCE;
    secondMin.distance = MAX_DISTANCE;
    thirdMin.distance = MAX_DISTANCE;
    fourthMin.distance = MAX_DISTANCE;
    fifthMin.distance = MAX_DISTANCE;
    sixthMin.distance = MAX_DISTANCE;

    QList<Neighbour> minimalDistances;
    QList<FeatureVector>::iterator it1;
    QList<double>::iterator it;

    for(int i = 0 ; i < allMinutiaeFromFingerprints.size(); i++){

        if(allMinutiaeFromFingerprints[i].distance < firstMin.distance){
            sixthMin = fifthMin;
            fifthMin = fourthMin;
            fourthMin = thirdMin;
            thirdMin = secondMin;
            secondMin = firstMin;
            firstMin = allMinutiaeFromFingerprints[i];
        }
        else if(allMinutiaeFromFingerprints[i].distance < secondMin.distance){
            sixthMin = fifthMin;
            fifthMin = fourthMin;
            fourthMin = thirdMin;

            thirdMin = secondMin;
            secondMin = allMinutiaeFromFingerprints[i];
        }
        else if(allMinutiaeFromFingerprints[i].distance  < thirdMin.distance){
            sixthMin = fifthMin;
            fifthMin = fourthMin;
            fourthMin = thirdMin;
            thirdMin = allMinutiaeFromFingerprints[i];
        }
        else if(allMinutiaeFromFingerprints[i].distance < fourthMin.distance){
            sixthMin = fifthMin;
            fifthMin = fourthMin;
            fourthMin = allMinutiaeFromFingerprints[i];
        }
        else if(allMinutiaeFromFingerprints[i].distance < fifthMin.distance){
            sixthMin = fifthMin;
            fifthMin = allMinutiaeFromFingerprints[i];
        }
        else if(allMinutiaeFromFingerprints[i].distance < sixthMin.distance){
            sixthMin = allMinutiaeFromFingerprints[i];
        }
    }
    minimalDistances.append(firstMin);
    minimalDistances.append(secondMin);
    minimalDistances.append(thirdMin);
    minimalDistances.append(fourthMin);
    minimalDistances.append(fifthMin);
    minimalDistances.append(sixthMin);

    return minimalDistances;
}
