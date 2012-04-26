#include "controler.h"

Controler::Controler()
{
}

void Controler::openImage(QString path){
    imageIn = imageOut = new Image(path.toStdString());

    QImage* i;
    i = new QImage();
    i->load(path);
    this->imageInLabel = this->imageOutLabel = i;

    if(!imageIn->getType().compare("P2") || !imageIn->getType().compare("P5")){//pgm
        this->ppmImage=false;
    }else if(!imageIn->getType().compare("P3") || !imageIn->getType().compare("P6")){
        this->ppmImage=true;
    }

}
void Controler::saveImage(QString path, QImage* img){
    /*Image* saveTemp;
    saveTemp = new Image();

    saveTemp->setHeight(imageIn->getHeight());
    saveTemp->setWidth(imageIn->getWidth());
    saveTemp->setLevel(imageIn->getLevel());
    saveTemp->setType(imageIn->getType());

    if(!this->ppmImage){
        matrix gray;
        gray.resize(saveTemp->getHeight());
        for(int i=0; i<saveTemp->getHeight(); i++){
            gray[i].resize(saveTemp->getWidth());
        }
        for(int i=0; i<saveTemp->getHeight(); i++){
            for(int j = 0; j < saveTemp->getWidth();j++){
                gray[i][j] = qGray(img->pixel(i,j));

            }
        }

        saveTemp->setGraysScale(gray);

    }else{
        matrix blue, red, green;
        blue.resize(saveTemp->getHeight());
        red.resize(saveTemp->getHeight());
        green.resize(saveTemp->getHeight());
        for(int i=0; i<saveTemp->getHeight(); i++){
            blue[i].resize(saveTemp->getWidth());
            green[i].resize(saveTemp->getWidth());
            red[i].resize(saveTemp->getWidth());
        }
        for(int i=0; i<saveTemp->getHeight(); i++){
            for(int j = 0; j < saveTemp->getWidth();j++){
                blue[i][j] = qBlue(img->pixel(i,j));
                green[i][j] = qGreen(img->pixel(i,j));
                red[i][j] = qRed(img->pixel(i,j));
            }
        }

        saveTemp->setBlue(blue);
        saveTemp->setRed(red);
        saveTemp->setGreen(green);
    }


    saveTemp->saveImage(path.toStdString());*/

    this->imageOut->saveImage(path.toStdString());
}

void Controler::setImageIn(QImage *i){

}

void Controler::setImageOut(QImage *i){

}

QImage* Controler::getImageIn(){

    return this->imageInLabel;
}

QImage* Controler::getImageOut(){
    return this->imageOutLabel;
}

QImage* Controler::convertImage(Image* image){


    QImage* img = new QImage(image->getHeight(), image->getWidth(),QImage::Format_Mono);
    /*
    for(int i = 0; i< image->getHeight(); i++){
        for(int j = 0;j< image->getWidth(); j++){

            uint temp =  (image->round(image->getGraysScale()[i][j]));
            QColor *c = new QColor();
            img->setPixel(temp);
        }
    }
*/
    return img;

}

QImage* Controler::convertImageIn(){
    return convertImage(this->imageIn);
}

QImage* Controler::convertImageOut(){
    return convertImage(this->imageIn);
}

