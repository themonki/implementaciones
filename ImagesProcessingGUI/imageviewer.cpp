/****************************************************************************
 **
 ** Copyright (C) 2005-2007 Trolltech ASA. All rights reserved.
 **
 ** This file is part of the example classes of the Qt Toolkit.
 **
 ** This file may be used under the terms of the GNU General Public
 ** License version 2.0 as published by the Free Software Foundation
 ** and appearing in the file LICENSE.GPL included in the packaging of
 ** this file.  Please review the following information to ensure GNU
 ** General Public Licensing requirements will be met:
 ** http://www.trolltech.com/products/qt/opensource.html
 **
 ** If you are unsure which license is appropriate for your use, please
 ** review the following information:
 ** http://www.trolltech.com/products/qt/licensing.html or contact the
 ** sales department at sales@trolltech.com.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **
 ****************************************************************************/

 #include <QtGui>

 #include "imageviewer.h"

ImageViewer::ImageViewer(QWidget *parent):QMainWindow(parent)
 {
     imageLabel = new QLabel;
     imageLabel->setBackgroundRole(QPalette::Dark);
     imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel->setScaledContents(true);

     scrollArea = new QScrollArea;
     scrollArea->setBackgroundRole(QPalette::Dark);
     scrollArea->setWidget(imageLabel);
     setCentralWidget(scrollArea);

     resize(500, 400);
 }
ImageViewer::ImageViewer(Image img2, QImage image, QString title, QWidget *parent):QMainWindow(parent)
{
    this->img = new Image();
    img->setBlue(img2.getBlue());
    img->setGraysScale(img2.getGraysScale());
    img->setGreen(img2.getGreen());

    img->setHeight(img2.getHeight());
    img->setLevel(img2.getLevel());
    img->setRed(img2.getRed());
    img->setType(img2.getType());
    img->setWidth(img2.getWidth());

    initComponents(image,title);
    createActions();
    createMenus();
}
 ImageViewer::ImageViewer(QImage image,QString title, QWidget *parent):QMainWindow(parent)
 {
    initComponents(image,title);

 }

 void ImageViewer::initComponents(QImage image, QString title){
     if (image.isNull()) {
         QMessageBox::information(this, tr("Image Viewer"), tr("No se puede cargar la imagen"));
         return;
     }
     imageLabel = new QLabel;
     imageLabel->setBackgroundRole(QPalette::Dark);
     imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

     scrollArea = new QScrollArea;
     scrollArea->setBackgroundRole(QPalette::Dark);
     scrollArea->setWidget(imageLabel);
     setCentralWidget(scrollArea);

     imageLabel->setPixmap(QPixmap::fromImage(image));
     imageLabel->adjustSize();

     this->setWindowTitle(title);
     resize(500, 400);
     this->show();

     scaleFactor = 1.0;
 }

 QLabel* ImageViewer::getImageLabel(){return this->imageLabel;}

 QWidget* ImageViewer::getWidget(){return centralWidget();}

 void ImageViewer::createActions()
 {
     exitAct = new QAction(tr("E&xit"), this);
     exitAct->setShortcut(tr("Ctrl+Q"));
     connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

     zoomInAct = new QAction(tr("Zoom &In (25%)"), this);
     zoomInAct->setShortcut(tr("Ctrl++"));
     connect(zoomInAct, SIGNAL(triggered()), this, SLOT(scaleUp()));

     zoomOutAct = new QAction(tr("Zoom &Out (25%)"), this);
     zoomOutAct->setShortcut(tr("Ctrl+-"));
     connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(scaleDown()));
}




 void ImageViewer::createMenus()
 {
     fileMenu = new QMenu(tr("&File"), this);
     fileMenu->addAction(exitAct);

     viewMenu = new QMenu(tr("&View"), this);
     viewMenu->addAction(zoomInAct);
     viewMenu->addAction(zoomOutAct);


     menuBar()->addMenu(fileMenu);
     menuBar()->addMenu(viewMenu);
 }

 void ImageViewer::scaleImage(double factor)
 {
     OperationGeometric opg;
     Image temp = opg.scaleBilinearGray(*img,(double) fabs( factor));
     temp.saveImage("file.pgm");
     QImage scalada("file.pgm");

     imageLabel->setPixmap(QPixmap::fromImage(scalada));
     imageLabel->adjustSize();


     zoomInAct->setEnabled(scaleFactor < 3.0);
     zoomOutAct->setEnabled(scaleFactor > 0.333);

 }


 void ImageViewer::changeEvent(QEvent *e)
 {
   QMainWindow::changeEvent(e);
   switch (e->type())
   {
   case QEvent::LanguageChange:
     //ui->retranslateUi(this);
     break;
   default:
     break;
   }
 }

 //Added
 void ImageViewer::resizeEvent(QResizeEvent*)
 {
   /*static int n_times = 0;
   QString s; s = s.number(n_times);

   setWindowTitle("hola " + s);
   ++n_times;
*/
 }



 void ImageViewer::wheelEvent(QWheelEvent *e){//para escalar imagen
     return;
     if (e->modifiers().testFlag(Qt::ControlModifier)){ // zoom only when CTRL key pressed
         int scale = e->delta()/120;

         if (scale == 0) {
             e->ignore();
             return;
         }else if(scale<0){

            /* OperationGeometric opg;
             Image temp = opg.scaleBilinearGray(*img,(double)(fabs(scale)*0.2));
             temp.saveImage("file.pgm");
             QImage scalada("file.pgm");
             QLabel *label= (QLabel*)(ui->viewport);

             label->setPixmap(QPixmap::fromImage(scalada));
             //ui->viewport = label;
             ui->viewport->update();*/

         }else {//mayor
             /*OperationGeometric opg;
             Image temp = opg.scaleBilinearGray(*img,(double)  scale);
             temp.saveImage("file.pgm");
             QImage scalada("file.pgm");
             QLabel *label= new QLabel;
             label->setPixmap(QPixmap::fromImage(scalada));
             ui->viewport = label;
             ui->viewport->update();*/

         }

         e->accept();

     }

 }

 void ImageViewer::scaleDown(){
     this->scaleFactor*=0.8;
     scaleImage(this->scaleFactor);

 }

 void ImageViewer::scaleUp(){
     this->scaleFactor*=1.25;
     scaleImage(this->scaleFactor);
 }
/*
 void ImageViewer::scaleImage(double scale){
     OperationGeometric opg;
     Image temp = opg.scaleBilinearGray(*img,(double) fabs( scale));
     temp.saveImage("file.pgm");
     QImage scalada("file.pgm");
     QLabel *label= (QLabel*)(ui->viewport);
     label->setPixmap(QPixmap::fromImage(scalada));
     //ui->viewport->update();

     //ui->buttonScaleUp->setEnabled(numScale < 3.0);
     //ui->buttonScaleDown->setEnabled(numScale > 0.333);
 }*/
