#include "histogramequalizer.h"

HistogramEqualizer::HistogramEqualizer()
{
    this->sum = 0;
}

vectorx HistogramEqualizer::getAccumulativeValues()
{
    return accumulativeValues;
}

vectorx HistogramEqualizer::getFunctionValues()
{
    return functionValues;
}

vectorx HistogramEqualizer::getLookUpTable()
{
    return lookUpTable;
}

void HistogramEqualizer::setAccumulativeValues(vectorx accumulativeValues)
{
    this->accumulativeValues = accumulativeValues;
}

void HistogramEqualizer::setFunctionValues(vectorx functionValues)
{
    this->functionValues = functionValues;
}

void HistogramEqualizer::setLookUpTable(vectorx lookUpTable)
{
    this->lookUpTable = lookUpTable;
}

double HistogramEqualizer::getSum()
{
    return sum;
}

void HistogramEqualizer::setSum(double sum)
{
    this->sum = sum;
}

void HistogramEqualizer::obtainSum(vectorx vectorHistogram)
{
    int size = vectorHistogram.size();
    for(int i=0; i< size;i++)
    {
        sum+= vectorHistogram[i];
        this->accumulativeValues[i] = sum;
    }
}


Image HistogramEqualizer::applyEqulizer(Image& image)
{
    Histogram histogram(image);
    vectorx vectorHistogram =histogram.getHistogram();
    int level = image.getLevel();

    this->accumulativeValues.resize(level+1);
    this->functionValues.resize(level+1);

    this->obtainSum(vectorHistogram);

    // Encontramos el indice del primer pico(valor con mayor frecuencia)
    for(int i=0;i<level+1;i++)
    {
        functionValues[i]= level*accumulativeValues[i]/sum;
    }




    this->lookUpTable.resize(level+1);
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
