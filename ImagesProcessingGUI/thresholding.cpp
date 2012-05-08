#include "thresholding.h"

Thresholding::Thresholding()
{
    this->threshold = 0;
}

int Thresholding::getThreshold()
{

    return threshold;
}

vectorx Thresholding::getLookUpTable()
{
    return lookUpTable;
}

void Thresholding::setThreshold(int threshold)
{
    this->threshold = threshold;
}

void Thresholding::setLookUpTable(vectorx lookUpTable)
{
    this->lookUpTable = lookUpTable;
}

Image Thresholding::applyDosPicos(Image& image)
{
    Histogram histogram(image);
    vectorx vectorHistogram =histogram.getHistogram();
    int level = image.getLevel();
    int firstPeak = 0;
    int secondPeak = 0;
    int temp = 0;

    // Encontramos el indice del primer pico(valor con mayor frecuencia)
    for(int i=1;i<level;i++)
    {
        if(vectorHistogram[i] > vectorHistogram[firstPeak])
        {
            firstPeak = i;
        }
    }


    for(int i =0;i<level;i++)
    {
        int value = pow(i-firstPeak,2)*vectorHistogram[i];

        if(value > temp)
        {
            secondPeak = i;
            temp = value;
        }

    }

    int start =  min(firstPeak,secondPeak);
    int finish = max(firstPeak,secondPeak);



    for(int i=start+1; i<=finish;i++)
    {
        int value = vectorHistogram[i];
        if(value < temp)
        {
            this->threshold = i;
            temp = value;
        }

    }




    this->lookUpTable.resize(level+1);
    for(int i=0; i<level+1;i++)
    {
        if(i< this->threshold)
        {
            lookUpTable[i] = 0;
        }
        else
        {
            lookUpTable[i] = 1;
        }
    }



    Image imageOuput;

    int height = image.getHeight();
    int width = image.getWidth();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(1);

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

Image Thresholding::applyOtsu(Image& image)
{
    Histogram histogram(image);
    vectorx vectorHistogram = histogram.getHistogram(); //Histograma de la imagen
    double sum=0, weight1, weight2, mean1, mean2, variance1, variance2, classVariance, temp=HUGE_VAL, tempWeight;
    int level=image.getLevel();
    int i, j; //Iteradores

    //Peso de todo el histograma
    for(i=0; i<=level; i++)
        sum+=vectorHistogram[i];

    for(i=0; i<=level; i++){
        weight1=0; weight2=0; mean1=0; mean2=0; variance1=0; variance2=0;

        //Deste 0 hasta T
        for(j=0; j<=i; j++)
            weight1+=vectorHistogram[j];
        tempWeight=weight1;
        weight1=weight1/sum;

        if(tempWeight==0) //Se evita la division entre 0
            continue;

        //Varianza
        for(j=0; j<=i; j++)
            variance1+=(j*vectorHistogram[j]);
        variance1=variance1/tempWeight;

        //Promedio
        for(j=0; j<=i; j++)
            mean1+=(pow(j-variance1, 2)*vectorHistogram[j]);

        //Desde T hasta el final
        for(j=i+1; j<=level; j++)
            weight2+=vectorHistogram[j];
        tempWeight=weight2;
        weight2=weight2/sum;

        if(tempWeight==0) //Se evita la division entre 0
            continue;

        //Varianza
        for(j=i+1; j<=level; j++)
            variance2+=(j*vectorHistogram[j]);
        variance2=variance2/tempWeight;

        //Promedio
        for(j=i+1; j<=level; j++)
            mean2+=(pow(j-variance2, 2)*vectorHistogram[j]);

        classVariance=weight1*mean1+weight2*mean2; //Varianza entre clases

        //Si el valor de la funcion es inferior se actualiza
        if(classVariance<temp){
            this->threshold=i;
            temp=classVariance;
        }
    }







    this->lookUpTable.resize(level+1);
    for(int i=0; i<level+1;i++)
    {
        if(i< this->threshold)
        {
            lookUpTable[i] = 0;
        }
        else
        {
            lookUpTable[i] = 1;
        }
    }



    Image imageOuput;

    int height = image.getHeight();
    int width = image.getWidth();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(1);

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
Image Thresholding::applyIsodata(Image& image)
{
    Histogram histogram(image);
    vectorx vectorHistogram = histogram.getHistogram(); //Histograma de la imagen
    double mean1=0, mean2=0, intensityMean = 0;
    int height = image.getHeight();
    int width = image.getWidth();
    int level = image.getLevel();
    int total = height*width;
    int i; //Iterador

    //Se calcula el promedio de intensidades
    for(i=0; i<=level; i++)
            intensityMean+=(vectorHistogram[i]*i);
    intensityMean=intensityMean/total;

    //Se calcula promedio hasta el promedio de intensidades
    for(i=0; i<=round(intensityMean); i++)
            mean1+=(vectorHistogram[i]*i);
    mean1=mean1/total;

    //Se calcula promedio desde el promedio de intensidades hasta el final del histograma
    for(i=round(intensityMean)+1; i<=level; i++)
            mean2+=(vectorHistogram[i]*i);
    mean2=mean2/total;

    double beforeIntensityMean = (mean1+mean2)/2;

    while(round(intensityMean)!=round(beforeIntensityMean)){
            intensityMean=(mean1+mean2)/2; //Posible umbral

            mean1=0; mean2=0;

            //Se calcula promedio hasta el promedio de intensidades
            for(i=0; i<=round(intensityMean); i++)
                    mean1+=(vectorHistogram[i]*i);
            mean1=mean1/total;

            //Se calcula promedio desde el promedio de intensidades hasta el final del histograma
            for(i=round(intensityMean)+1; i<=level; i++)
                    mean2+=(vectorHistogram[i]*i);
            mean2=mean2/total;

            beforeIntensityMean = (mean1+mean2)/2;
    }

    this->threshold = round(intensityMean);

    this->lookUpTable.resize(level+1);
    for(int i=0; i<level+1;i++)
    {
        if(i< this->threshold)
        {
            lookUpTable[i] = 0;
        }
        else
        {
            lookUpTable[i] = 1;
        }
    }



    Image imageOuput;


    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(1);

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

Image Thresholding::createThresholdImage(Image& image, int threshold)
{
    int level = image.getLevel();

    this->lookUpTable.resize(level+1);
    for(int i=0; i<level+1;i++)
    {
        if(i< threshold)
        {
            lookUpTable[i] = 0;
        }
        else
        {
            lookUpTable[i] = 1;
        }
    }



    Image imageOuput;

    int height = image.getHeight();
    int width = image.getWidth();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(1);

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
matrix Thresholding::createThresholdImage(matrix& grayScale, int level, int threshold)
{


    this->lookUpTable.resize(level+1);
    for(int i=0; i<level+1;i++)
    {
        if(i< threshold)
        {
            lookUpTable[i] = 0;
        }
        else
        {
            lookUpTable[i] = 1;
        }
    }





    int height = grayScale.size();
    int width = grayScale[0].size();

    matrix grayScaleCopy = grayScale;



    for(int i=0;i<height;i++)
    {
        for(int j= 0; j<width;j++)
        {
            grayScaleCopy[i][j] = this->lookUpTable[round(grayScaleCopy[i][j])];
        }

    }


    return grayScaleCopy;
}


