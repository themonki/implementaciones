#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);






    this->path = QDir::homePath();
    this->createMenus();
    ui->menubar->addMenu(this->fileMenu);
    ui->menubar->addMenu(this->filterMenu);
    ui->menubar->addMenu(this->HistogramMenu);
    ui->menubar->addMenu(this->helpMenu);

    setWindowTitle(tr("Image Processing"));

    /*************CENTRAR EN PANTALLA*************************/
    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth, width;
    int screenHeight, height;
    int x, y;
    QSize windowSize;

    screenWidth = desktop->width(); // get width of screen
    screenHeight = desktop->height(); // get height of screen

    windowSize = size(); // size of our application window
    width = windowSize.width();
    height = windowSize.height();

    // little computations
    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;
    y -= 50;

    // move window to desired coordinates
    move ( x, y );

    /**************************************/

}

MainWindow::~MainWindow()
{
    delete ui;
}


QAction* MainWindow::createActionOpenFile()
 {
     QAction *act;
     act = new QAction(tr("&Abrir"), this);
     act->setShortcuts(QKeySequence::Open);
     act->setStatusTip(tr("Abre un archivo de imagen"));
     connect(act, SIGNAL(triggered()), this, SLOT(openFile()));
     this->menuOpenFile = act;
     return act;
}

QAction* MainWindow::createActionSaveFile()
 {
     QAction *act;
     act = new QAction(tr("&Guardar"), this);
     act->setShortcuts(QKeySequence::SaveAs);
     connect(act, SIGNAL(triggered()), this, SLOT(saveFile()));
     this->menuSaveFile = act;
     return act;
}

QAction* MainWindow::createActionFilterSigma()
 {
     QAction *act;
     act = new QAction(tr("Filtro &Sigma"), this);
     //act->setShortcuts(QKeySequence::SaveAs);
     connect(act, SIGNAL(triggered()), this, SLOT(applyFilterSigma()));
     act->setStatusTip(tr("Aplica el filtro sigma"));
     this->menuApplyFilterSigma = act;
     return act;
}

QAction* MainWindow::createActionFilterMedian()
 {
     QAction *act;
     act = new QAction(tr("Filtro &Median"), this);
     //act->setShortcuts(QKeySequence::SaveAs);
     connect(act, SIGNAL(triggered()), this, SLOT(applyFilterMedian()));
     act->setStatusTip(tr("Aplica el filtro de la media"));
     this->menuApplyFilterMedian = act;
     return act;
}

QAction* MainWindow::createActionHistogram()
 {
     QAction *act;
     act = new QAction(tr("&Obtener Histograma"), this);
     //act->setShortcuts(QKeySequence::SaveAs);
     connect(act, SIGNAL(triggered()), this, SLOT(getHistogram()));
     act->setStatusTip(tr("Calcula el histograma de la imagen en escala de grises"));
     this->menuHistogramGet = act;
     return act;
}

QAction* MainWindow::createActionAbout()
 {
     QAction *act;
     act = new QAction(tr("&Acerca de.."), this);
     //act->setShortcuts(QKeySequence::SaveAs);
     connect(act, SIGNAL(triggered()), this, SLOT(showAbout()));
     act->setStatusTip(tr("Acerca de la aplicación y sus creadores"));
     //this->menuAboutOf = act;
     return act;
}

void MainWindow::createMenus(){

    this->fileMenu = new QMenu(tr("&Archivo"));
    fileMenu->addAction(createActionOpenFile());
    fileMenu->addAction(createActionSaveFile());
    menuSaveFile->setEnabled(false);


    this->filterMenu = new QMenu(tr("&Filtro"));
    filterMenu->addAction(createActionFilterMedian());
    filterMenu->addAction(createActionFilterSigma());
    menuApplyFilterSigma->setEnabled(false);
    menuApplyFilterMedian->setEnabled(false);



    this->HistogramMenu = new QMenu(tr("&Histogram"));
    HistogramMenu->addAction(createActionHistogram());
    menuHistogramGet->setEnabled(false);

    this->helpMenu = new QMenu(tr("&Ayuda"));
    helpMenu->addAction(createActionAbout());



}



void MainWindow::openFile(){

    QString temp = QFileDialog::getOpenFileName( this,"Seleccionar Imagen a Buscar",this->path,"Imagenes pgm o Dicom (*.pgm *.ppm *dcm)");
    if(temp.isNull()){
        return;
    }
    this->path=temp;
    this->controler.openImage(path);
    this->menuSaveFile->setEnabled(true);
    if(!controler.isppmImage()){
        this->menuHistogramGet->setEnabled(true);

        this->menuApplyFilterMedian->setEnabled(true);
        this->menuApplyFilterSigma->setEnabled(true);
    }else{
        this->menuApplyFilterMedian->setEnabled(false);
        this->menuApplyFilterSigma->setEnabled(false);
        this->menuHistogramGet->setEnabled(false);
    }



    ui->labelImageIn->setPixmap(QPixmap::fromImage(controler.getImageIn()));
    ui->labelImageIn->setScaledContents(true);
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageIn()));
    ui->labelImageOut->setScaledContents(true);

    ui->labelHistogram->setPixmap(QPixmap::fromImage(QImage()));
    ui->labelImageIn->update();
    ui->labelImageOut->update();
    ui->labelHistogram->update();

}

void MainWindow::saveFile(){

    if(controler.isDicomImage()){

        QString temp = QFileDialog::getSaveFileName(this,"Seleccionar lugar y nombre del archivo", this->path, "Imagenes ppm (*.ppm)");
        if(temp.isNull()){
            return;
        }
        this->controler.saveImage(temp, controler.getImageOut());
        this->menuSaveFile->setStatusTip(tr("El archivo se ha guardado correctamente"));

        return;

    }
    QString temp = QFileDialog::getSaveFileName(this,"Seleccionar lugar y nombre del archivo", this->path, "Imagenes pgm (*.pgm *.ppm)");
    if(temp.isNull()){
        return;
    }
    this->controler.saveImage(temp, controler.getImageOut());
    this->menuSaveFile->setStatusTip(tr("El archivo se ha guardado correctamente"));
}

void MainWindow::applyFilterMedian(){
    this->controler.applyFilterMedian(3);
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOut()));
    ui->labelImageOut->setStatusTip("Filtro Mediana Aplicado");
    ui->labelImageOut->setScaledContents(true);
    ui->labelImageOut->update();
}

void MainWindow::applyFilterSigma(){
    this->controler.applyFilterSigma(10);
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOut()));
    ui->labelImageOut->setStatusTip("Filtro Sigma Aplicado");
    ui->labelImageOut->setScaledContents(true);
    ui->labelImageOut->update();

}

void MainWindow::getHistogram(){
    QImage a = controler.getHistogram();
    ui->labelHistogram->setPixmap(QPixmap::fromImage(a));
    ui->labelHistogram->setStatusTip("Histograma calculado");
    ui->labelHistogram->setScaledContents(true);
    ui->labelHistogram->update();
}

void MainWindow::showAbout(){
    QMessageBox dialog(this);
    dialog.setText("Aplicación para el manejo e implementacion de algoritmos para el procesamiento de imagenes.\n Integrantes:\n\tEdgar Andres Moncada\n\tYerminson Gonzalez");
    dialog.exec();



}
