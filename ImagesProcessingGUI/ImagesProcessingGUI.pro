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
    imageexeption.cpp

HEADERS  += mainwindow.h \
    image.h \
    controler.h \
    imageexeption.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -DHAVE_CONFIG_H

unix:!macx:!symbian: LIBS += -ldcmimgle

unix:!macx:!symbian: LIBS += -ldcmdata

unix:!macx:!symbian: LIBS += -loflog

unix:!macx:!symbian: LIBS += -lofstd

unix:!macx:!symbian: LIBS += -lz
