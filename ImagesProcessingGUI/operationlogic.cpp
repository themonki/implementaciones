#include "operationlogic.h"

OperationLogic::OperationLogic()
{
    //Constructor por defecto
}

Image OperationLogic::binaryOperations(Image &image1, Image &image2, binaryOperation operation)
{
    Image imageOuput;
    if(image1.getHeight()!=image2.getHeight() || image1.getWidth()!=image2.getWidth() ){

        cerr << "Error la operacion no se puede aplicar a la imagen";
        return imageOuput;
    }


    int height = image1.getHeight();
    int width = image1.getWidth();
    double level = image1.getLevel();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image1.getType());
    imageOuput.setLevel(level);

    matrix grayScaleInput1 = image1.getGraysScale();
    matrix grayScaleInput2 = image2.getGraysScale();
    matrix grayScaleOuput = image1.getGraysScale();

    int valueA;
    int valueB;
    cout << "Valores obtenidos "<< endl;


    // La operacion escogida fue AND
    if(operation == OperationLogic::And)
    {
        for(int i=0; i<height;i++)
        {
            for(int j=0; j<width;j++){

                valueA = round(grayScaleInput1[i][j]);
                valueB = grayScaleInput2[i][j];
                int value = valueA & valueB;

                cout << value << " ";
                if(value>level){
                    value=level;
                }else if(value < 0)
                {
                    value = 0;
                }

                grayScaleOuput[i][j] = value;
            }
            cout << endl;
        }

        // La operacion escogida fue OR
    }else if(operation == OperationLogic::Or)
    {

        for(int i=0; i<height;i++)
        {
            for(int j=0; j<width;j++)
            {

                valueA = round(grayScaleInput1[i][j]);
                valueB = grayScaleInput2[i][j];
                int value = valueA | valueB;

                cout << value << " ";
                if(value>level)
                {
                    value=level;
                }else if(value < 0)
                {
                    value = 0;
                }

                grayScaleOuput[i][j] = value;
            }
            cout << endl;
        }

    }else if(operation == OperationLogic::Xor)
    {
        for(int i=0; i<height;i++)
        {
            for(int j=0; j<width;j++){

                valueA = round(grayScaleInput1[i][j]);
                valueB = grayScaleInput2[i][j];
                int value = valueA ^ valueB;

                cout << value << " ";
                if(value>level){
                    value=level;
                }else if(value < 0)
                {
                    value = 0;
                }

                grayScaleOuput[i][j] = value;
            }
            cout << endl;
        }


    }



    imageOuput.setGraysScale(grayScaleOuput);
    return imageOuput;
}

Image OperationLogic::unaryOperations(Image &image1, unaryOperation operation)
{
    Image imageOuput;

    int height = image1.getHeight();
    int width = image1.getWidth();
    double level = image1.getLevel();

    imageOuput.setHeight(height);
    imageOuput.setWidth(width);
    imageOuput.setType(image1.getType());
    imageOuput.setLevel(level);

    matrix grayScaleInput1 = image1.getGraysScale();

    matrix grayScaleOuput = image1.getGraysScale();

    int valueA;

    cout << "Valor obtenidos "<< endl;


    // La operacion escogida fue AND
    if(operation == OperationLogic::Not)
    {
        for(int i=0; i<height;i++)
        {
            for(int j=0; j<width;j++){

                valueA = round(grayScaleInput1[i][j]);

                int value = ~valueA;

                cout << value << " ";
                if(value < 0)
                {
                    value = fabs(value);
                }

                if(value>level){
                    value=level;
                }

                grayScaleOuput[i][j] = value;
            }
            cout << endl;
        }
    }


    return imageOuput;


}
