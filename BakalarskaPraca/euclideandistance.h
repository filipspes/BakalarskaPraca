#ifndef EUCLIDEANDISTANCE_H
#define EUCLIDEANDISTANCE_H
#include <Python.h>
#include "preprocessing.h"
#include "extraction.h"
#include "structures.h"
#include "angles.h"
#include "filesoperations.h"
#include "nearestneighbour.h"


class EuclideanDistance
{
public:
    EuclideanDistance();

    QList<QList<FeatureVector>> EuklidDistance(EXTRACTION_RESULTS results, int label, QString dir);
    QList<QList<Neighbour>> getAllEukclidianDistances(EXTRACTION_RESULTS results);

private:
    Preprocessing preprocessing;
    Extraction extraction;
    Angles angle;
    FilesOperations files;
    NearestNeighbour neighbour;

};

#endif // EUCLIDEANDISTANCE_H
