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
    void saveImage(QString);
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
    void applyFilterCleaningPixel(double);
    void applyFilterCleaningLine(double);
    void applyContrastCorrectionGamma(double r);
    void applyContrastStretching();
    void applyContrastImprove(int option);
    void applyEqualizer();
    QImage getHistogram();
    void getThresholdingDosPicos();
    void getThresholdingOtsu();
    void getThresholdingIsodata();
    bool isDicomImage();
    bool isppmImage();
    void clearAll();

};

#endif // CONTROLER_H
