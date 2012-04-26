#ifndef CONTROLER_H
#define CONTROLER_H

#include <QImage>
#include <QColor>
#include <QString>
#include "image.h"


class Controler
{
private:
    Image* imageIn;
    Image* imageOut;
    QImage* imageInLabel;
    QImage* imageOutLabel;
    QImage* convertImageIn();
    QImage* convertImageOut();
    QImage* convertImage(Image*);
    bool ppmImage;
    bool dicomImage;
public:
    Controler();
    void openImage(QString);
    void saveImage(QString, QImage*);
    void setImageIn(QImage*);
    void setImageOut(QImage*);
    QImage* getImageIn();
    QImage* getImageOut();

};

#endif // CONTROLER_H
