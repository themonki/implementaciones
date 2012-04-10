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


int main(int argc, char *argv[])
{
    //Image image("Images Test/lena.pgm");

    try{

        Image image("../ImagenesPrueba/PruebaP5.pgm");

        image.saveImage("../ImagenesPrueba/PruebaP5prueba.pgm");

        Histogram histogram(image);
        Image imageHistogram = histogram.getImageHistogram();
        imageHistogram.saveImage("../ImagenesPrueba/hystogramPP5.pgm");

        Thresholding thresholding;
        Image imageDospicos =  thresholding.applyDosPicos(image);
        imageDospicos.saveImage("../ImagenesPrueba/thresholdingDosPicosP5.pgm");
        Image imageOtsu =  thresholding.applyOtsu(image);
        imageOtsu.saveImage("../ImagenesPrueba/thresholdingOtsuP5.pgm");
        Image imagenIsodata =  thresholding.applyIsodata(image);
        imagenIsodata.saveImage("../ImagenesPrueba/thresholdingIsodataP5.pgm");


    }catch(ImageExeption& e){
        cerr << e.getDescription()<< ": " <<e.what();
    }catch(...){
        cerr << "Desconocido";
    }
        return 0;
}

