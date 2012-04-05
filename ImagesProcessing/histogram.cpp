#include "histogram.h"

Histogram::Histogram()
{
}

Histogram::Histogram(Image& image)
{
    this->histogram.resize(image.getLevel()+1,0);

    matrix grayScale =image.getGraysScale();

    for(int i=0; i<image.getHeight(); i++){

        for(int j=0; j<image.getWidth(); j++){

            this->histogram[image.round(grayScale[i][j])]++;
        }

    }

}

vectorx Histogram::getHistogram()
{
    return histogram;

}

Image Histogram::getImageHistogram()
{
    int higher =0;
    Image image;
    image.setWidth(512);
    image.setType("P2");

    for(unsigned int i=1; i<this->histogram.size(); i++)
        if(this->histogram[i]>this->histogram[higher])
            higher=i;

    image.setHeight(1000);
    image.setLevel(1);
    matrix values(1000, vectorx(512, 1));

    for(unsigned int i=0; i<this->histogram.size(); i++)
        for(unsigned int j=0; j<1000; j++)
            if(j>=1000-(this->histogram[i]*1000/higher))
                cout<<"*";

    image.setGraysScale(values);

    return image;

}

void Histogram::setHistogram(vectorx histogram)
{

    this->histogram = histogram;
}
