#include "image.h"

//#define HI(num) (((num) & 0x0000FF00) >> 8)
//#define LO(num) ((num) & 0x000000FF)


Image::Image()
{

}

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
                this->width=atoi(content.c_str());
            }
            if(count == 2){
                this->height=atoi(content.c_str());
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

        cout << "Bien: ¡La imagen se leyo correctamente" << endl;

    }else if(!this->type.compare("P5")){

        //Lectura P5
        this->graysScale.resize(this->height);
        for(int i=0; i<this->height; i++)
            this->graysScale[i].resize(this->width);


        //unsigned char *charImage = (unsigned char *) new unsigned char [this->height*this->width];  //creates 2D array
        //imageIn.read( reinterpret_cast<char *>(charImage), (this->height*this->width)*sizeof(unsigned char));  //reads in 2D array

        //if (imageIn.fail())
        //{
        //arrojar expecion de rango de datos o noc
        //cout << "Image " << 34 << " has wrong size" << endl;
        //}

        //imageIn.close();
        // Convert the unsigned characters to integers

        int val;

        for(int i=0; i<this->height; i++)
            for(int j=0; j<this->width; j++)
            {
                val = imageIn.get();//(int)charImage[i*this->width+j];
                this->graysScale[i][j]= val;
            }

        //delete [] charImage;

        cout << "Bien: ¡La imagen se leyo correctamente " << this->type<< endl;

    }else if(!this->type.compare("P6")){

        //Lectura P6
        this->blue.resize(this->height);
        this->green.resize(this->height);
        this->red.resize(this->height);
        for(int i=0; i<this->height; i++){
            this->blue[i].resize(this->width);
            this->red[i].resize(this->width);
            this->green[i].resize(this->width);
        }

        int val;
        imageIn.get();
        for(int i=0; i<this->height; i++)
            for(int j=0; j<this->width; j++)
            {
                val = imageIn.get(); //(int)charImage[i*this->width+j];
                this->red[i][j]= val;
                val = imageIn.get();
                this->green[i][j]= val;
                val = imageIn.get();
                this->blue[i][j]= val;




            }

        //this->type = "P3";//esto se tiene que quitar para guardar en p6

        cout << "Bien: ¡La imagen se leyo correctamente p6" << this->type<< endl;

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

void Image::setType(string type){
    this->type=type;
}





//Le asigna la matriz de grises a la imagen
void Image::setGraysScale(matrix graysScale){
    this->graysScale=graysScale;
}





//Calcula la escala de grises de una imagen a color
void Image::colorToGraysScale(){
    if(!this->type.compare("P6") || !this->type.compare("P3")){

        if(this->graysScale.size() == (unsigned)height){
            for(int i = 0; i < height; i++){
                this->graysScale[i].clear();

            }
            this->graysScale.clear();
        }
        //Se le dan tamaño a la matriz Y
        this->graysScale.resize(this->height);
        for(int i=0; i<this->height; i++)
            this->graysScale[i].resize(this->width);

        //Se hacen las operaciones para hallar los valores de la matriz Y
        for(int i=0; i<this->height; i++)
            for(int j=0; j<this->width; j++)
                this->graysScale[i][j]=Wr*this->red[i][j]+Wg*this->green[i][j]+Wb*this->blue[i][j];

        this->type="P2";
        /*Para no perder los datos*//*
        for(int i = 0; i < height; i++){
            this->blue[i].clear();
            this->red[i].clear();
            this->green[i].clear();
        }
        this->blue.clear();
        this->red.clear();
        this->green.clear();
        /**/

    }
}






//Se guarda la imagen
void Image::saveImage(string path){


    ofstream imageOut(path.c_str(), ios::out|ios::binary);
    if(!path.substr(path.length()-4, 4).compare(".pgm")){ //Si la ruta es una imagen en escala de grises

        if(!this->type.compare("P2"))
        {
            imageOut << "P2\n# Pruebas Procesamiento de Imagenes \n";
            imageOut << width << " " << height << "\n";
            imageOut << level << "\n";

            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    int value = round(graysScale[i][j]);
                    if(isRangeLevel(value)){
                        imageOut << value << "\t";
                    }else{
                        cout << value << " - "<<graysScale[i][j] << " - "<< i << " - "<<j << endl;
                        const char* s= "GrayValue-saveImage";
                        throw ImageExeption(VALOR_FUERA_RANGO_NIVEL, s);
                    }

                }
                imageOut <<"\n";
            }
        }else if(!this->type.compare("P5"))
        {
            //Escritura de imagen para P5

            imageOut << "P5\n# Pruebas Procesamiento de Imagenes \n";
            imageOut << width << " " << height << "\n";
            imageOut << level << "\n";
            unsigned char *image;
            image = (unsigned char *) new unsigned char [this->height*this->width];

            for(int i=0; i<this->height; i++)
                for(int j=0; j<this->width; j++)
                    image[i*this->width+j]=(unsigned char)graysScale[i][j];



            imageOut.write( reinterpret_cast<char *>(image), (this->width*this->height)*sizeof(unsigned char));
            delete [] image;


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
                        //cerr << valueRed << " " << valueGreen << " " << valueBlue << "\t";
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

            imageOut << "P6\n# Pruebas Procesamiento de Imagenes \n";
            imageOut << width << " " << height << "\n";
            imageOut << level << "\n";

            for(int i=0; i<this->height; i++)
                for(int j=0; j<this->width; j++){

                    imageOut.put((unsigned char)red[i][j]);
                    imageOut.put((unsigned char)green[i][j]);
                    imageOut.put((unsigned char)blue[i][j]);

                }
        }else
        {

            //Tipo de imagen no corresponde a la extension dada

        }
        imageOut.close();
    }else if(path.substr(path.length()-4, 4).compare(".pgm") && path.substr(path.length()-4, 4).compare(".ppm")){ //Si la ruta de la imagen esta en otro formato
        imageOut.close();
        const char* s= "saveImage";
        throw ImageExeption(EXTENSION_DESCONOCIDA, s);
        //cerr << "Error: ¡La ruta de la imagen no es valida!\n";
    }

    cout << "La imagen se guardo correctamente \n";

}

void Image::clearImage(){
    //para limpiar todos los vectores y datos
    if(graysScale.size()==(unsigned)height){
        if(this->graysScale.size() == (unsigned)height){
            for(int i = 0; i < height; i++){
                this->graysScale[i].clear();

            }
            this->graysScale.clear();
        }
    }else if(blue.size()==(unsigned)height){
        for(int i = 0; i < height; i++){
            this->blue[i].clear();
            this->red[i].clear();
            this->green[i].clear();
        }
        this->blue.clear();
        this->red.clear();
        this->green.clear();
    }

    this->width=0;
    this->height=0;
    this->type.clear();
    this->level=0;
    this->path.clear();
}

int Image::round(double number){

    return floor(number+0.5);
}

bool Image::isRangeLevel(int number){
    return (number>=0 && number<=this->level);
}

void Image::readDicomImage(string path)
{


    DcmFileFormat fileformat;
    OFCondition status = fileformat.loadFile(path.c_str());
    if (status.good())
    {
        OFString patientName;
        if (fileformat.getDataset()->findAndGetOFString(DCM_PatientName, patientName).good())
        {
            cout << "Patient's Name: " << patientName << endl;
        } else
            cerr << "Error: cannot access Patient's Name!" << endl;
    } else
        cerr << "Error: cannot read DICOM file (" << status.text() << ")" << endl;


    DicomImage *image = new DicomImage(path.c_str());

    image->getStatus();

    width = image->getWidth();
    height = image->getHeight();
    level = 255;
    type = "P2";


    this->graysScale.resize(this->height);



    if (image != NULL)
    {
        if (image->getStatus() == EIS_Normal)
        {

            Uint8 *pixelData = (Uint8 *)(image->getOutputData(8)); // bits per sample

            if (pixelData != NULL)
            {
                int contador = 0;
                for(int i=0;i<height;i++)
                {
                    this->graysScale[i].resize(this->width);
                    for(int j=0;j<width;j++)
                    {

                        graysScale[i][j] = static_cast< int >( pixelData[contador] );
                        contador++;
                    }

                }

                string pgmPath = path.substr(0,path.length()-4)+".pgm";
                cout << pgmPath << endl;
                saveImage(pgmPath);


            }
        } else
            cerr << "Error: cannot load DICOM image (" << DicomImage::getString(image->getStatus()) << ")" << endl;
    }
    delete image;



}


