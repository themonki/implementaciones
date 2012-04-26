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
    int height = 256;
    int width= 256;

    Image image;
    image.setWidth(width);
    image.setHeight(height);
    image.setType("P2");
    image.setLevel(1);
    matrix values(height, vectorx(width, 1));

    int size = this->histogram.size();

    for(int i=1; i<size; i++)
    {
        int value = this->histogram[i];
        if(value >higher)
        {
            higher=histogram[i];
        }
    }



    for(int i=0; i<size; i++)
    {

        for(int j=0; j<height; j++)
        {
            int value = this->histogram[i];
            if(j>=height-(value*height/higher))
            {
                  values[j][i]=0;

            }

        }


    }
    image.setGraysScale(values);

    return image;

}

void Histogram::setHistogram(vectorx histogram)
{

    this->histogram = histogram;
}
