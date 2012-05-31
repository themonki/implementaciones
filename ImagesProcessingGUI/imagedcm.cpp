#include "imagedcm.h"

ImageDCM::ImageDCM(const char *fileName){

    dicomImage = new DicomImage(fileName);

    if (dicomImage != NULL)
    {
        if (dicomImage->getStatus() == EIS_Normal)
        {

            this->type="P2";
            this->level=pow(2,(dicomImage->getDepth()-1))-1;
            this->height=dicomImage->getWidth();
            this->width=dicomImage->getHeight();


            //Lectura correcta datos imagen DICOM
            cout <<"DICOM depth: "<<dicomImage->getDepth()<<endl;
            cout <<"Color Depth: "<<level<<endl;
            cout<< "frameCount: "<<dicomImage->getFrameCount()<<endl;

            dicomImage->getMinMaxValues(minimunDensity, maximunDensity);

            //Valores maximos y minimos
            cout<<"Min Value: "<<minimunDensity<<endl;
            cout<<"Max Value: "<<maximunDensity<<endl;

            //Lookup Table
            lutSize=abs(minimunDensity)+abs(maximunDensity)+1;
            cout <<"lut size"<<lutSize<<endl;

            lookUpTable.resize(lutSize);
            for (int i = 0; i < lutSize; ++i){
                lookUpTable[i]=i-abs(minimunDensity);
                cout <<"LUT["<<i<<"]: "<<lookUpTable[i]<<endl;
            }

            this->graysScale.resize(this->height);
            for(int i=0; i<this->height; i++)
                this->graysScale[i].resize(this->width);



            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    graysScale[i][j]=lookUpTable[getDensity(j,i)+abs(minimunDensity)];
                    cout<<graysScale[i][j]<<" ";
                }
                cout << endl;
            }
            applyWindowLevel(400,40);

            cout << "aplique \n";






        } else
        {

        }

    }

}


int ImageDCM::getDensity(int x, int y)
{
    int iPos = x + (y*width);
    OFString str;
    const DiPixel *dmp = NULL;
    dmp = dicomImage->getInterData();
    void *pixelData = NULL;
    pixelData = (void *)dmp->getData();

    if(NULL == dmp)
    {
        return 0;
    }

    int result = 0;

    EP_Representation rep = dmp->getRepresentation();
    switch(rep)
    {
    case EPR_Sint32:
    {
        Sint32 *pixelNew1 = ((Sint32*)pixelData+iPos);
        result = *pixelNew1;
        break;
    }
    case EPR_Uint32:
    {
        Uint32 *pixelNew2 = ((Uint32*)pixelData+iPos);
        result = *pixelNew2;
        break;
    }
    case EPR_Sint16:
    {
        Sint16 *pixelNew3 = ((Sint16*)pixelData+iPos);
        result = *pixelNew3;
        break;
    }
    case EPR_Uint16:
    {
        Uint16 *pixelNew4 = ((Uint16*)pixelData+iPos);
        result = *pixelNew4;
        break;
    }
    case EPR_Uint8:
    {
        Uint8 *pixelNew5 = ((Uint8*)pixelData+iPos);
        result = *pixelNew5;
        break;
    }
    default:
    {
        Sint8 *pixelNew6 = ((Sint8*)pixelData+iPos);
        result = *pixelNew6;
        break;
    }
    }

    return result;
}

void ImageDCM::applyWindowLevel(int window, int level){

    double min = level - ceil(window/2);
    double max = level + floor(window/2);
    double newPixelValue, pixelValue;

    for (int i = 0; i < lutSize; i++){
        lookUpTable[i]=i-abs(minimunDensity);
        cout << "density value "<< lookUpTable[i]<< endl;
    }

    for(int i=0;i<height;i++)
    {
        for(int j= 0; j<width;j++)
        {
            if (graysScale[i][j]>=min && graysScale[i][j]<=max) {

                pixelValue=graysScale[i][j];
                newPixelValue= (pixelValue-min)*(255/(max-min));
                graysScale[i][j]=newPixelValue;
                cout << "new pixel "<< graysScale[i][j]<< endl;


            } else{

                if(graysScale[i][j]>max){


                    graysScale[i][j]=255;

                } else{

                    graysScale[i][j]=0;

                }

            }


        }
    }


}

int ImageDCM::appyCalibrationFunction(int pixelValue, int rescaleSlope, int rescaleIntercept){ // Not it use!
    return (pixelValue * rescaleSlope) + rescaleIntercept;
}



