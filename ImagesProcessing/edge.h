#ifndef EDGE_H
#define EDGE_H

#include "image.h"
#include <math.h>
#include "filter.h"


#define PI 3.14159265
#define RECT_ANGLE 1.57079633;

const double Sx [3][3] ={{-1,-2,-1},{0,0,0},{1,2,1}} , Sy [3][3]= {{-1,0,1},{-2,0,2},{-1,0,1}};

class Edge
{
public:
    Edge();
    ~Edge();
    Image getProfileIntensityOnY(Image& img, int lineY);
    Image calcGradient(Image& img,const double gX[][3], const double gY[][3]);
    Image applySobelDetection(Image& img, double threshold);
    Image applyCannyDetector(Image& img, double, double);
    matrix nonMaximumSuppression(int,int);
    matrix hysteresis(int,int, double, double);
    double convolution(matrix& img, int posX, int posY,const double kernel[][3]);
    int edgeDetection(int posX, int posY, int heigth, int width, double thresholdHigh, double thresholdsDown );


private:
    matrix dx;
    matrix dy;
    matrix gradientMagnitude;
    matrix gradientDegree;// el angulo del gradiente
    matrix gradientOrientationDiscret;//las direcciones del gradiente discretisadas en 0,1,2,3
    matrix gradientDegreeDiscret;//los angulos discretizados
    matrix edgeNonMaximumSuppression;//la imagen con non-maximum supression aplicada
    matrix edgeHysteresis;// contiene la imagen con los bordes al aplicar canny
    matrix edgeControl;// para saber si ya se visito

    double discretDegree(double);
    double discretOrientation(double);


};

#endif // EDGE_H
