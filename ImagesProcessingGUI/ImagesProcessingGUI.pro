#-------------------------------------------------
#
# Project created by QtCreator 2012-04-25T17:09:40
#
#-------------------------------------------------

QT       += core gui

TARGET = ImagesProcessingGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    image.cpp \
    controler.cpp \
    imageexeption.cpp \
    filter.cpp \
    histogram.cpp \
    thresholding.cpp \
    contrast.cpp \
    imageviewer.cpp \
    operationarithmetic.cpp \
    operationgeometric.cpp \
    operationlogic.cpp \
    imagedcm.cpp \
    edge.cpp

HEADERS  += mainwindow.h \
    image.h \
    controler.h \
    imageexeption.h \
    filter.h \
    histogram.h \
    thresholding.h \
    contrast.h \
    imageviewer.h \
    operationarithmetic.h \
    operationgeometric.h \
    operationlogic.h \
    imagedcm.h \
    edge.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -DHAVE_CONFIG_H

unix:!macx:!symbian: LIBS += -ldcmimgle

unix:!macx:!symbian: LIBS += -ldcmdata

unix:!macx:!symbian: LIBS += -loflog

unix:!macx:!symbian: LIBS += -lofstd

unix:!macx:!symbian: LIBS += -lz

OTHER_FILES +=

RESOURCES +=
