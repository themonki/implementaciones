#include "filter.h"
#include <algorithm>



Filter::Filter()
{
}

Image Filter::medianFilter(Image &image, int n)
{
    Image imageOuput;

    int height = image.getHeight();
    int width = image.getWidth();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(image.getLevel());

    matrix grayScaleInput = image.getGraysScale();
    matrix grayScaleOuput = image.getGraysScale();

    //D
    int edgeX = n/2;
    int edgeY = n/2;

    for(int i=edgeY; i<height-edgeY;i++)
    {
        for(int j=edgeX; j<width-edgeX;j++)
        {
            vector<int> values;
            values.resize(n*n);


            int count =0;

            for(int k=0; k<n;k++)
            {
                for(int l=0; l<n;l++)
                {
                    values[count] =  grayScaleInput[i+k-edgeX][j+l-edgeY];
                    // cout<< values[count]<<"--";
                    count++;
                }
            }
            //cout <<"\n";

            sort(values.begin(),values.end());

            //cout<<n*n/2<<"\n";
            grayScaleOuput[i][j] = values[(n*n)/2];
            //cout << grayScaleOuput[i][j]<<"\n";


        }
    }


    imageOuput.setGraysScale(grayScaleOuput);





    return imageOuput;
}

Image Filter::sigmaFilter(Image &image, int sigma)
{
    Image imageOuput;

    int height = image.getHeight();
    int width = image.getWidth();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(image.getLevel());

    matrix grayScaleInput = image.getGraysScale();
    matrix grayScaleOuput = image.getGraysScale();


    double sum = 0;
    int no = 0;


    for (int i=0; i < height; i++ )
    {
        for (int j=0; j < width; j++ )
        {


            sum = no = 0;
            int m =0;
            int n = 0;
            int pixelValue =0;
            for ( int k=-1; k<= 5; k++ )
            {
                m = i + k;

                if ( m < 0 || m >= height ) continue;   //beyond the border

                for (int  l=-1; l <=5; l++ )
                {

                    n = j + l;

                    if ( n < 0 || n >= width ) continue; //beyond the border


                    pixelValue = grayScaleInput[m][n];
                    //cout << fabs( grayScaleInput[i][j] - pixelValue )<< "\n";
                    if ( fabs( grayScaleInput[i][j] - pixelValue ) < sigma )
                    {
                        sum += pixelValue;
                        no++;
                    }
                }
            }
            if ( no > 0 )
            {
                grayScaleOuput[i][j] = sum/no ;
                cout << grayScaleOuput[i][j] << "\n";
            }
            else
            {

                grayScaleOuput[i][j] = grayScaleInput[i][j]; //just copy
            }
        }

        //============== end for (int y... =====================
    }

    imageOuput.setGraysScale(grayScaleOuput);





    return imageOuput;
}
