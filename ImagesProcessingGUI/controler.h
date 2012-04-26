#ifndef CONTROLER_H
#define CONTROLER_H

#include <QImage>
#include "image.h"


class Controler
{
private:
    Image image;
    QImage imageIn;
    QImage imageOut;
public:
    Controler();
    void openImage(string);
    void saveImage(string);
    void setImageIn(Image);
    void setImageOut(Image);
    QImage getImageIn();
    QImage getImageOut();

};

#endif // CONTROLER_H
