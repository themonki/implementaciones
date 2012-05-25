#ifndef EDGE_H
#define EDGE_H

#include "image.h"
#include <math.h>


#define PI 3.14159265

const double Sx [3][3] ={{-1,-2,-1},{0,0,0},{1,2,1}} , Sy [3][3]= {{-1,0,1},{-2,0,2},{-1,0,1}};

class Edge
{
public:
    Edge();
    ~Edge();
    Image getProfileIntensityOnY(Image& img, int lineY);
    Image calcGradient(Image& img);
    Image applySobelDetection(Image& img);
    Image applyCannyDetector(Image& img);
    matrix nonMaximumSuppression(int,int);
    matrix hysteresis(int,int, double, double);



private:
    matrix dx;
    matrix dy;
    matrix gradientMagnitude;
    matrix gradientDirection;
    matrix gradientOrientationDiscret;
    matrix gradientDirectionDiscret;
    matrix edgeNonMaximumSuppression;
    matrix edgeHysteresis;

    double discretDegree(double);
    double discretDirection(double);


};

#endif // EDGE_H
