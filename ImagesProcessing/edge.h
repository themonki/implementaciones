#ifndef EDGE_H
#define EDGE_H

#include "image.h"


const double Sx [3][3] ={{-1,-2,-1},{0,0,0},{1,2,1}} , Sy [3][3]= {{-1,0,1},{-2,0,2},{-1,0,1}};


class Edge
{
public:
    Edge();
    Image getProfileIntensityOnY(Image& img, int lineY);
    Image applySobel(Image& img);

};

#endif // EDGE_H
