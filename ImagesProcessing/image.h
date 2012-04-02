#ifndef IMAGE_H
#define IMAGE_H


#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "imageexeption.h"

using namespace std;


typedef vector<vector <double> > matrix;

class Image
{
private:

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
    int round(double number);

public:
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

    void colorToGraysScale();

    bool isRangeLevel(int);

    matrix scaleImage(int, int);

};

#endif // IMAGE_H
