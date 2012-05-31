#ifndef OPERATIONLOGIC_H
#define OPERATIONLOGIC_H

#include "image.h"


class OperationLogic
{
public:

    enum binaryOperation{And, Or, Xor};
    enum unaryOperation{Not};


    OperationLogic();

    Image binaryOperations(Image& image1, Image& image2, binaryOperation operation );
    Image unaryOperations(Image& image1,unaryOperation operation);

};
#endif // OPERATIONLOGIC_H
