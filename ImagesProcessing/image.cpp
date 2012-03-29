#include "image.h"

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
                this->heigh=atoi(content.c_str());
            }
            if(count == 3){
                this->level=atoi(content.c_str());
            }

            count++;
        }else getline(imageIn, content); //Si es un comentario se descarta el resto de linea
    }

    if(this->type.compare("P2") != 0 || this->type.compare("P5") !=0 ){ //Si la imagen es en escala de grises

        this->graysScale.resize(this->width);
        for(int i=0; i<this->width; i++)
                this->graysScale[i].resize(this->heigh);

        for(int i=0;i<this->width;i++){ //Hasta que se haya llenado la matriz Y

            for(int j=0;j<this->heigh;j++)
            {
                imageIn >> content;

                if(content.substr(0, 1).compare("#")){ //Si la linea no es un comentario se guardan los datos

                    this->graysScale[i][j]=atoi(content.c_str());

                }else{
                    getline(imageIn, content);
                    i--;
                    j--;
                } //Si es un comentario se descarta el resto de linea
            }
        }

        cout << "Bien: ¡La imagen se leyo correctamente" << endl;
    }else{	//Si la imagen es a color

        //Se le dan tamaño a las matrices RGB
        this->red.resize(this->width);
        this->green.resize(this->width);
        this->blue.resize(this->width);
        for(int i=0; i<this->heigh; i++){
                this->red[i].resize(this->heigh);
                this->green[i].resize(this->heigh);
                this->blue[i].resize(this->heigh);
        }



        for(int i=0; i<this->width;i++){

            for(int j=0; i<this->heigh;j++){

                if(content.substr(0, 1).compare("#")){ //Si la linea no es un comentario se guardan los datos

                    imageIn >> content; //R
                    red[i][j] = atoi(content.c_str());;

                    imageIn >> content; //G
                    green[i][j] = atoi(content.c_str());;

                    imageIn >> content; //B
                    blue[i][j] = atoi(content.c_str());

                }else{

                    getline(imageIn, content);
                    i--;
                    j--;
                } //Si es un comentario se descarta el resto de linea
            }

        }

    }


    imageIn.close();

}
