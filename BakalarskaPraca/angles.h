#ifndef ANGLES_H
#define ANGLES_H
#include <Python.h>
#include "preprocessing.h"
#include "extraction.h"
#include "ftrScanAPI.h"
#include "structures.h"



class Angles
{
public:

    Angles();

    QList<FeatureVector> getAllAngles(QList<FeatureVector> listOfFeatureVectorsWithoutAngles);
    int getAngleBetweenTwoEdges(QList<Neighbour> dataFromFingerpint, int positionOfFirtsEdge, int positionOfSecondsEdge);

};

#endif // ANGLES_H
