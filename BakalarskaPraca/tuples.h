#ifndef TUPLES_H
#define TUPLES_H
#include <Python.h>
#include "preprocessing.h"
#include "extraction.h"
#include "ftrScanAPI.h"
#include "structures.h"
#include "angles.h"

class Tuples
{
public:
    Tuples();

    QList<QList<MTuples>> createTuples(QList<QList<Neighbour>> datafromFingerprint);
    int matchPairOfTuples(QList<MTuples> tuplesFromFirst, QList<MTuples> tuplesFromSecond);
    QMap<int,int> matchAllTuples(QList<QList<MTuples>> tuplesFromFirstFingerprint, QList<QList<MTuples>> tuplesFromSecondFingerprint);
    int checkMatched(QList<int> isMatched, int positionToSkip);

    Angles angle;

};

#endif // TUPLES_H
