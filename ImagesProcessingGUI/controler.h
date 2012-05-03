#ifndef CONTROLER_H
#define CONTROLER_H

#include <QImage>
#include <QColor>
#include <QString>
#include <QDir>
#include "image.h"
#include "filter.h"
#include "histogram.h"
#include "contrast.h"
#include "thresholding.h"


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
    void setImageIn(Image*);
    void setImageOut(Image*);
    void setImageInLabel(QImage);
    void setImageOutLabel(QImage);
    Image* getImageIn();
    Image* getImageOut();
    QImage getImageInLabel();
    QImage getImageOutLabel();
    void applyFilterSigma(int sigma);
    void applyFilterMedian(int);
    void applyContrastCorrectionGamma(double r);
    void applyContrastExpansion();
    void applyContrastImprove(int option);
    void applyEqualizer();
    QImage getHistogram();
    bool isDicomImage();
    bool isppmImage();
    void clearAll();

};

#endif // CONTROLER_H
