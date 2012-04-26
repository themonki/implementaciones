#ifndef CONTROLER_H
#define CONTROLER_H

#include <QImage>
#include <QColor>
#include <QString>
#include <QDir>
#include "image.h"
#include "filter.h"
#include "histogram.h"


class Controler
{
private:
    Image* imageIn;
    Image* imageOut;
    QImage imageInLabel;
    QImage imageOutLabel;
    QImage convertImageIn();
    QImage convertImageOut();
    QImage convertImage(Image&, QImage&);
    bool ppmImage;
    bool dicomImage;
public:
    Controler();
    void openImage(QString);
    void saveImage(QString, QImage);
    void setImageIn(QImage);
    void setImageOut(QImage);
    QImage getImageIn();
    QImage getImageOut();
    void applyFilterSigma(int sigma);
    void applyFilterMedian(int);
    QImage getHistogram();
    bool isDicomImage();
    bool isppmImage();

};

#endif // CONTROLER_H
