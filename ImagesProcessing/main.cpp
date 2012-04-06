#include "image.h"
#include "histogram.h"
#include "thresholding.h"

int main(int argc, char *argv[])
{
    //Image image("Images Test/lena.pgm");

    try{

        Image image("../ImagenesPrueba/lena.pgm");

        image.saveImage("../ImagenesPrueba/lenaPrueba.pgm");

        Histogram histogram(image);
        Image imageHistogram = histogram.getImageHistogram();
        imageHistogram.saveImage("../ImagenesPrueba/hystogramLena.pgm");

        Thresholding thresholding;
        Image imageDospicos =  thresholding.applyDosPicos(image);
        imageDospicos.saveImage("../ImagenesPrueba/thresholdingDosPicos.pgm");
        Image imageOtsu =  thresholding.applyOtsu(image);
        imageOtsu.saveImage("../ImagenesPrueba/thresholdingOtsu.pgm");
        Image imagenIsodata =  thresholding.applyIsodata(image);
        imagenIsodata.saveImage("../ImagenesPrueba/thresholdingIsodata.pgm");


    }catch(ImageExeption& e){
        cerr << e.getDescription()<< ": " <<e.what();
    }catch(...){
        cerr << "Desconocido";
    }
        return 0;
}
