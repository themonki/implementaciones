#include "edge.h"

Edge::Edge()
{
}


Image Edge::getProfileIntensityOnY(Image &img, int lineY){
    Image outPut;

    int height= img.getLevel();
    int width = img.getWidth();

    if(lineY<0 && lineY> img.getHeight()){
        cerr << "error";
    }

    outPut.setLevel(1);
    outPut.setHeight(height);
    outPut.setType("P2");
    outPut.setWidth(width);

    matrix grayOutPut;
    matrix grayImageIn = img.getGraysScale();

    grayOutPut.resize(height);
    for(int i=0; i<height; i++){
        grayOutPut[i].resize(width);
        for(int j = 0 ; j < width; j++){
            grayOutPut[i][j]=1;
        }
    }

    for(int i= 0; i < width;i++){
        grayOutPut[grayImageIn[lineY][i]][i] = 0;
        //se lee width luego heigth
        //la matriz tiene heigth luego width
    }


    outPut.setGraysScale(grayOutPut);

    return outPut;
}
