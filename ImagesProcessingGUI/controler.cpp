#include "controler.h"

Controler::Controler()
{
}

void Controler::openImage(string path){
    image=Image(path);
}

void Controler::saveImage(string path){
    image.saveImage(path);
}

void Controler::setImageIn(Image i){
    QImage();
}

void Controler::setImageOut(Image i){

}

QImage Controler::getImageIn(){
    return this->imageIn;
}

QImage Controler::getImageOut(){
    return this->imageOut;
}
