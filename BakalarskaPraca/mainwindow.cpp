#include <Python.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include <pythonrun.h>
#include <QMessageBox>
#include <angles.h>
#include <euclideandistance.h>
#include <filesoperations.h>
#include <nearestneighbour.h>
#include <structures.h>
#include <tuples.h>
#include "futronic.h"

#define MAX_DISTANCE 100000


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType<EXTRACTION_RESULTS >("PREPROCESSING_RESULTS");
    qRegisterMetaType<EXTRACTION_RESULTS >("EXTRACTION_RESULTS");
    connect(&preprocessing,SIGNAL(preprocessingDoneSignal(PREPROCESSING_RESULTS)),this,SLOT(preprocessingResultsSlot(PREPROCESSING_RESULTS)));
    connect(&extraction, SIGNAL(extractionDoneSignal(EXTRACTION_RESULTS)), this, SLOT(extractionResultsSlot(EXTRACTION_RESULTS)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


/*BUTTONS*/


void MainWindow::on_SaveData_Button_clicked()
{
    QMessageBox msgBox;
    QList<QList<FeatureVector>> EuklidDistanceResults;
    QString dir = QFileDialog::getExistingDirectory(this, tr("Save to"),"/home",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);

    for(int j = 0; j < listOfExtractionResults.size(); j++){
                EuklidDistanceResults = distance.EuklidDistance(listOfExtractionResults[j],this->labels[j], dir);
    }
    msgBox.setWindowTitle("Saved succesfully");
    msgBox.setText("Dataset saved to "+dir+"/FeatureVectorsToTrain.csv");
    msgBox.exec();
}

void MainWindow::on_ExtractDataFromFingerprintsDB_Button_clicked()
{
    QString nr, nr1;
    this->labels.clear();
    for(int i = 1; i < 101; i++){
        for(int j = 1; j <= 8; j++){
            this->labels.push_back(i);
            nr = QString::number(i);
            nr1 = QString::number(j);
            img = cv::imread(QString(pathToFingerprints+"/"+nr+"_"+nr1+".tif").arg(i,j).toStdString());
            preprocessing.loadInput(img);
            preprocessing.start();
            extraction.loadInput(preprocessingResult);
            extraction.start();
            extraction.wait(5000);
       }
    }
       qDebug() << "DONE !" << endl;
}


void MainWindow::on_ConstructTestDataset_clicked()
{

    QMessageBox msgBox;
    QList<QList<FeatureVector>> EuklidDistanceResults;
    QString dir = QFileDialog::getExistingDirectory(this, tr("Save to"),"/home",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    for(int j = 0; j < listOfExtractionResults.size(); j++){
       EuklidDistanceResults = distance.EuklidDistance(listOfExtractionResults[j], 0, dir);
    }
    msgBox.setWindowTitle("Saved successfully");
    msgBox.setText("Dataset saved to "+dir+"/FeatureVectorsToCompare.csv");
    msgBox.exec();
}



/* Preprocessing results slot*/
void MainWindow::preprocessingResultsSlot(PREPROCESSING_RESULTS v)
{
    preprocessingResult = v;
}

/*Extraction results slot*/
void MainWindow::extractionResultsSlot(EXTRACTION_RESULTS results)
{
    QList<QPoint> listOfPoints;
    listOfExtractionResults.append(results);

    for(int i =0; i < results.minutiaePredictedFixed.length(); i++){
    listOfPoints.append(results.minutiaePredictedFixed[i].xy);
    if(results.minutiaePredictedFixed[i].type == 0){
        cv::circle(img, cv::Point(results.minutiaePredictedFixed[i].xy.x(), results.minutiaePredictedFixed[i].xy.y()), 5, cv::Scalar(255,0,0),1 );
        cv::line(img, cv::Point(results.minutiaePredictedFixed[i].xy.x(), results.minutiaePredictedFixed[i].xy.y()), cv::Point(results.minutiaePredictedFixed[i].xy.x() +10*cos(CV_PI-results.minutiaePredictedFixed[i].angle), results.minutiaePredictedFixed[i].xy.y() +10*sin(CV_PI-results.minutiaePredictedFixed[i].angle)),cv::Scalar(255,0,0),1);
    }
    else{
        cv::circle(img, cv::Point(results.minutiaePredictedFixed[i].xy.x(), results.minutiaePredictedFixed[i].xy.y()), 5, cv::Scalar(0,0,255),1 );
        cv::line(img, cv::Point(results.minutiaePredictedFixed[i].xy.x(), results.minutiaePredictedFixed[i].xy.y()), cv::Point(results.minutiaePredictedFixed[i].xy.x() +10*cos(CV_PI-results.minutiaePredictedFixed[i].angle), results.minutiaePredictedFixed[i].xy.y() +10*sin(CV_PI-results.minutiaePredictedFixed[i].angle)),cv::Scalar(0,0,255),1);
    }

    }
}


void MainWindow::on_LoadfirstImg_Button_clicked()
{

    QString path = QFileDialog::getOpenFileName(this, "Select first fingerprint", commonPath);
    ui->label->clear();
    img = cv::imread(path.toStdString().c_str());
    img2 = img;
    cv::cvtColor(img2, img2, cv::COLOR_BGR2RGB);
    QImage image(img2.size().width, img2.size().height, QImage::Format_RGB888);
    memcpy(image.scanLine(0), img2.data, static_cast<size_t>(image.width() * image.height() * img2.channels()));
    ui->label->setPixmap(QPixmap::fromImage(image));

    preprocessing.loadInput(img2);
    preprocessing.start();

    extraction.loadInput(preprocessingResult);
    extraction.start();
    firstImageLoaded = true;

}

void MainWindow::on_LoadSecondImg_Button_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Select second fingerprint", commonPath);
    ui->label_2->clear();
    img = cv::imread(path.toStdString().c_str());
    img3 = img;
    cv::cvtColor(img3, img3, cv::COLOR_BGR2RGB);
    QImage image(img3.size().width, img3.size().height, QImage::Format_RGB888);
    memcpy(image.scanLine(0), img3.data, static_cast<size_t>(image.width() * image.height() * img3.channels()));
    ui->label_2->setPixmap(QPixmap::fromImage(image));

    preprocessing.loadInput(img3);
    preprocessing.start();

    extraction.loadInput(preprocessingResult);
    extraction.start();
    secondImageLoaded = true;

}

void MainWindow::drawTree(QMap<int,int> commonPoints)
{
    QMap<int, int>::iterator i;
    for (i = commonPoints.begin(); i != commonPoints.end()-1; ++i){
        cv::line(img2, cv::Point(listOfExtractionResults[0].minutiaePredictedFixed[i.key()].xy.x(), listOfExtractionResults[0].minutiaePredictedFixed[i.key()].xy.y()), cv::Point(listOfExtractionResults[0].minutiaePredictedFixed[(i+1).key()].xy.x(), listOfExtractionResults[0].minutiaePredictedFixed[(i+1).key()].xy.y()) ,cv::Scalar(255,255,255),1);
    }
    for (i = commonPoints.begin(); i != commonPoints.end()-1; ++i){
        cv::line(img3, cv::Point(listOfExtractionResults[1].minutiaePredictedFixed[i.value()].xy.x(), listOfExtractionResults[1].minutiaePredictedFixed[i.value()].xy.y()), cv::Point(listOfExtractionResults[1].minutiaePredictedFixed[(i+1).value()].xy.x(), listOfExtractionResults[1].minutiaePredictedFixed[(i+1).value()].xy.y()) ,cv::Scalar(255,255,255),1);
    }

    ui->label->clear();
    ui->label_2->clear();

    QImage image(img2.size().width, img2.size().height, QImage::Format_RGB888);
    memcpy(image.scanLine(0), img2.data, static_cast<size_t>(image.width() * image.height() * img2.channels()));
    ui->label->setPixmap(QPixmap::fromImage(image));

    QImage image2(img3.size().width, img3.size().height, QImage::Format_RGB888);
    memcpy(image2.scanLine(0), img3.data, static_cast<size_t>(image2.width() * image2.height() * img3.channels()));
    ui->label_2->setPixmap(QPixmap::fromImage(image2));
}

QMap<int,int> MainWindow::sortCommonPoints(QMap<int,int> commonPoints){
    QMap<int, int>::iterator i;
    QList<int> sortedFromSecond;
    int j = 0;
    for (i = commonPoints.begin(); i != commonPoints.end(); ++i){
        sortedFromSecond.append(i.value());
    }
    qSort(sortedFromSecond);
    for (i = commonPoints.begin(); i != commonPoints.end(); ++i){
        i.value() = sortedFromSecond.at(j);
        j++;
    }
    return commonPoints;
}

void MainWindow::Result(int numberOfConfirmed){
    int maxNumberOfMinutiae = 0;

    if(listOfExtractionResults[0].minutiaePredictedFixed.size() < listOfExtractionResults[1].minutiaePredictedFixed.size()){
        maxNumberOfMinutiae = listOfExtractionResults[0].minutiaePredictedFixed.size();
    }
    else{
        maxNumberOfMinutiae = listOfExtractionResults[0].minutiaePredictedFixed.size();
    }
    if(numberOfConfirmed > maxNumberOfMinutiae/2){
      ui->label_3->setText("Match Found!");
    }
    else{
      ui->label_3->setText("Match Not Found");
    }
}
void MainWindow::on_matchButton_clicked()
{

        QList<QList<Neighbour>> fiveNearestFromFirstFingerprint, fiveNearestFromSecondFingerprint;
        QMap<int,int> candidateCommonPointList, sortedMap;
        QList<QList<MTuples>>  tuplesFromFirstFingerprint, tuplesFromSecondFingerprint;
        fiveNearestFromFirstFingerprint = distance.getAllEukclidianDistances(listOfExtractionResults[0]);
        fiveNearestFromSecondFingerprint = distance.getAllEukclidianDistances(listOfExtractionResults[1]);
        tuplesFromFirstFingerprint = tuple.createTuples(fiveNearestFromFirstFingerprint);
        tuplesFromSecondFingerprint = tuple.createTuples(fiveNearestFromSecondFingerprint);
        candidateCommonPointList = tuple.matchAllTuples(tuplesFromFirstFingerprint,tuplesFromSecondFingerprint);
        QMap<int,int> sorted = sortCommonPoints(candidateCommonPointList);
        sortedMap = sortCommonPoints(candidateCommonPointList);
        drawTree(sortedMap);
        Result(sorted.size());
        listOfExtractionResults.clear();
}

void MainWindow::on_ExtractMinutiaeFromBoth_button_clicked()
{
    ui->label->clear();
    ui->label_2->clear();
    QMessageBox msgBox;
    if((firstImageLoaded == false || secondImageLoaded == false) || (firstImageLoaded == false && secondImageLoaded == false))
    {
        msgBox.setText("Images are not loaded.");
        msgBox.exec();
        return;
    }
    for(int i = 0; i < 2; i++){
        if(i == 0){
            img = img2;
            img2 = img;
            cv::cvtColor(img2, img2, cv::COLOR_BGR2RGB);
            QImage image(img2.size().width, img2.size().height, QImage::Format_RGB888);
            memcpy(image.scanLine(0), img2.data, static_cast<size_t>(image.width() * image.height() * img2.channels()));
            ui->label->setPixmap(QPixmap::fromImage(image));
        }
        else if(i==1){
            img = img3;
            img3 = img;
            cv::cvtColor(img3, img3, cv::COLOR_BGR2RGB);
            QImage image2(img3.size().width, img3.size().height, QImage::Format_RGB888);
            memcpy(image2.scanLine(0), img3.data, static_cast<size_t>(image2.width() * image2.height() * img3.channels()));
            ui->label_2->setPixmap(QPixmap::fromImage(image2));
        }
    }

}


void MainWindow::on_ScanFinger1_button_clicked()
{
    QMessageBox msgBox;
    img = scanner.scanFinger();
    if(img.empty()){
        msgBox.setWindowTitle("Failure");
        msgBox.setText("Cannot detect fingerprint scanner.");
        msgBox.exec();
        return;
    }
    img2 = img;
    cv::cvtColor(img2, img2, cv::COLOR_BGR2RGB);
    QImage image(img2.size().width, img2.size().height, QImage::Format_RGB888);
    memcpy(image.scanLine(0), img2.data, static_cast<size_t>(image.width() * image.height() * img2.channels()));
    ui->label->setPixmap(QPixmap::fromImage(image));
    preprocessing.loadInput(img2);
    preprocessing.start();
    extraction.loadInput(preprocessingResult);
    extraction.start();
    firstImageLoaded = true;
}

void MainWindow::on_ScanFinger2_button_clicked()
{
    QMessageBox msgBox;
    img = scanner.scanFinger();
    if(img.empty()){
        msgBox.setWindowTitle("Failure");
        msgBox.setText("Cannot detect fingerprint scanner.");
        msgBox.exec();
        return;
    }
    img3 = img;
    cv::cvtColor(img3, img3, cv::COLOR_BGR2RGB);
    QImage image(img3.size().width, img3.size().height, QImage::Format_RGB888);
    memcpy(image.scanLine(0), img3.data, static_cast<size_t>(image.width() * image.height() * img3.channels()));
    ui->label_2->setPixmap(QPixmap::fromImage(image));
    preprocessing.loadInput(img3);
    preprocessing.start();
    extraction.loadInput(preprocessingResult);
    extraction.start();
    secondImageLoaded = true;

}

