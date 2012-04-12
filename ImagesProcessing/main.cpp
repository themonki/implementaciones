/*
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmdata/dcpxitem.h"


int main(int argc, char *argv[])
{
  OFCondition result = EC_Normal;

  DcmFileFormat dfile;
  result = dfile.loadFile("test.dcm");
  if (result.bad())
    return 1;
  DcmDataset *data = dfile.getDataset();
  if (data == NULL)
    return 1;
  DcmElement* element = NULL;
  result = data->findAndGetElement(DCM_PixelData, element);
  if (result.bad() || element == NULL)
    return 1;
  DcmPixelData *dpix = NULL;



  if (result.bad())
    return 1;
  else
    return 0;
}
*/



#include "image.h"
#include "histogram.h"
#include "thresholding.h"
#include "contrast.h"
#include "filter.h"


int main(int argc, char *argv[])
{
    //Image image("Images Test/lena.pgm");

    try{

        Image image("../ImagenesPrueba/lena.pgm");

        image.saveImage("../ImagenesPrueba/pruebalena.pgm");

        Histogram histogram(image);
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

        Filter filter;

        Image image2("../ImagenesPrueba/noisy.pgm");
        Image imageMedianFilter = filter.medianFilter(image2,3);
        imageMedianFilter.saveImage("../ImagenesPrueba/Denoysing.pgm");


        Image imageSigmaFilter = filter.sigmaFilter(image2,10);
        imageSigmaFilter.saveImage("../ImagenesPrueba/Denoysing4.pgm");




    }catch(ImageExeption& e){
        cerr << e.getDescription()<< ": " <<e.what();
    }catch(...){
        cerr << "Desconocido";
    }
        return 0;
}

