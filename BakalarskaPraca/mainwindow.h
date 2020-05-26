#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Python.h>
#include <QMainWindow>
#include "preprocessing.h"
#include "extraction.h"
#include "ftrScanAPI.h"
#include "structures.h"
#include "angles.h"
#include "filesoperations.h"
#include "futronic.h"
#include "nearestneighbour.h"
#include "tuples.h"
#include "euclideandistance.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    FTRSCAN_IMAGE_SIZE ImageSize;
    unsigned char *pBuffer;


private:
    Ui::MainWindow *ui;
    Preprocessing preprocessing;
    Angles angle;
    FilesOperations fileOperation;
    EuclideanDistance distance;
    Futronic scanner;
    NearestNeighbour neighbour;
    Tuples tuple;

    Extraction extraction;
    PREPROCESSING_RESULTS preprocessingResult;
    EXTRACTION_RESULTS extractionResult;
    QList<EXTRACTION_RESULTS> listOfExtractionResults;
    QVector<int> labels;
    cv::Mat img;
    cv::Mat img2;
    cv::Mat img3;
    bool firstImageLoaded = false;
    bool secondImageLoaded = false;
    QString commonPath = "/home/"; //

    QString pathToFingerprints = "/home/filip/Downloads/FVC_Fingerprint_DB/FVC2004/DB3_A";




private slots:
    void preprocessingResultsSlot(PREPROCESSING_RESULTS);
    void extractionResultsSlot(EXTRACTION_RESULTS results);
    //void drawConnections(QList<QPoint> listOfPoints);
    void on_FillDataToMatrix_Button_clicked();
    void on_SaveData_Button_clicked();
    void on_ExtractDataFromFingerprint_Button_clicked();
    void on_Compare_Button_clicked();
    void on_LoadfirstImg_Button_clicked();
    void on_LoadSecondImg_Button_clicked();
    void on_matchButton_clicked();
    void drawTree(QMap<int,int> commonPoints);
    QMap<int,int> sortCommonPoints(QMap<int,int> commonPoints);
    void Result(int numberOfConfirmed);
    void on_ExtractMinutiaeFromBoth_button_clicked();
    void on_ScanFinger1_button_clicked();
    void on_ScanFinger2_button_clicked();
    void on_ConstructTestDataset_clicked();
    void on_ExtractDataFromFingerprintsDB_Button_clicked();
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
