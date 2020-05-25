#ifndef FUTRONIC_H
#define FUTRONIC_H
#include <Python.h>
#include "preprocessing.h"
#include "extraction.h"
#include "ftrScanAPI.h"
#include "structures.h"


class Futronic
{
public:
    Futronic();
    cv::Mat scanFinger();
};


#endif // FUTRONIC_H
