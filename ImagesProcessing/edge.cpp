
#include "edge.h"

#include "math.h"

Edge::Edge()
{
}

Edge::~Edge()
{
    /*this->dx.~vector();
    this->dy.~vector();
    this->edgeHysteresis.~vector();
    this->edgeNonMaximumSuppression.~vector();
    this->gradientOrientationDiscret.~vector();
    this->gradientDirection.~vector();
    this->gradientDirectionDiscret.~vector();
    this->gradientMagnitude.~vector();
    */
}


Image Edge::getProfileIntensityOnY(Image &img, int lineY){
    Image outPut;

    int height= img.getLevel();
    int width = img.getWidth();

    if(lineY<0 && lineY> img.getHeight()){
        cerr << "error";
        return img;
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


Image Edge::applySobelDetection(Image &image){
    return calcGradient(image);
}

Image Edge::calcGradient(Image &image){
    Image imageOuput;
    int height = image.getHeight();
    int width = image.getWidth();
    int level = image.getLevel();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(level);

    matrix grayScaleInput = image.getGraysScale();
    matrix grayScaleOuput = image.getGraysScale();

    if(this->dx.size()!=(unsigned)height){
        this->dx = grayScaleInput;
        this->dy = grayScaleInput;

    }
    if(this->gradientMagnitude.size()!=(unsigned)height){
        this->gradientMagnitude = grayScaleInput;
        this->gradientDirection = grayScaleInput;
        this->gradientDirectionDiscret = grayScaleInput;
        this->gradientOrientationDiscret = grayScaleInput;
    }

    for (int i=0; i < height; i++ ){
        for (int j=0; j < width; j++ ){
            if(i==0 || j==0 || i==height-1 || j==width-1){// si son los bordes de la imagen completa
                grayScaleOuput[i][j]=0;
                this->dx[i][j]=0;
                this->dy[i][j]=0;
                this->gradientMagnitude[i][j]=0;
                this->gradientDirection[i][j]=0;
                this->gradientDirectionDiscret[i][j]=0;
                this->gradientOrientationDiscret[i][j]=0;


            }else{
                double valueX=0, valueY=0, dx, dy, degree;
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

                dx = fabs(valueX/8);
                dy = fabs(valueY/8);

                degree = atan2(dy, dx);

                if(degree<0){
                    cerr << "noc"<<endl;
                    degree= fabs(degree);
                }
                double value =  (dy + dx);
                //double value = level - (dy + dx);
                if(value > level){
                    value = level;
                }
                this->dx[i][j]= dx;
                this->dy[i][j]= dy;
                this->gradientMagnitude[i][j]=value;
                this->gradientDirection[i][j]= degree;
                this->gradientOrientationDiscret[i][j]=discretDegree(degree);
                this->gradientDirectionDiscret[i][j]= discretDirection(degree);
                grayScaleOuput[i][j] = value;

            }
        }
    }
    /*
    imageOuput.setGraysScale(dx);    
    imageOuput.saveImage("../ImagenesPrueba/dx.pgm");
    imageOuput.setGraysScale(dy);
    imageOuput.saveImage("../ImagenesPrueba/dy.pgm");
    imageOuput.setGraysScale(gradientMagnitude);
    imageOuput.saveImage("../ImagenesPrueba/gradientMagnitude.pgm");
    imageOuput.setGraysScale(this->gradientDirection);
    imageOuput.setLevel(2*PI);
    imageOuput.saveImage("../ImagenesPrueba/gradientOrientation.pgm");
    imageOuput.setGraysScale(this->gradientOrientationDiscret);
    imageOuput.saveImage("../ImagenesPrueba/gradientOrientationDiscret.pgm");

    imageOuput.setLevel(level);
    /**/
    imageOuput.setGraysScale(grayScaleOuput);
    return imageOuput;
}

double Edge::discretDegree(double value){
    double degree = value * 180 / PI;

    if(degree>=360){
        cerr << "error discret" << endl;
    }

    if(degree >= 22.5 && degree < 67.5 ){//45   1
        return 1;
        //return 45*PI/180;
    }else if(degree >= 67.5 && degree < 112.5 ){//90   2
        return 2;
        //return 90*PI/180;
    }else if(degree >= 112.5 && degree < 157.5 ){//135  3
        return 3;
        //return 135*PI/180;
    }else if(degree >= 157.5 && degree < 202.5 ){//180   0
        return 0;
        //return 135*PI/180;
    }else if(degree >= 202.5 && degree < 247.5 ){//225   1
        return 1;
        //return 135*PI/180;
    }else if(degree >= 247.5 && degree < 292.5 ){//270   2
        return 2;
        //return 135*PI/180;
    }else if(degree >= 292.5 && degree < 337.5 ){//315   3
        return 3;
        //return 135*PI/180;
    }else if((degree >= 337.5 && degree < 360) || (degree>=0 && degree < 22.5) ){//0   0
        return 0;
        //return 135*PI/180;
    }

    cerr << "no entro discret" << endl;
    return -1;

}

double Edge::discretDirection(double value){
    double degree = value * 180 / PI;

    if(degree>=360){
        cerr << "error discret" << endl;
    }

    if(degree >= 22.5 && degree < 67.5 ){//45   1
        //return 1;
        return 45*PI/180;
    }else if(degree >= 67.5 && degree < 112.5 ){//90   2
        //return 2;
        return 90*PI/180;
    }else if(degree >= 112.5 && degree < 157.5 ){//135  3
        //return 3;
        return 135*PI/180;
    }else if(degree >= 157.5 && degree < 202.5 ){//180   0
        //return 0;
        return 135*PI/180;
    }else if(degree >= 202.5 && degree < 247.5 ){//225   1
        //return 1;
        return 135*PI/180;
    }else if(degree >= 247.5 && degree < 292.5 ){//270   2
        //return 2;
        return 135*PI/180;
    }else if(degree >= 292.5 && degree < 337.5 ){//315   3
        //return 3;
       return 135*PI/180;
    }else if((degree >= 337.5 && degree < 360) || (degree>=0 && degree < 22.5) ){//0   0
        //return 0;
        return 135*PI/180;
    }

    cerr << "no entro discret" << endl;
    return -1;

}

Image Edge::applyCannyDetector(Image &image){
    Image imageOuput;
    int height = image.getHeight();
    int width = image.getWidth();
    int level = image.getLevel();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(level);

    matrix grayScaleInput = image.getGraysScale();
    matrix grayScaleOuput = grayScaleInput;
    this->dx = grayScaleInput;
    this->dy = grayScaleInput;
    this->gradientMagnitude = grayScaleInput;
    this->gradientDirection = grayScaleInput;
    this->gradientOrientationDiscret = grayScaleInput;

    calcGradient(image);
    nonMaximumSuppression(height, width);
    hysteresis(height, width, 100, 15);

    /*imageOuput.setGraysScale(this->edgeNonMaximumSuppression);
    imageOuput.saveImage("../ImagenesPrueba/nonmaxsup.pgm");*/

    imageOuput.setGraysScale(grayScaleOuput);
    return imageOuput;
}

matrix Edge::nonMaximumSuppression(int height, int width){
    this->edgeNonMaximumSuppression = this->gradientMagnitude;


    for(int i = 0 ; i< height;i++ ){
        for(int j = 0 ; j< width;j++ ){

            int orientation = (int)this->gradientOrientationDiscret[i][j];
            double valueGradient = this->gradientMagnitude[i][j];
            switch(orientation){
            case 0:
                if(i==0){
                    if(valueGradient < this->gradientMagnitude[i+1][j]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }

                }else if(i==height-1){
                    if(valueGradient < this->gradientMagnitude[i-1][j]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }
                }else{
                    if(valueGradient < this->gradientMagnitude[i+1][j] || valueGradient < this->gradientMagnitude[i-1][j]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }
                }
                break;
            case 1:
                if((i == height-1) && (j==0)){
                    if(valueGradient < this->gradientMagnitude[i-1][j+1]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }

                }else if((i == 0) && (j==height-1)){
                    if(valueGradient < this->gradientMagnitude[i+1][j-1]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }
                }else{
                    if(valueGradient < this->gradientMagnitude[i+1][j-1] || valueGradient < this->gradientMagnitude[i-1][j+1]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }
                }
                break;
            case 2:
                if(j==0){
                    if(valueGradient < this->gradientMagnitude[i][j+1]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }

                }else if(j==height-1){
                    if(valueGradient < this->gradientMagnitude[i][j-1]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }
                }else{
                    if(valueGradient < this->gradientMagnitude[i][j+1] || valueGradient < this->gradientMagnitude[i][j-1]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }
                }
                break;
            case 3:
                if((i == 0) && (j==0)){
                    if(valueGradient < this->gradientMagnitude[i+1][j+1]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }

                }else if((i == height-1) && (j==height-1)){
                    if(valueGradient < this->gradientMagnitude[i-1][j-1]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }
                }else{
                    if(valueGradient < this->gradientMagnitude[i+1][j+1] || valueGradient < this->gradientMagnitude[i-1][j-1]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }
                }
                break;

            }

        }
    }

    return edgeNonMaximumSuppression;

}


matrix Edge::hysteresis(int heigth, int width, double thresholdHigh, double thresholdsDown ){
    this->edgeHysteresis = this->edgeNonMaximumSuppression;
    for(int i = 0; i < heigth; i++){
        for(int j = 0; j < width ; j++){

        }
    }
    return this->edgeHysteresis;
}
