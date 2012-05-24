#include "operationgeometric.h"
#include <math.h>
OperationGeometric::OperationGeometric()
{
}

Image OperationGeometric::scaleBilinearGray(Image& image, double scale){

    Image imageOuput;

    int height = image.getHeight();
    int width = image.getWidth();

    int h2 = height*scale, w2= width*scale;
    //cerr <<height <<" - "<< height<< endl;

    imageOuput.setHeight(h2);
    imageOuput.setWidth(w2);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(image.getLevel());

    matrix grayScaleInput = image.getGraysScale();
    matrix grayScaleOuput;

    grayScaleOuput.resize(h2);

    double A, B, C, D;
    int x, y ;

    double x_ratio = ((double)(width-1))/w2 ;
    double y_ratio = ((double)(height-1))/h2 ;
    double floor_x, floor_y, gray;

    for (int i=0;i<h2;i++) {
        for (int j=0;j<w2;j++) {
            grayScaleOuput[i].resize(w2);

            x = (int)(x_ratio * j) ;
            y = (int)(y_ratio * i) ;
            floor_x = (x_ratio * j) - x ;
            floor_y = (y_ratio * i) - y ;


            // range is 0 to 255 thus bitwise AND with 0xff
            A = grayScaleInput[y][x] ;
            B = grayScaleInput[y+1][x] ;
            C = grayScaleInput[y][x+1];
            D = grayScaleInput[y+1][x+1];

            // Y = A(1-w)(1-h) + B(w)(1-h) + C(h)(1-w) + Dwh
            gray = (double)(
                        A*(1-floor_x)*(1-floor_y) +  B*(floor_x)*(1-floor_y) +
                        C*(floor_y)*(1-floor_x)   +  D*(floor_x*floor_y)
                        ) ;


            if(gray>imageOuput.getLevel()){gray = imageOuput.getLevel();}
            if(gray<0){gray = 0;}
            grayScaleOuput[i][j]=gray;

        }
    }

    imageOuput.setGraysScale(grayScaleOuput);

    return imageOuput;

}
