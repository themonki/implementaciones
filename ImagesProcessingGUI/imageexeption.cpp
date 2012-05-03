#include "imageexeption.h"

ImageExeption::ImageExeption(int mot) : exception(), motive(mot)
{
    this->description = "";
}

ImageExeption::ImageExeption(int mot, const char* des) : exception(), motive(mot), description(des)
{
}

const char* ImageExeption::what() const throw(){
    switch(this->motive){
    case VALOR_FUERA_RANGO_NIVEL: return "El valor esta por fuera del Rango de Nivel.\n"; break;
    case EXTENSION_DESCONOCIDA: return "El archivo tiene una extension invalida o desconocida.\n"; break;
    case CONTENIDO_IMAGEN_DESCONOCIDO: return "El archivo no contiene el formato adecuado.\n"; break;
    case ARCHIVO_NO_EXISTE: return "El archivo no existe.\n"; break;
    default: return "Error Desconocido";
    }
}

int ImageExeption::getMotive(){
    return this->motive;
}

const char* ImageExeption::getDescription(){
    return this->description;
}

string ImageExeption::getMessage(){
    string exp ("Error:");
    stringstream strm;
    string num;
    strm << this->motive;
    strm >> num;
    exp.append(num);
    exp.append(" - ");
    exp.append(this->description);
    exp.append("\n");
    exp.append(this->what());
    return exp;
}
