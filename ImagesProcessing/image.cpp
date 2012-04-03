    #include "image.h"

const double Wr=0.299, Wg=0.587, Wb=0.114, Umax=0.436, Vmax=0.615; //Definicion de constantes


Image::Image(string path)
{
    this->path = path;
    readImage();
}

void Image::readImage()
{

    ifstream imageIn(path.c_str(), ios::binary);

    string content;
    int count=0;

    if(!imageIn.is_open()){
        cerr << "Error: ¡La imagen no existe o no pudo ser cargada!" << endl;
        abort();
    }

    while(count<4){
        imageIn >> content;

        if(content.substr(0, 1).compare("#")){ //Si la linea no es un comentario se guardan los datos
            if(count==0){
                if(content.compare("P2") && content.compare("P3") && content.compare("P5") && content.compare("P6")){
                    cerr << "Error: ¡La imagen no es de tipo PGM " << content << endl;
                    return;
                }
                else{
                    this->type=content;
                }

            }
            if(count == 1){
                this->height=atoi(content.c_str());
            }
            if(count == 2){
                this->width=atoi(content.c_str());
            }
            if(count == 3){
                this->level=atoi(content.c_str());
            }

            count++;
        }else getline(imageIn, content); //Si es un comentario se descarta el resto de linea
    }

    if(!this->type.compare("P2")){ //Si la imagen es en escala de grises

        this->graysScale.resize(this->height);
        for(int i=0; i<this->height; i++)
                this->graysScale[i].resize(this->width);

        for(int i=0;i<this->height;i++){ //Hasta que se haya llenado la matriz Y

            for(int j=0;j<this->width;j++)
            {
                imageIn >> content;

                if(content.substr(0, 1).compare("#")){ //Si la linea no es un comentario se guardan los datos
                    int value = atoi(content.c_str());

                    if(isRangeLevel(value)){
                        this->graysScale[i][j]=value;
                    }else{
                        //cerr << "Valor fuera del rango de nivel";
                        const char* s= "GrayValue-readImage";
                        throw(ImageExeption(VALOR_FUERA_RANGO_NIVEL,s ));
                    }
                }else{
                    getline(imageIn, content);
                    i--;
                } //Si es un comentario se descarta el resto de linea
            }
        }

        cout << "Bien: ¡La imagen se leyo correctamente" << endl;
    }else if(!this->type.compare("P3")){	//Si la imagen es a color

        //Se le dan tamaño a las matrices RGB
        this->red.resize(this->height);
        this->green.resize(this->height);
        this->blue.resize(this->height);

        for(int i=0; i<this->height; i++){
                this->red[i].resize(this->width);
                this->green[i].resize(this->width);
                this->blue[i].resize(this->width);
        }



        for(int i=0; i<this->height;i++){

            for(int j=0; j<this->width;j++){

                if(content.substr(0, 1).compare("#")){ //Si la linea no es un comentario se guardan los datos

                    int value;
                    imageIn >> content; //R
                    value = atoi(content.c_str());


                    if(isRangeLevel(value)){
                         red[i][j] = value;
                    }else{
                        const char* s= "RedValue-readImage";
                        throw(ImageExeption(VALOR_FUERA_RANGO_NIVEL), s);
                    }

                    imageIn >> content; //G
                    value = atoi(content.c_str());
                    if(isRangeLevel(value)){
                        green[i][j] = value;
                    }else{
                        const char* s= "GreenValue-readImage";
                        throw(ImageExeption(VALOR_FUERA_RANGO_NIVEL, s));
                    }

                    imageIn >> content; //B
                    value = atoi(content.c_str());
                    if(isRangeLevel(value)){
                        blue[i][j] = value;
                    }else{
                        const char* s= "BlueValue-readImage";
                        throw(ImageExeption(VALOR_FUERA_RANGO_NIVEL), s);
                    }

                }else{
                    getline(imageIn, content);
                    i--;
                } //Si es un comentario se descarta el resto de linea
            }

        }


    }else if(!this->type.compare("P5")){

        //Lectura P5






    }else if(!this->type.compare("P6")){

        //Lectura P6




    }


    imageIn.close();

}

//Retorna el tipo de imagen (P2, P3, etc.)
string Image::getType(){
        return type;
}


//Retorna el ancho de la imagen
int Image::getWidth(){
        return width;
}





//Retorna el alto de la imagen
int Image::getHeight(){
        return height;
}





//Retorna la escala de color de la imagen
int Image::getLevel(){
        return level;
}





//Retorna la matriz de rojo a la imagen
matrix Image::getRed(){
        return red;
}





//Retorna la matriz de verde a la imagen
matrix Image::getGreen(){
        return green;
}





//Retorna la matriz de azul a la imagen
matrix Image::getBlue(){
        return blue;
}





//Le asigna la matriz de azul a la imagen
matrix Image::getGraysScale(){
        return graysScale;
}





//Le asigna el ancho de la imagen
void Image::setWidth(int width){
        this->width=width;
}





//Le asigna el alto de la imagen
void Image::setHeight(int height){
        this->height=height;
}





//Le asigna la escala de color de la imagen
void Image::setLevel(int level){
        this->level=level;
}





//Le asigna la matriz de rojo a la imagen
void Image::setRed(matrix red){
        this->red=red;
}





//Le asigna la matriz de verde a la Imagen
void Image::setGreen(matrix green){
        this->green=green;
}





//Le asigna la matriz de azul a la imagen
void Image::setBlue(matrix blue){
        this->blue=blue;
}





//Le asigna la matriz de grises a la imagen
void Image::setGraysScale(matrix graysScale){
        this->graysScale=graysScale;
}





//Calcula la escala de grises de una imagen a color
void Image::colorToGraysScale(){
        //Se le dan tamaño a la matriz Y
        this->graysScale.resize(this->height);
        for(int i=0; i<this->height; i++)
                this->graysScale[i].resize(this->width);

        //Se hacen las operaciones para hallar los valores de la matriz Y
        for(int i=0; i<this->height; i++)
                for(int j=0; j<this->width; j++)
                        this->graysScale[i][j]=Wr*this->red[i][j]+Wg*this->green[i][j]+Wb*this->blue[i][j]; //Hallar Y
}





//Se guarda la imagen
void Image::saveImage(string path){


        ofstream imageOut(path.c_str(), ios::binary);
        if(!path.substr(path.length()-4, 4).compare(".pgm")){ //Si la ruta es una imagen en escala de grises

            if(!this->type.compare("P2"))
            {
            imageOut << "P2\n# Pruebas Procesamiento de Imagenes \n";
            imageOut << height << " " << width << "\n";
            imageOut << level << "\n";

            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    int value = round(graysScale[i][j]);
                    if(isRangeLevel(value)){
                        imageOut << value << "\t";
                    }else{
                        const char* s= "GrayValue-saveImage";
                        throw ImageExeption(VALOR_FUERA_RANGO_NIVEL, s);
                    }

                }
                imageOut <<"\n";
            }
            }else if(!this->type.compare("P5"))
            {
                    //Escritura de imagen para P5

            }else
            {
                    //Tipo de imagen no corresponde a la extension dada
            }

            imageOut.close();
        }else if(!path.substr(path.length()-4, 4).compare(".ppm")){ //Si la ruta es una imagen a color

            if(!this->type.compare("P3"))
            {

                imageOut << "P3\n# Pruebas Procesamiento de Imagenes\n";
                imageOut << height << " " << width << "\n";
                imageOut << level << "\n";
                for(int i=0; i<height; i++){
                        for(int j=0; j<width; j++){
                            int valueRed = round(red[i][j]), valueBlue = round(blue[i][j]), valueGreen = round(green[i][j]);
                            if(isRangeLevel(valueRed) && isRangeLevel(valueBlue) &&isRangeLevel(valueGreen)){
                                imageOut << valueRed << " " << valueGreen << " " << valueBlue << "\t";
                            }else{
                                const char* s= "ColorValue-saveImage";
                                throw ImageExeption(VALOR_FUERA_RANGO_NIVEL, s);
                            }
                        }
                        imageOut << "\n";
                }
            }else if(!this->type.compare("P6"))
            {

                    //Escritura de imagen para P6

            }else
            {

                    //Tipo de imagen no corresponde a la extension dada

            }
                imageOut.close();
                cout << "La imagen se guardo correctamente";
        }else if(path.substr(path.length()-4, 4).compare(".pgm") && path.substr(path.length()-4, 4).compare(".ppm")){ //Si la ruta de la imagen esta en otro formato
                imageOut.close();
                const char* s= "saveImage";
                throw ImageExeption(EXTENSION_DESCONOCIDA, s);
                //cerr << "Error: ¡La ruta de la imagen no es valida!\n";
        }
}



int Image::round(double number){

    return floor(number+0.5);
}

bool Image::isRangeLevel(int number){
    return (number>=0 && number<=this->level);
}


/*matrix Image::scaleImage(int height2, int width2){

}*/

