#ifndef OPERATIONARITHMETIC_H
#define OPERATIONARITHMETIC_H

#include "image.h"


class OperationArithmetic
{
public:
    OperationArithmetic();
    Image additionValue(Image& image, double add);
    Image subtractionValue(Image& image, double sub);
    Image multiplicationValue(Image& image, double mul);
    Image divisionValue(Image& image, double div);
    Image additionImages(Image& image1, Image& image2, double alfa);
    Image invertImage(Image& image);

};

#endif // OPERATIONARITHMETIC_H
