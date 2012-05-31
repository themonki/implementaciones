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
#include "operationarithmetic.h"
#include "edge.h"


class Controler
{
private:
    Image* imageIn;
    Image* imageOut;
    Image* histogramIn;
    Image* histogramOut;
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
    QImage gethistogramInLabel();
    QImage applyConvertToGrayScale(Image* img, QImage labelImage);
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
    void applyOperationAddValue(double value);
    void applyOperationDivValue(double value);
    void applyOperationSubValue(double value);
    void applyOperationMulValue(double value);
    void applyOperationAddImage(Image in , double value);
    void applyOperationInvertImage();
    bool isDicomImage();
    bool isppmImage();
    void clearAll();
    void applyEdgeDetectorSobel(double threshold);
    void applyEdgeDetectorCanny(double thresholdHigh, double thresholdsDown);
    void applyDicomWindow();
    void applyDicomLevel();

};

#endif // CONTROLER_H
