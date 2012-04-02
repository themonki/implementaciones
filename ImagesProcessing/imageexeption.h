#ifndef IMAGEEXEPTION_H
#define IMAGEEXEPTION_H

#include <iostream>
#include <exception>
#include <string.h>

using namespace std;

static const int VALOR_FUERA_RANGO_NIVEL=100;
static const int EXTENSION_DESCONOCIDA=200;

class ImageExeption: public exception{
public:
    ImageExeption(int);
    ImageExeption(int, const char *);
    const char* what() const throw();
    int getMotive();
    const char* getDescription();
    const char* appendValue(const char* , const char* );
private:
    int motive;
    const char* description;


};

#endif // IMAGEEXEPTION_H
