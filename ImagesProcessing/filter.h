#ifndef FILTER_H
#define FILTER_H
#include<image.h>

class Filter
{
public:
    Filter();
    Image medianFilter(Image& image, int n);
    Image sigmaFilter(Image& image, int sigma);
};

#endif // FILTER_H
