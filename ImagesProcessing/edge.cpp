
#include "edge.h"

#include "math.h"

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


Image Edge::applySobel(Image &image){
    Image imageOuput;
    int height = image.getHeight();
    int width = image.getWidth();
    int level = image.getLevel();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(image.getLevel());

    matrix grayScaleInput = image.getGraysScale();
    matrix grayScaleOuput = image.getGraysScale();


    for (int i=0; i < height; i++ ){
        for (int j=0; j < width; j++ ){
            if(i==0 || j==0 || i==height-1 || j==width-1){// si son los bordes de la imagen completa
                grayScaleOuput[i][j]=0;
            }else{
                double valueX=0, valueY=0;
                valueX += grayScaleInput[i-1][j-1]*Sx[0][0];
                valueY += grayScaleInput[i-1][j-1]*Sy[0][0];


                valueX += grayScaleInput[i-1][j]*Sx[0][1];
                valueY += grayScaleInput[i-1][j]*Sy[0][1];

                valueX += grayScaleInput[i-1][j+1]*Sx[0][2];
                valueY += grayScaleInput[i-1][j+1]*Sy[0][2];

                valueX += grayScaleInput[i][j-1]*Sx[1][0];
                valueY += grayScaleInput[i][j-1]*Sy[1][0];

                valueX += grayScaleInput[i][j]*Sx[1][1];
                valueY += grayScaleInput[i][j]*Sy[1][1];

                valueX += grayScaleInput[i][j+1]*Sx[1][2];
                valueY += grayScaleInput[i][j+1]*Sy[1][2];

                valueX += grayScaleInput[i+1][j-1]*Sx[2][0];
                valueY += grayScaleInput[i+1][j-1]*Sy[2][0];

                valueX += grayScaleInput[i+1][j]*Sx[2][1];
                valueY += grayScaleInput[i+1][j]*Sy[2][1];

                valueX += grayScaleInput[i+1][j+1]*Sx[2][2];
                valueY += grayScaleInput[i+1][j+1]*Sy[2][2];

                //double value =  level - (fabs(valueY/8) + fabs(valueX/8));//blanco
                double value =  (fabs(valueY/8) + fabs(valueX/8));//negro
                if(value > level){
                    value = level;
                }
                grayScaleOuput[i][j] = value;
            }
        }
    }

    imageOuput.setGraysScale(grayScaleOuput);
    return imageOuput;
}
