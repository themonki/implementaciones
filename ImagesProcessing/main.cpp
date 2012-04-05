#include "image.h"
#include "histogram.h"

int main(int argc, char *argv[])
{
    //Image image("Images Test/lena.pgm");

    try{

        Image image("../ImagenesPrueba/lena.pgm");

        image.saveImage("../ImagenesPrueba/lenaPrueba.pgm");

        Histogram histogram(image);
        Image imageHistogram = histogram.getImageHistogram();
        imageHistogram.saveImage("../ImagenesPrueba/hystogramLena.pgm");
    }catch(ImageExeption& e){
        cerr << e.getDescription()<< ": " <<e.what();
    }catch(...){
        cerr << "Desconocido";
    }
        return 0;
}
