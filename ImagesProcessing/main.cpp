#include<image.h>

int main(int argc, char *argv[])
{
    //Image image("Images Test/lena.pgm");

    try{

        Image image("../ImagenesPrueba/lena.ascii.pgm");

        image.saveImage("../ImagenesPrueba/prueba.pgm");

    }catch(ImageExeption& e){
        cerr << e.getDescription()<< ": " <<e.what();
    }catch(...){
        cerr << "Desconocido";
    }
        return 0;
}
