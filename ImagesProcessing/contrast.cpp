#include "contrast.h"

Contrast::Contrast()
{
    this->minimunLevel = 0;
    this->contrast = 0;
    this->maximunLevel = 0;
}

vectorx Contrast::getLookUpTable()
{
    return lookUpTable;
}


void Contrast::setLookUpTable(vectorx lookUpTable)
{
    this->lookUpTable = lookUpTable;
}

double Contrast::getContrast()
{
    return contrast;
}

void Contrast::setContrast(double contrast)
{
    this->contrast = contrast;
}

void Contrast::setMaximunLevel(int maximunLevel)
{
    this->maximunLevel = maximunLevel;
}

void Contrast::setMinimunLevel(int minimunLevel)
{
    this->maximunLevel = minimunLevel;

}

int Contrast::getMaximulLevel()
{
    return maximunLevel;

}


int Contrast::getMinimunLevel()
{
    return minimunLevel;

}

void Contrast::obtainContrast(Image& image)
{

    Histogram histogram(image);
    vectorx vectorHistogram = histogram.getHistogram();


    int size = vectorHistogram.size();

    this->minimunLevel=0,
    this->maximunLevel= size-1;

    for(int i=0; i<size; i++)
        if(vectorHistogram[i]!=0){
            this->minimunLevel=i;
            break;
        }

    for(int i=size-1; i>=0; i--)
        if(vectorHistogram[i]!=0){
            this->maximunLevel=i;
            break;
        }

    this->contrast=(this->maximunLevel-this->minimunLevel)/(this->maximunLevel+this->minimunLevel);

}


Image Contrast::gammaCorrection(Image& image, double r)
{
    if(r<0 || r>3){
            cerr << "Error: ¡" << r << " se encuentra en un rango es invalido!" << endl;
            abort();
    }
    if(r==1)
            return image;




    int level =image.getLevel();
    this->lookUpTable.resize(level+1);

    for(int i=0; i<level+1;i++)
    {

        lookUpTable[i] = i;
        lookUpTable[i] = level *pow(lookUpTable[i]/level,r);

    }



    Image imageOuput;

    int height = image.getHeight();
    int width = image.getWidth();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(level);

    matrix grayScale = image.getGraysScale();

    for(int i=0;i<height;i++)
    {
        for(int j= 0; j<width;j++)
        {
            grayScale[i][j] = this->lookUpTable[round(grayScale[i][j])];
        }

    }



    imageOuput.setGraysScale(grayScale);


    return imageOuput;


}

Image Contrast::contrastStretching(Image& image)
{
    obtainContrast(image);
    int level=image.getLevel();


    this->lookUpTable.resize(level+1);

    for(int i=0; i<level+1; i++)
    {

        this->lookUpTable[i]=(i-this->minimunLevel)*level/(this->maximunLevel-this->minimunLevel);

    }


    Image imageOuput;

    int height = image.getHeight();
    int width = image.getWidth();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(level);

    matrix grayScale = image.getGraysScale();

    for(int i=0;i<height;i++)
    {
        for(int j= 0; j<width;j++)
        {
            grayScale[i][j] = this->lookUpTable[round(grayScale[i][j])];
        }

    }



    imageOuput.setGraysScale(grayScale);

    return imageOuput;



}

Image Contrast::improveContrast(Image& image, int option)
{
    int level = image.getLevel();



    this->lookUpTable.resize(level+1);
    if(option==0){

        for(int i=0; i<level+1; i++){

            this->lookUpTable[i]=i;
            if(level-(level*pow(this->lookUpTable[i]/128, 2))<0)
            {

                this->lookUpTable[i]=0;

            }
            else
            {
                this->lookUpTable[i]=level-(level*pow(this->lookUpTable[i]/128, 2));
            }
        }
    }
    if(option==1){

        for(int i=0; i<level+1; i++){
            this->lookUpTable[i] = i;

            this->lookUpTable[i]=level*pow((this->lookUpTable[i]-128)/128, 2);

        }
    }else if(option>1){
        cerr << "Error: ¡" << option << " no es una opcion valida!";
        abort();
    }




    Image imageOuput;

    int height = image.getHeight();
    int width = image.getWidth();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(level);

    matrix grayScale = image.getGraysScale();

    for(int i=0;i<height;i++)
    {
        for(int j= 0; j<width;j++)
        {
            grayScale[i][j] = this->lookUpTable[round(grayScale[i][j])];
        }

    }



    imageOuput.setGraysScale(grayScale);

    return imageOuput;


}


Image Contrast::applyEqulizer(Image& image)
{
    Histogram histogram(image);
    vectorx vectorHistogram  =histogram.getHistogram();
    int level = image.getLevel();
    int size = vectorHistogram.size();

    vectorx accumulativeValues;
    accumulativeValues.resize(size);
    double sum = 0;

    for(int i=0; i< size;i++)
    {
        sum+= vectorHistogram[i];
        accumulativeValues[i] = sum;
    }

    vectorx functionValues;
    functionValues.resize(size);

    // Encontramos el indice del primer pico(valor con mayor frecuencia)
    for(int i=0;i<level+1;i++)
    {
        functionValues[i]= level*accumulativeValues[i]/sum;
    }




    this->lookUpTable.resize(size);
    for(int i=0; i<level+1;i++)
    {
        lookUpTable[i] = round(functionValues[i]);
    }



    Image imageOuput;

    int height = image.getHeight();
    int width = image.getWidth();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(level);

    matrix grayScale = image.getGraysScale();

    for(int i=0;i<height;i++)
    {
        for(int j= 0; j<width;j++)
        {
            grayScale[i][j] = this->lookUpTable[round(grayScale[i][j])];
        }

    }



    imageOuput.setGraysScale(grayScale);

    return imageOuput;
}
