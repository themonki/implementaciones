#ifndef SEGMENTATION_H
#define SEGMENTATION_H
#include "image.h"

class segmentation
{
public:
    segmentation();
    Image kmeans(int k, Image &image);
};

#endif // SEGMENTATION_H
