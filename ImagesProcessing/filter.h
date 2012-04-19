#ifndef FILTER_H
#define FILTER_H
#include<image.h>

class Filter
{
public:
    Filter();
    Image medianFilter(Image& image, int n);
    Image sigmaFilter(Image& image, int sigma);
    Image nagao_MatsuyamaFilter(Image& image, int win);

};

#endif // FILTER_H
