#ifndef IMAGE_H
#define IMAGE_H


#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"  /* gcc 3.4 needs this */
#include "imageexeption.h"

using namespace std;

const double Wr=0.299, Wg=0.587, Wb=0.114;// Umax=0.436, Vmax=0.615; //Definicion de constantes

typedef vector<vector <double> > matrix;

class Image
{
protected:

    int width;
    int height;
    int level;
    matrix red;
    matrix blue;
    matrix green;
    matrix graysScale;
    string type;
    string path;
    void readImage();

public:
    Image();
    Image(string path);

    int getWidth();
    int getHeight();
    int getLevel();

    void setWidth(int width);
    void setHeight(int height);
    void setLevel(int level);

    matrix getRed();
    matrix getBlue();
    matrix getGreen();
    matrix getGraysScale();

    void setRed(matrix red);
    void setBlue(matrix blue);
    void setGreen(matrix green);
    void setGraysScale(matrix graysScale);


    string getType();
    void setType(string type);

    void saveImage(string path);

    void readDicomImage(string path);

    void colorToGraysScale();

    bool isRangeLevel(int);

    matrix scaleImage(int, int);

    int round(double number);

    void clearImage();


};

#endif // IMAGE_H
