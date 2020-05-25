#ifndef FILESOPERATIONS_H
#define FILESOPERATIONS_H
#include <Python.h>
#include "structures.h"

class FilesOperations
{
public:
    FilesOperations();

    void printDataToFile(QList<QList<FeatureVector>> featureVectorsToPrint, int label, QString directoryToSave);
};

#endif // FILESOPERATIONS_H
