#ifndef IMAGE_H
#define IMAGE_H


#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>

using namespace std;


typedef vector<vector <double> > matrix;

class Image
{
private:

    int width;
    int heigh;
    int level;
    matrix red;
    matrix blue;
    matrix green;
    matrix graysScale;
    string type;
    string path;
    void readImage();

public:
    Image(string path);

    int getWidth();
    int getheight();
    int getLevel();

    void setWidth();
    void setHeight();
    void setLevel();

    matrix getRed();
    matrix getBlue();
    matrix getGreen();
    matrix getGraysScale();

    void getRed(matrix red);
    void getBlue(matrix blue);
    void getGreen(matrix green);
    void getGraysScale(matrix graysScale);


    string getType();
    void setType(string type);

};

#endif // IMAGE_H
