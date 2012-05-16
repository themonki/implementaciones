#ifndef EDGE_H
#define EDGE_H

#include "image.h"

class Edge
{
public:
    Edge();
    Image getProfileIntensityOnY(Image& img, int lineY);
};

#endif // EDGE_H
