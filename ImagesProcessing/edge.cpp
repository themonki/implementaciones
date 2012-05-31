
#include "edge.h"
#include "operationarithmetic.h"
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


Image Edge::applySobelDetection(Image &image, double threshold){
    Filter f;
    image = f.medianFilter(image,3);

    Image imageOuput;
    int height = image.getHeight();
    int width = image.getWidth();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(1);

    matrix grayScaleOuput = image.getGraysScale();

    calcGradient(image,Sx,Sy);

    for(int i =0;i < height;i++){
        for(int j  = 0; j< width; j++){
            if(this->gradientMagnitude[i][j]>threshold){
                grayScaleOuput[i][j]=0;
            }else{
                grayScaleOuput[i][j]=1;
            }
        }
    }
    imageOuput.setGraysScale(grayScaleOuput);

    return imageOuput;
}

Image Edge::calcGradient(Image &image, const double gX[][3], const double gY[][3]){
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
        this->gradientDegree = grayScaleInput;
        this->gradientDegreeDiscret = grayScaleInput;
        this->gradientOrientationDiscret = grayScaleInput;
    }

    for (int i=0; i < height; i++ ){
        for (int j=0; j < width; j++ ){
            this->edgeControl[i][j]=0;
            this->edgeHysteresis[i][j]=1;
            if(i==0 || j==0 || i==height-1 || j==width-1){// si son los bordes de la imagen completa
                grayScaleOuput[i][j]=0;
                this->dx[i][j]=0;
                this->dy[i][j]=0;
                this->gradientMagnitude[i][j]=0;
                this->gradientDegree[i][j]=0;
                this->gradientDegreeDiscret[i][j]=0;
                this->gradientOrientationDiscret[i][j]=0;
            }else{
                double valueX=0, valueY=0, dx, dy, degree;
                /*valueX += grayScaleInput[i-1][j-1]*gX[0][0];
                valueY += grayScaleInput[i-1][j-1]*gY[0][0];


                valueX += grayScaleInput[i-1][j]*gX[0][1];
                valueY += grayScaleInput[i-1][j]*gY[0][1];

                valueX += grayScaleInput[i-1][j+1]*gX[0][2];
                valueY += grayScaleInput[i-1][j+1]*gY[0][2];

                valueX += grayScaleInput[i][j-1]*gX[1][0];
                valueY += grayScaleInput[i][j-1]*gY[1][0];

                valueX += grayScaleInput[i][j]*gX[1][1];
                valueY += grayScaleInput[i][j]*gY[1][1];

                valueX += grayScaleInput[i][j+1]*gX[1][2];
                valueY += grayScaleInput[i][j+1]*gY[1][2];

                valueX += grayScaleInput[i+1][j-1]*gX[2][0];
                valueY += grayScaleInput[i+1][j-1]*gY[2][0];

                valueX += grayScaleInput[i+1][j]*gX[2][1];
                valueY += grayScaleInput[i+1][j]*gY[2][1];

                valueX += grayScaleInput[i+1][j+1]*gX[2][2];
                valueY += grayScaleInput[i+1][j+1]*gY[2][2];
                */

                valueX=convolution(grayScaleInput, i, j, gX);
                valueY=convolution(grayScaleInput, i, j, gY);

                dx = fabs(valueX);
                dy = fabs(valueY);

                degree = atan2(dy, dx);

                if(degree<0){
                    cerr << "noc"<<endl;
                    degree= fabs(degree);
                }
                double value =  (dy + dx);
                //double value = level - (dy + dx);
                //value =  (dy/8 + dx/8);

                this->dx[i][j]= dx;
                this->dy[i][j]= dy;
                this->gradientMagnitude[i][j]=value;
                this->gradientDegree[i][j]= degree;
                this->gradientDegreeDiscret[i][j]=discretDegree(degree);
                this->gradientOrientationDiscret[i][j]= discretOrientation(degree);

                if(value > level){
                    value = level;
                }
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
    imageOuput.setGraysScale(this->gradientDegree);
    imageOuput.setLevel(2*PI);
    imageOuput.saveImage("../ImagenesPrueba/gradientDegree.pgm");
    imageOuput.setLevel(7);
    imageOuput.setGraysScale(this->gradientDegreeDiscret);
    imageOuput.saveImage("../ImagenesPrueba/gradientDegree.pgm");
    imageOuput.setLevel(3);
    imageOuput.setGraysScale(this->gradientOrientationDiscret);
    imageOuput.saveImage("../ImagenesPrueba/gradientOrientationDiscret.pgm");
    imageOuput.setLevel(level);
    /**/
    imageOuput.setGraysScale(grayScaleOuput);
    return imageOuput;
}

double Edge::discretOrientation(double value){
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
        return 4;
        //return 135*PI/180;
    }else if(degree >= 202.5 && degree < 247.5 ){//225   1
        return 5;
        //return 135*PI/180;
    }else if(degree >= 247.5 && degree < 292.5 ){//270   2
        return 6;
        //return 135*PI/180;
    }else if(degree >= 292.5 && degree < 337.5 ){//315   3
        return 7;
       //return 135*PI/180;
    }else if((degree >= 337.5 && degree < 360) || (degree>=0 && degree < 22.5) ){//0   0
        return 0;
        //return 135*PI/180;
    }

    cerr << "no entro discret" << endl;
    return -1;

}

Image Edge::applyCannyDetector(Image &image){
    Image imageOuput;
    int height = image.getHeight();
    int width = image.getWidth();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());

    matrix grayScaleInput = image.getGraysScale();
    this->dx = grayScaleInput;
    this->dy = grayScaleInput;
    this->gradientMagnitude = grayScaleInput;
    this->gradientDegree = grayScaleInput;
    this->gradientDegreeDiscret = grayScaleInput;
    this->gradientOrientationDiscret = grayScaleInput;
    this->edgeControl= grayScaleInput;
    this->edgeHysteresis = grayScaleInput;

    calcGradient(image,Sx,Sy);
    nonMaximumSuppression(height, width);
    hysteresis(height, width, 220,180);

    //OperationArithmetic op;
    //imageOuput.setLevel(image.getLevel());
    //imageOuput.setGraysScale(this->edgeNonMaximumSuppression);
    //imageOuput = op.invertImage(imageOuput);
    //imageOuput.saveImage("../ImagenesPrueba/nonmaxsup.pgm");
    imageOuput.setLevel(1);
    imageOuput.setGraysScale(this->edgeHysteresis);
    return imageOuput;
}

matrix Edge::nonMaximumSuppression(int height, int width){//ojo aca
    this->edgeNonMaximumSuppression = this->gradientMagnitude;
    for(int i = 0 ; i< height;i++ ){
        for(int j = 0 ; j< width;j++ ){

            int orientation = (int)this->gradientOrientationDiscret[i][j];
            double valueGradient = this->gradientMagnitude[i][j];
            switch(orientation){
            case 0:
                if(i==0){
                    if(valueGradient <= this->gradientMagnitude[i+1][j]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }

                }else if(i==height-1){
                    if(valueGradient <= this->gradientMagnitude[i-1][j]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }
                }else{
                    if(valueGradient <= this->gradientMagnitude[i+1][j] || valueGradient <= this->gradientMagnitude[i-1][j]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }
                }
                break;
            case 3:
                if((i == height-1) && (j==0)){
                    if(valueGradient <= this->gradientMagnitude[i-1][j+1]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }

                }else if((i == 0) && (j==height-1)){
                    if(valueGradient <= this->gradientMagnitude[i+1][j-1]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }
                }else{
                    if(valueGradient <= this->gradientMagnitude[i+1][j-1] || valueGradient <= this->gradientMagnitude[i-1][j+1]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }
                }
                break;
            case 2:
                if(j==0){
                    if(valueGradient <= this->gradientMagnitude[i][j+1]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }

                }else if(j==height-1){
                    if(valueGradient <= this->gradientMagnitude[i][j-1]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }
                }else{
                    if(valueGradient <= this->gradientMagnitude[i][j+1] || valueGradient <= this->gradientMagnitude[i][j-1]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }
                }
                break;
            case 1:
                if((i == 0) && (j==0)){
                    if(valueGradient <= this->gradientMagnitude[i+1][j+1]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }

                }else if((i == height-1) && (j==height-1)){
                    if(valueGradient <= this->gradientMagnitude[i-1][j-1]){
                        this->edgeNonMaximumSuppression[i][j]=0;
                    }
                }else{
                    if(valueGradient <= this->gradientMagnitude[i+1][j+1] || valueGradient <= this->gradientMagnitude[i-1][j-1]){
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
    //this->edgeHysteresis = this->edgeNonMaximumSuppression;
    for(int i = 0; i < heigth; i++){
        for(int j = 0; j < width ; j++){
            //cout << edgeNonMaximumSuppression[i][j]<< " ";
            if(edgeNonMaximumSuppression[i][j]>=thresholdHigh){
                //edgeHysteresis[i][j]=0;
                edgeDetection(i,j,heigth, width, thresholdHigh, thresholdsDown);
                this->edgeControl[i][j]==1;
                this->edgeHysteresis[i][j]=0;
            }/*else if(edgeNonMaximumSuppression[i][j]<thresholdsDown){
                edgeHysteresis[i][j]=1;
                //this->edgeControl[i][j]=1;
            }*/
        } //cout << endl << endl << endl;
    }
    //0 es borde , 1 no es borde
    return this->edgeHysteresis;
}

int Edge::edgeDetection(int posX, int posY, int heigth, int width, double thresholdHigh, double thresholdsDown){
    if(this->edgeControl[posX][posY]==0){//si no lo visite

        int degree = this->gradientDegree[posX][posY];
        switch(degree){//mover al siguiente punto 90° respecto angulo gradiente contra manecillas reloj
        case 0:
            posY--;
            posX--;
            break;
        case 1:
            posX-=2;
            break;
        case 2:
            posY++;
            posX--;
            break;
        case 3:
            posY+=2;
            break;
        case 4:
            posY++;
            posY++;
            break;
        case 5:
            posX+=2;
            break;
        case 6:
            posX++;
            posY--;
            break;
        case 7:
            posY-=2;
            break;

        }
        //siguiente punto!!!

        if(!(posX<0 || posX>=heigth) && !(posY<0 || posY>=width) && this->edgeNonMaximumSuppression[posX][posY] >= thresholdsDown){//puede interesarme
            if(edgeDetection(posX, posY,heigth, width, thresholdHigh, thresholdsDown)){
                this->edgeControl[posX][posY]==1;
                this->edgeHysteresis[posX][posY]=0;
                return 1;
            }



        }

        }
    return 0;





/*

    //si sobrepasa los limites
    if(posX<0 || posX>=heigth){
        return 1;
    }else if(posY<0 || posY>=width){
        return 1;
    }else if(this->edgeNonMaximumSuppression[posX][posY]<thresholdsDown){// si es menor al TD
        this->edgeHysteresis[posX][posY]=1;
        return 1;
    }else if(this->edgeNonMaximumSuppression[posX][posY]>=thresholdHigh){// me interesa es mayor a TH
        this->edgeHysteresis[posX][posY]=0;
        return edgeDetection(posX, posY, heigth, width, thresholdHigh, thresholdsDown);
    }else {// puede ser un punto de interes
        //this->edgeHysteresis[posX][posY]=0;
        return edgeDetection(posX, posY, heigth, width, thresholdHigh, thresholdsDown);
    }

    if(this->edgeHysteresis[posX][posY]==1){
        this->edgeHysteresis[posX][posY]=0;
        for (int y_off = -1; y_off <=1; y_off++)
                {
                    for(int x_off = -1; x_off <= 1; x_off++)
                    {
                        if (!(posY == 0 && x_off == 0) && !(posX<0 || posX>=heigth) && !(posY<0 || posY>=width) &&this->gradientMagnitude[posX+x_off][posY + y_off] >= thresholdsDown) {
                            if (edgeDetection(posX + x_off, posY + y_off,heigth, width, thresholdHigh, thresholdsDown))
                            {
                                return 1;
                            }
                        }
                    }
                    return 1;
                }
        return 0;

    }*/



}




//aplica una ventana de convolución de tamaño 3
double Edge::convolution(matrix &img, int posX, int posY, const double kernel[][3]){
    int i, j;
    double r=0;
    for(i=-1;i<=1;i++)
        for(j=-1;j<=1;j++)
            r+= img[posX+i][posY+j] * kernel[i+1][j+1];

    return r;

}


