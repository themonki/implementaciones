#include "operationarithmetic.h"

OperationArithmetic::OperationArithmetic()
{
}

Image OperationArithmetic::additionValue(Image &image, double add){
    Image imageOuput;

    int height = image.getHeight();
    int width = image.getWidth();
    double level = image.getLevel();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(level);

    matrix grayScaleInput = image.getGraysScale();
    matrix grayScaleOuput = image.getGraysScale();

    for(int i=0; i<height;i++)
    {
        for(int j=0; j<width;j++){

            double value = grayScaleInput[i][j] + add;
            if(value>level){
                value = level;
            }
            grayScaleOuput[i][j] = value;
        }
    }


    imageOuput.setGraysScale(grayScaleOuput);
    return imageOuput;
}

Image OperationArithmetic::subtractionValue(Image &image, double sub){
    Image imageOuput;

    int height = image.getHeight();
    int width = image.getWidth();
    double level = image.getLevel();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(level);

    matrix grayScaleInput = image.getGraysScale();
    matrix grayScaleOuput = image.getGraysScale();

    for(int i=0; i<height;i++)
    {
        for(int j=0; j<width;j++){

            double value = level - fabs(grayScaleInput[i][j] - sub);
            /*if(value<0){//negativo
                value = level+1+value;
            }
            if(value>level){//si por alguna razon
                value = level;
                cerr << "es mayor: operation::subtractionValue" << endl;
            }*/
            grayScaleOuput[i][j] = value;
        }
    }


    imageOuput.setGraysScale(grayScaleOuput);
    return imageOuput;
}

Image OperationArithmetic::multiplicationValue(Image &image, double mul){
    Image imageOuput;

    int height = image.getHeight();
    int width = image.getWidth();
    double level = image.getLevel();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(level);

    matrix grayScaleInput = image.getGraysScale();
    matrix grayScaleOuput = image.getGraysScale();

    for(int i=0; i<height;i++)
    {
        for(int j=0; j<width;j++){

            double value = grayScaleInput[i][j] * mul;
            if(value>level){
                value = level;
            }
            grayScaleOuput[i][j] = value;
        }
    }


    imageOuput.setGraysScale(grayScaleOuput);
    return imageOuput;
}

Image OperationArithmetic::divisionValue(Image &image, double div){
    Image imageOuput;

    int height = image.getHeight();
    int width = image.getWidth();
    double level = image.getLevel();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());

    imageOuput.setLevel(level);

    matrix grayScaleInput = image.getGraysScale();
    matrix grayScaleOuput = image.getGraysScale();

    for(int i=0; i<height;i++)
    {
        for(int j=0; j<width;j++){

           grayScaleOuput[i][j] = grayScaleInput[i][j] / div;
        }
    }


    imageOuput.setGraysScale(grayScaleOuput);
    return imageOuput;
}

Image OperationArithmetic::additionImages(Image &image1, Image &image2, double alfa){

    Image imageOuput;
    if(image1.getHeight()!=image2.getHeight() || image1.getWidth()!=image2.getWidth() ){

        cerr << "error no se pueden sumar";
        return imageOuput;
    }


    int height = image1.getHeight();
    int width = image1.getWidth();
    double level = image1.getLevel();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image1.getType());
    imageOuput.setLevel(level);

    matrix grayScaleInput1 = image1.getGraysScale();
    matrix grayScaleInput2 = image2.getGraysScale();
    matrix grayScaleOuput = image1.getGraysScale();

    for(int i=0; i<height;i++)
    {
        for(int j=0; j<width;j++){
            double value = alfa*grayScaleInput1[i][j] + (1-alfa)* grayScaleInput2[i][j];

            if(value>level){
                value=level;
            }

            grayScaleOuput[i][j] = value;
        }
    }


    imageOuput.setGraysScale(grayScaleOuput);
    return imageOuput;
}
