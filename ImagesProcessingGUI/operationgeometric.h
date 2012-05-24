#ifndef OPERATIONGEOMETRIC_H
#define OPERATIONGEOMETRIC_H

#include "image.h"

class OperationGeometric
{
public:
    OperationGeometric();
    Image scaleBilinearGray(Image& image, double scale);
};

#endif // OPERATIONGEOMETRIC_H
