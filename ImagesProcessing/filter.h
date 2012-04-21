#ifndef FILTER_H
#define FILTER_H
#include<image.h>

using namespace std;

class Filter
{
public:
    Filter();
    Image medianFilter(Image& image, int n);
    Image sigmaFilter(Image& image, int sigma);
    Image nagao_MatsuyamaFilter(Image& image, int win);
    double* calculateVariance(matrix grayScaleInput, int posPixelX, int posPixelY, int win, int dif, int subwind);

};

#endif // FILTER_H
