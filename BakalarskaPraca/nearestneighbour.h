#ifndef NEARESTNEIGHBOUR_H
#define NEARESTNEIGHBOUR_H
#include <Python.h>
#include "preprocessing.h"
#include "extraction.h"
#include "ftrScanAPI.h"
#include "structures.h"

#define MAX_DISTANCE 100000

class NearestNeighbour
{
public:
    NearestNeighbour();
    QList<FeatureVector> getThreeNearestMinutiae(QList<FeatureVector> allMinutiaeFromFingerprints);
    QList<Neighbour> getFiveNearesMinutiae(QList<Neighbour> allMinutiaeFromFingerprints);
};

#endif // NEARESTNEIGHBOUR_H
