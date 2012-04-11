#ifndef CONTRAST_H
#define CONTRAST_H

#include <histogram.h>

class Contrast
{

private:
    int minimunLevel;
    int maximunLevel;
    double contrast;
    vectorx lookUpTable;
    void obtainContrast(Image& image);
public:
    Contrast();

    vectorx getLookUpTable();
    double getContrast();
    int getMinimunLevel();
    int getMaximulLevel();



    void setLookUpTable(vectorx lookUpTable);
    void setContrast(double contrast);
    void setMinimunLevel(int minimunLevel);
    void setMaximunLevel(int maximunLevel);


    Image gammaCorrection(Image& image, double r);
    Image contrastExpansion(Image& image);
    Image improveContrast(Image& image, int option);
    Image applyEqulizer(Image& image);


};

#endif // CONTRAST_H
