#include "image.h"
#include "histogram.h"
#include "thresholding.h"
#include "contrast.h"
#include "filter.h"


int main(int argc, char *argv[])
{
     Image imagen;
     imagen.readDicomImage("../ImagenesPrueba/DCMTKSamples/brain2.dcm");
    //image.saveImage("../ImagenesPrueba/guardeP6.ppm");

    try{
        //Image image("../ImagenesPrueba/lena256.ppm");

        //image.saveImage("../ImagenesPrueba/pruebap6.ppm");

        /*Histogram histogram(image);
        Image imageHistogram = histogram.getImageHistogram();
        imageHistogram.saveImage("../ImagenesPrueba/hystogramLena.pgm");

        Thresholding thresholding;
        Image imageDospicos =  thresholding.applyDosPicos(image);
        imageDospicos.saveImage("../ImagenesPrueba/thresholdingDosPicosLena.pgm");
        Image imageOtsu =  thresholding.applyOtsu(image);
        imageOtsu.saveImage("../ImagenesPrueba/thresholdingOtsuLena.pgm");
        Image imagenIsodata =  thresholding.applyIsodata(image);
        imagenIsodata.saveImage("../ImagenesPrueba/thresholdingIsodataLena.pgm");

        Contrast contrast;
        Image imageEqualizer = contrast.applyEqulizer(image);
        imageEqualizer.saveImage("../ImagenesPrueba/EqualizerLena.pgm");

        Image imageCorrectionGama = contrast.gammaCorrection(image,2.2);
        imageCorrectionGama.saveImage("../ImagenesPrueba/CorrectionGamaLena.pgm");

        Image imageExpansionContrast = contrast.contrastExpansion(image);
        imageExpansionContrast.saveImage("../ImagenesPrueba/ExpansionContrastLena.pgm");

        Image imageImproveContrast = contrast.improveContrast(image,0);
        imageImproveContrast.saveImage("../ImagenesPrueba/ImproveContrastLena1.pgm");
        imageImproveContrast = contrast.improveContrast(image,1);
        imageImproveContrast.saveImage("../ImagenesPrueba/ImproveContrastLena2.pgm");
        /**/

        Filter filter;

        Image image2("../ImagenesPrueba/noisy.pgm");
        Image imageNoiseCleaningPixel = filter.noiseCleaningPixel(image2, 10.0);
        imageNoiseCleaningPixel.saveImage("../ImagenesPrueba/cleanPixel2.pgm");
        /*Image imageMedianFilter = filter.medianFilter(image2,3);
        imageMedianFilter.saveImage("../ImagenesPrueba/Denoysing.pgm");
        */

        Image imageSigmaFilter = filter.medianFilter(image2,10);
        imageSigmaFilter.saveImage("../ImagenesPrueba/Denoysing4.pgm");
        //image.readDicomImage("asdasd");
        /*
        Image imageNagao("../ImagenesPrueba/noisy2.pgm");        
        Image imageNagao_MatsuyamaFilter = filter.nagao_MatsuyamaFilter(imageNagao,5);
        imageNagao_MatsuyamaFilter.saveImage("../ImagenesPrueba/nagao_matsumayafilter.pgm");
        /**/




    }catch(ImageExeption& e){
        cerr << e.getDescription()<< ": " <<e.what();
    }catch(...){
        cerr << "Desconocido";
    }
    return 0;
}

