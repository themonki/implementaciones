#include "controler.h"

Controler::Controler()
{
    this->dicomImage=false;
    this->ppmImage=false;
}

void Controler::openImage(QString path){


    if(!path.toStdString().substr(path.toStdString().length()-4, 4).compare(".dcm")){//si es una imagen dicom
        this->dicomImage=true;
        this->ppmImage=false;
        this->imageIn= new Image();
        this->imageOut= new Image();
        this->imageIn->readDicomImage(path.toStdString());
        this->imageOut->readDicomImage(path.toStdString());
        this->imageIn->saveImage("file2.pgm");

        QImage i, j;
        i = QImage();
        j = QImage();
        i.load("file2.pgm");
        this->imageInLabel = i;
        j.load("file2.pgm");
        this->imageOutLabel = j;
        return;
    }

    imageIn = new Image(path.toStdString());
    imageOut = new Image(path.toStdString());

    QImage i, j;
    i = QImage();
    j = QImage();
    i.load(path);
    this->imageInLabel = i;
    j.load(path);
    this->imageOutLabel = j;

    //cout << imageOutLabel.format()  <<" size " << imageOutLabel.width()<<"," << imageIn->getHeight() << " - " << imageIn->getWidth() <<","<<imageIn->getHeight() << endl;
/*
    for(int i = 0; i< image*In->getHeight(); i++){
        for(int j = 0;j< imageIn->getWidth(); j++){
            cout << qGray(imageinlabel.pixel(i,j)) << " este " << imageIn->getGraysScale()[i][j] << endl;

        }}
*/

    if(!imageIn->getType().compare("P2") || !imageIn->getType().compare("P5")){//pgm
        this->ppmImage=false;
    }else if(!imageIn->getType().compare("P3") || !imageIn->getType().compare("P6")){
        this->ppmImage=true;
    }

}
void Controler::saveImage(QString path){


    /*Image* img;
    img = new Image();

    img->setHeight(imageIn->getHeight());
    img->setWidth(imageIn->getWidth());
    img->setLevel(imageIn->getLevel());
    img->setType(imageIn->getType());

    if(!this->ppmImage){
        matrix gray;
        gray.resize(img->getHeight());
        for(int i=0; i<img->getHeight(); i++){
            gray[i].resize(img->getWidth());
        }
        for(int i=0; i<img->getHeight(); i++){
            for(int j = 0; j < img->getWidth();j++){
                gray[i][j] = qGray(img->pixel(i,j));

            }
        }

        img->setGraysScale(gray);

    }else{
        matrix blue, red, green;
        blue.resize(img->getHeight());
        red.resize(img->getHeight());
        green.resize(img->getHeight());
        for(int i=0; i<img->getHeight(); i++){
            blue[i].resize(img->getWidth());
            green[i].resize(img->getWidth());
            red[i].resize(img->getWidth());
        }
        for(int i=0; i<img->getHeight(); i++){
            for(int j = 0; j < img->getWidth();j++){
                blue[i][j] = qBlue(img->pixel(i,j));
                green[i][j] = qGreen(img->pixel(i,j));
                red[i][j] = qRed(img->pixel(i,j));
            }
        }

        img->setBlue(blue);
        img->setRed(red);
        img->setGreen(green);
    }


    img->saveImage(path.toStdString());*/

    this->imageOut->saveImage(path.toStdString());
}

void Controler::setImageIn(Image* i){
    this->imageIn=i;
}

void Controler::setImageOut(Image* i){
    this->imageIn=i;
}

void Controler::setImageInLabel(QImage i){
    this->imageInLabel=i;
}

void Controler::setImageOutLabel(QImage i){
    this->imageOutLabel=i;
}



Image* Controler::getImageIn(){

    return this->imageIn;
}

Image* Controler::getImageOut(){
    return this->imageOut;
}

QImage Controler::getImageInLabel(){

    return this->imageInLabel;
}

QImage Controler::getImageOutLabel(){
    return this->imageOutLabel;
}

QImage Controler::applyConvertToGrayScale(Image* img,QImage labelImage){
    img->colorToGraysScale();
    img->saveImage(QDir::currentPath().append("/file.pgm").toStdString());
    labelImage.load(QDir::currentPath().append("/file.pgm"));
    this->ppmImage=false;
    return labelImage;
}

QImage Controler::convertImage(Image & image, QImage & img){


    //cout << img.format()  <<" size " << img.width()<<"," << img.height() << " - " << imageIn->getWidth() <<","<<imageIn->getHeight() << endl;

    for(int i = 0; i< img.height(); i++){
        for(int j = 0;j< img.width(); j++){
           // unsigned int x = image->round(image->getGraysScale()[i][j]);
            //cout << image->round(image->getGraysScale()[i][j]) << " nuevo " << x << endl;
            //if(i < 300  && j < 50){
                unsigned int temp =   image.round(image.getGraysScale()[i][j]);
                img.setPixel(j,i,temp);
            //}else{
             //   break;
           // }
        }
    }
    //cerr << "terminamos"<<endl << endl;


    return img;

}

QImage Controler::convertImageIn(){
    return convertImage(*this->imageIn, this->imageInLabel);
}

QImage Controler::convertImageOut(){
    return convertImage(*this->imageOut, this->imageOutLabel);
}

void Controler::applyFilterSigma(int sigma){
    Filter filtro;
    /*Image img;
    img.setHeight(imageOut->getHeight());
    img.setWidth(imageOut->getWidth());
    img.setLevel(imageOut->getLevel());
    img.setType(imageOut->getType());
    img.setBlue(imageOut->getBlue());
    img.setRed(imageOut->getRed());
    img.setGreen(imageOut->getGreen());
    img.setGraysScale(imageOut->getGraysScale());*/
    Image img, *temp;
    img = filtro.sigmaFilter(*this->imageOut, sigma);
    img.saveImage(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
    /*

    this->imageOut->setHeight(img.getHeight());
    this->imageOut->setWidth(img.getWidth());
    this->imageOut->setLevel(img.getLevel());
    this->imageOut->setType(img.getType());
    this->imageOut->setBlue(img.getBlue());
    this->imageOut->setRed(img.getRed());
    this->imageOut->setGreen(img.getGreen());
    this->imageOut->setGraysScale(img.getGraysScale());


    convertImage(*imageOut, imageOutLabel);*/

}

void Controler::applyFilterMedian(int n){
    Filter filtro;
    /*Image img;
    img.setHeight(imageOut->getHeight());
    img.setWidth(imageOut->getWidth());
    img.setLevel(imageOut->getLevel());
    img.setType(imageOut->getType());
    img.setBlue(imageOut->getBlue());
    img.setRed(imageOut->getRed());
    img.setGreen(imageOut->getGreen());
    img.setGraysScale(imageOut->getGraysScale());*/

    Image tempImageOut = filtro.medianFilter(*imageOut, n), *temp;
    tempImageOut.saveImage(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
    //cout << QDir::currentPath().append("/file.pgm").toStdString()<<endl;
   // convertImage(*imageOut, imageOutLabel);
}

void Controler::applyFilterCleaningPixel(double delta){
    Filter filtro;
        Image tempImageOut = filtro.noiseCleaningPixel(*imageOut, delta), *temp;
    tempImageOut.saveImage(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
}

void Controler::applyFilterCleaningLine(double delta){
    Filter filtro;
        Image tempImageOut = filtro.noiseCleaningLine(*imageOut, delta), *temp;
    tempImageOut.saveImage(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
}

QImage Controler::getHistogram(){

    Histogram h(*this->imageOut);
    Image imgH = h.getImageHistogram();

    imgH.saveImage(QDir::currentPath().toStdString().append("/file.pgm"));
    QImage imgcopy;
    imgcopy.load(QDir::currentPath().append("/file.pgm"));

    //cout <<  QDir::currentPath().append("/file.pgm").toStdString()<<endl << endl;
    return imgcopy;
}

QImage Controler::gethistogramInLabel(){
    Histogram h(*this->imageIn);
    Image imgH = h.getImageHistogram();

    imgH.saveImage(QDir::currentPath().toStdString().append("/file.pgm"));
    QImage imgcopy;
    imgcopy.load(QDir::currentPath().append("/file.pgm"));

    //cout <<  QDir::currentPath().append("/file.pgm").toStdString()<<endl << endl;
    return imgcopy;
}

void Controler::applyContrastStretching(){
    Contrast c;
    Image img= c.contrastStretching(*this->imageOut), *temp;
    img.saveImage(QDir::currentPath().toStdString().append("/file.pgm"));
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
}

void Controler::applyContrastCorrectionGamma(double r){
    Contrast c;
    Image img = c.gammaCorrection(*this->imageOut, r), *temp;
    img.saveImage(QDir::currentPath().toStdString().append("/file.pgm"));
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
}

void Controler::applyContrastImprove(int option){
    Contrast c;
    Image img = c.improveContrast(*this->imageOut, option), *temp;
    img.saveImage(QDir::currentPath().toStdString().append("/file.pgm"));
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
}

void Controler::applyEqualizer(){
    Contrast c;
    Image img = c.applyEqulizer(*this->imageOut), *temp;
    img.saveImage(QDir::currentPath().toStdString().append("/file.pgm"));
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
}

void Controler::getThresholdingDosPicos(){
    Thresholding t;
    Image img = t.applyDosPicos(*this->imageOut), *temp;
    img.saveImage(QDir::currentPath().toStdString().append("/file.pgm"));
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
}

void Controler::getThresholdingIsodata(){
    Thresholding t;
    Image img = t.applyIsodata(*this->imageOut), *temp;
    img.saveImage(QDir::currentPath().toStdString().append("/file.pgm"));
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
}

void Controler::getThresholdingOtsu(){
    Thresholding t;
    Image img = t.applyOtsu(*this->imageOut), *temp;
    img.saveImage(QDir::currentPath().toStdString().append("/file.pgm"));
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
}

void Controler::applyOperationAddImage(Image in, double value){
    OperationArithmetic op;
    Image img = op.additionImages(*this->imageOut, in, value), *temp;
    img.saveImage(QDir::currentPath().toStdString().append("/file.pgm"));
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
}

void Controler::applyOperationAddValue(double value){
    OperationArithmetic op;
    Image img = op.additionValue(*this->imageOut, value), *temp;
    img.saveImage(QDir::currentPath().toStdString().append("/file.pgm"));
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
}

void Controler::applyOperationDivValue( double value){
    OperationArithmetic op;
    Image img = op.divisionValue(*this->imageOut, value), *temp;
    img.saveImage(QDir::currentPath().toStdString().append("/file.pgm"));
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
}

void Controler::applyOperationMulValue( double value){
    OperationArithmetic op;
    Image img = op.multiplicationValue( *this->imageOut, value), *temp;
    img.saveImage(QDir::currentPath().toStdString().append("/file.pgm"));
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
}

void Controler::applyOperationSubValue( double value){
    OperationArithmetic op;
    Image img = op.subtractionValue(*this->imageOut,value), *temp;
    img.saveImage(QDir::currentPath().toStdString().append("/file.pgm"));
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
}

void Controler::applyOperationInvertImage(){
    OperationArithmetic op;
    Image img = op.invertImage(*this->imageOut), *temp;
    img.saveImage(QDir::currentPath().toStdString().append("/file.pgm"));
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
}


bool Controler::isDicomImage(){return dicomImage;}

bool Controler::isppmImage(){return ppmImage;}

void Controler::clearAll(){
    if(this->dicomImage){

    }
    this->imageIn->clearImage();
    this->imageOut->clearImage();
    this->dicomImage=false;
    this->ppmImage=false;
}

void Controler::applyEdgeDetectorSobel(double threshold){
    Edge e;
    Image img = e.applySobelDetection(*this->imageOut,threshold), *temp;
    img.saveImage(QDir::currentPath().toStdString().append("/file.pgm"));
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
}

void Controler::applyEdgeDetectorCanny(double thresholdHigh, double thresholdsDown){
    Edge e;
    Image img = e.applyCannyDetector(*this->imageOut,thresholdHigh,thresholdsDown), *temp;
    img.saveImage(QDir::currentPath().toStdString().append("/file.pgm"));
    this->imageOutLabel.load(QDir::currentPath().append("/file.pgm"));
    temp = new Image(QDir::currentPath().append("/file.pgm").toStdString());
    this->imageOut = temp;
}

void Controler::applyDicomWindow(){}

void Controler::applyDicomLevel(){}
