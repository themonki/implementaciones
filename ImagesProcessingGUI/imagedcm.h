#ifndef IMAGEDCM_H
#define IMAGEDCM_H


#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "image.h"
#include <QFile>

typedef vector<double> vectorx;

class ImageDCM : public Image{
private:

    DicomImage *dicomImage;
    //matrix graysScale;
    vectorx lookUpTable;
    int lutSize;
    double minimunDensity;
    double maximunDensity;



    int getDensity(int x, int y);
    int appyCalibrationFunction(int pixelValue, int rescaleSlope, int rescaleIntercept);

public:

    ImageDCM(const char *fileName);
    void applyWindowLevel(int window, int level);




};

#endif // IMAGEDCM_H
