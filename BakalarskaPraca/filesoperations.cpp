#include "filesoperations.h"
#include <QFileDialog>
#include <QDebug>
#include <iostream>
#include <QList>
#include <QtMath>
#include <QVector>
#include <QFile>
#include <QTextStream>

FilesOperations::FilesOperations()
{

}

void FilesOperations::printDataToFile(QList<QList<FeatureVector>> featureVectorsToPrint, int label, QString directoryToSave){
    QString filename;
    if(label < 0){
       filename = directoryToSave + "/FeatureVectorsToCompare.csv";
    }
    else{
        filename = directoryToSave + "/FeatureVectorsToTrain.csv";
    }
    QFile file(filename);
    int diference = 0;
    bool setClass = true;
    int titles = 2500;
    if(label < 0){
        setClass = false;
    }
            if (file.open(QIODevice::Append)) {
            QTextStream stream(&file);
            if (file.pos() == 0) {
                for(int i = 0; i < titles; i++){
                    if(setClass == true){
                        if(i == 0){
                            stream << "Class" << ",";
                        }
                    }
                    if(i !=titles-1){
                        stream << "a"+QString::number(i+1)+",";
                    }
                    else{
                        stream << "a"+QString::number(i+1);
                    }
                }
                stream << endl;
            }
            if(label >= 0){
               stream << label << ",";
            }
            for(int i = 0; i<featureVectorsToPrint.size(); i++){
                if(i != featureVectorsToPrint.size()-1){
                   stream <<  featureVectorsToPrint[i].at(0).typeOfParent <<","<< featureVectorsToPrint[i].at(0).typeOfChild <<","<< featureVectorsToPrint[i].at(1).typeOfChild <<","<< featureVectorsToPrint[i].at(2).typeOfChild <<","<< featureVectorsToPrint[i].at(0).distance<<","<< featureVectorsToPrint[i].at(1).distance<<","<<featureVectorsToPrint[i].at(2).distance<<","<<featureVectorsToPrint[i].at(0).angle1<<","<<featureVectorsToPrint[i].at(0).angle2<<","<<featureVectorsToPrint[i].at(0).angle3<<",";
                }
                else{
                    stream <<  featureVectorsToPrint[i].at(0).typeOfParent <<","<< featureVectorsToPrint[i].at(0).typeOfChild <<","<< featureVectorsToPrint[i].at(1).typeOfChild <<","<< featureVectorsToPrint[i].at(2).typeOfChild <<","<< featureVectorsToPrint[i].at(0).distance<<","<< featureVectorsToPrint[i].at(1).distance<<","<<featureVectorsToPrint[i].at(2).distance<<","<<featureVectorsToPrint[i].at(0).angle1<<","<<featureVectorsToPrint[i].at(0).angle2<<","<<featureVectorsToPrint[i].at(0).angle3;
                }
            }
            diference = titles + 1 - (featureVectorsToPrint.size()*10);
            for(int j = 0; j < diference; j++){
                if(j != diference-1){
                    stream << "0,";
                }
                else{
                    stream << "0";
                }
            }
            stream << endl;
            }
}

