QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BakalarskaPraca
TEMPLATE = app


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CFLAGS_ISYSTEM=
CONFIG += c++11

SOURCES += \
    angles.cpp \
    euclideandistance.cpp \
    filesoperations.cpp \
    futronic.cpp \
    main.cpp \
    mainwindow.cpp \
    nearestneighbour.cpp \
    tuples.cpp

HEADERS += \
    angles.h \
    euclideandistance.h \
    filesoperations.h \
    futronic.h \
    mainwindow.h \
    nearestneighbour.h \
    structures.h \
    tuples.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/../openfinger-preprocessor
DEPENDPATH += $$PWD/../openfinger-preprocessor

INCLUDEPATH += $$PWD/../openfinger-extractor
DEPENDPATH += $$PWD/../openfinger-extractor

#CUDA
unix:!macx: LIBS += -L/opt/cuda/lib64/ -lcudart
INCLUDEPATH += /opt/cuda/include
DEPENDPATH += /opt/cuda/include

#ArrayFire
unix:!macx: LIBS += -L/usr/lib64/ -lafcuda
INCLUDEPATH += /usr/include
DEPENDPATH += /usr/include

#OpenCV
unix:!macx: LIBS += -L/usr/lib64/ -lopencv_core
unix:!macx: LIBS += -L/usr/lib64/ -lopencv_imgproc
unix:!macx: LIBS += -L/usr/lib64/ -lopencv_imgcodecs
unix:!macx: LIBS += -L/usr/lib64/ -lopencv_highgui
INCLUDEPATH += /usr/include/opencv4

#caffe
unix:!macx: LIBS += -L/usr/lib64/ -lcaffe

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-Preprocessing-Desktop-Debug/release/ -lPreprocessing
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-Preprocessing-Desktop-Debug/debug/ -lPreprocessing
else:unix: LIBS += -L$$PWD/../build-Preprocessing-Desktop-Debug/ -lPreprocessing

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-Extraction-Desktop-Debug/release/ -lExtraction
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-Extraction-Desktop-Debug/debug/ -lExtraction
else:unix: LIBS += -L$$PWD/../build-Extraction-Desktop-Debug/ -lExtraction


#libscan
#unix:!macx: LIBS += -L$$PWD/./ -lScanAPI

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

unix:!macx: LIBS += -L$$PWD/./ -lScanAPI
unix:!macx: LIBS += -L$$PWD/../../../BP/libScanAPI_Linux_Src_v10.7.3.504/linux_x86_64bit/ -lScanAPI

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

#python
#INCLUDEPATH += /usr/include/python2.7
#DEPENDPATH += /usr/include
#unix:!macx: LIBS += -lpython2.7
#unix:!macx: LIBS += -L /usr/lib/ -lpython3.8
#INCLUDEPATH += /usr/include/python3.8
#DEPENDPATH += /usr/include/python3.8

INCLUDEPATH += /home/filip/anaconda3/include/python3.7m
INCLUDEPATH += /home/filip/anaconda3/bin/python3.7m
unix:!macx: LIBS += -L/home/filip/anaconda3/lib/ -lpython3.7m


