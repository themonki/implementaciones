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
                //                cout << grayScaleOuput[i][j] << "\n";
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


double* Filter::calculateVariance(matrix grayScaleInput, int posPixelX, int posPixelY, int win, int dif, int subwind){
    double varianza;
    double *result;
    result = new double[2];
    int count = ceil((double)(win)/2);// tamaño de la subventana
    vector<double> nums;
    double sum=0;
    int posX = posPixelX-dif, posY = posPixelY-dif, posWind = floor((double)(win)/4);
    //la ubicacion de la ventana
    if (subwind==1) {
        posX = posX+posWind;
    }else if(subwind==2){
        posX = posX+posWind*2;
    }else if(subwind==3){
        posY = posY+posWind;
    }else if(subwind==4){
        posY = posY+posWind;
        posX = posX+posWind;
    }else if(subwind==5){
        posY = posY+posWind;
        posX = posX+posWind*2;
    }else if(subwind==6){
        posY = posY+posWind*2;
    }else if(subwind==7){
        posY = posY+posWind*2;
        posX = posX+posWind;
    }else if(subwind==8){
        posY = posY+posWind*2;
        posX = posX+posWind*2;
    }/**/

    //cerr << posX << " " << posY << " - " << posPixelX << " " <<posPixelY << endl;
    //se obtienen los pixeles de la ventana para calcular
    for(int x = posX; x < posX+count; x++){
        for(int y = posY; y < posY+count;y++){
            if((x!=posPixelX) || (y!=posPixelY)){
                double value = grayScaleInput[x][y];
                nums.push_back(value);
                sum += value;
            }
        }
    }

    double media = sum/(double)(nums.size());
    count =0;
    sum = 0.0;

    for(int x = 0; x < (int)nums.size();x++){
        sum += (nums[count]-media)*(nums[count]-media);
    }

    varianza= sum / (double)(nums.size());

    result[0] = varianza;
    result[1] = media;

    return result;

}

Image Filter::nagao_MatsuyamaFilter(Image &image, int win){
    Image imageOuput;

    int height = image.getHeight();
    int width = image.getWidth();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(image.getLevel());

    matrix grayScaleInput = image.getGraysScale();
    matrix grayScaleOuput = image.getGraysScale();


    int dif = ceil((double)(win)/2) - (win%2),  rest = (win-dif)-1;
    cout << dif<<"dif\n";
    for(int x = dif; x < height-rest; x++){
        for(int y = dif; y < width-rest; y++){
            double *value, *temp;
            value = new double[2];
            value[0]=-1;
            if(x<100 && y < 100){// esto ahi q quitarlo es solo para limitar
                for(int subWind = 0 ; subWind<9 ; subWind++){//nueve subventanas
                    //cout << subWind << "*********************+subwind"<<endl;
                    temp = calculateVariance(grayScaleInput,x,y,win,dif, subWind);
                        if(value[0]==-1){
                            value[1]=temp[1];
                            value[0]=temp[0];
                        }else{
                            if(value[0]>temp[0]){
                                value[0]=temp[0];
                                value[1]=temp[1];
                            }
                        }
                }
                //cout << value[1] << endl;
                grayScaleOuput[x][y]=value[1];
            }else{
                grayScaleOuput[x][y]=grayScaleInput[x][y];

            }

        }
    }

    imageOuput.setGraysScale(grayScaleOuput);

    return imageOuput;

}


Image Filter::noiseCleaningPixel(Image &image, double delta){
    Image imageOuput;

    int height = image.getHeight();
    int width = image.getWidth();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(image.getLevel());

    matrix grayScaleInput = image.getGraysScale();
    matrix grayScaleOuput = image.getGraysScale();


    for(int i =1; i< height-1; i++){
        for(int j =1; j< width-1; j++){
            double test=grayScaleInput[i][j], neighbors,sum=0;
            sum+=grayScaleInput[i-1][j-1];
            sum+=grayScaleInput[i-1][j];
            sum+=grayScaleInput[i-1][j+1];
            sum+=grayScaleInput[i][j-1];
            sum+=grayScaleInput[i][j+1];
            sum+=grayScaleInput[i+1][j-1];
            sum+=grayScaleInput[i+1][j];
            sum+=grayScaleInput[i+1][j+1];
            neighbors = sum / 8.0;

            if(fabs(test - neighbors) > delta){
                grayScaleOuput[i][j]=neighbors;
            }else{
                grayScaleOuput[i][j]=test;
            }
        }
    }

    imageOuput.setGraysScale(grayScaleOuput);

    return imageOuput;


}

Image Filter::noiseCleaningLine(Image &image, double delta){
    Image imageOuput;

    int height = image.getHeight();
    int width = image.getWidth();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image.getType());
    imageOuput.setLevel(image.getLevel());

    matrix grayScaleInput = image.getGraysScale();
    matrix grayScaleOuput = image.getGraysScale();


    for(int i =0; i< height; i++){
        for(int j =2; j< width-2; j++){
            double test=grayScaleInput[i][j], neighbors,sum=0;
            sum+=grayScaleInput[i][j-1];
            sum+=grayScaleInput[i][j-2];
            sum+=grayScaleInput[i][j+1];
            sum+=grayScaleInput[i][j+2];
            neighbors = sum / 4.0;

            if(fabs(test - neighbors) > delta){
                grayScaleOuput[i][j]=neighbors;
            }else{
                grayScaleOuput[i][j]=test;
            }
        }
    }

    imageOuput.setGraysScale(grayScaleOuput);

    return imageOuput;
}


