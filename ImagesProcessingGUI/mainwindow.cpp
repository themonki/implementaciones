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


void MainWindow::createMenus(){

    this->fileMenu = menuBar()->addMenu(tr("&Archivo"));
    fileMenu->addAction(createActionOpenFile());
    fileMenu->addAction(createActionSaveFile());
    menuSaveFile->setEnabled(false);


}



void MainWindow::openFile(){

    QString temp = QFileDialog::getOpenFileName( this,"Seleccionar Imagen a Buscar",this->path,"Imagenes pgm o Dicom (*.pgm *.ppm *dcm)");
    if(temp.isNull()){
        return;
    }
    this->path=temp;
    this->controler.openImage(path);
    this->menuSaveFile->setEnabled(true);


    ui->labelImageIn->setPixmap(QPixmap::fromImage(*controler.getImageIn()));    
    ui->labelImageIn->setScaledContents(true);
    ui->labelImageOut->setPixmap(QPixmap::fromImage(*controler.getImageIn()));
    ui->labelImageOut->setScaledContents(true);

}

void MainWindow::saveFile(){
    QString temp = QFileDialog::getSaveFileName(this,"Seleccionar lugar y nombre del archivo", this->path, "Imagenes pgm o Dicom (*.pgm *.ppm *dcm)");
    if(temp.isNull()){
        return;
    }
    this->controler.saveImage(temp, controler.getImageOut());
    this->menuSaveFile->setStatusTip(tr("El archivo se ha guardado correctamente"));
}
