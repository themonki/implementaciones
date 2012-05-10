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
    ui->menubar->addMenu(this->histogramMenu);
    ui->menubar->addMenu(this->contrastMenu);
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

QAction* MainWindow::createActionCloseFile()
 {
     QAction *act;
     act = new QAction(tr("&Cerrar"), this);
     connect(act, SIGNAL(triggered()), this, SLOT(closeFile()));
     this->menuCloseFile = act;
     return act;
}

QAction* MainWindow::createActionFilterSigma()
 {
     QAction *act;
     act = new QAction(tr("Filtro &Sigma"), this);
     connect(act, SIGNAL(triggered()), this, SLOT(applyFilterSigma()));
     act->setStatusTip(tr("Aplica el filtro sigma"));
     this->menuApplyFilterSigma = act;
     return act;
}

QAction* MainWindow::createActionFilterMedian()
 {
     QAction *act;
     act = new QAction(tr("Filtro &Median"), this);
     connect(act, SIGNAL(triggered()), this, SLOT(applyFilterMedian()));
     act->setStatusTip(tr("Aplica el filtro de la media"));
     this->menuApplyFilterMedian = act;
     return act;
}

QAction* MainWindow::createActionFilterCleaningPixel()
 {
     QAction *act;
     act = new QAction(tr("Filtro Cleaning &Pixel"), this);
     connect(act, SIGNAL(triggered()), this, SLOT(applyFilterCleaningPixel()));
     act->setStatusTip(tr("Aplica el filtro Cleaning Pixel"));
     this->menuApplyFilterCleaningPixel = act;
     return act;
}

QAction* MainWindow::createActionFilterCleaningLine()
 {
     QAction *act;
     act = new QAction(tr("Filtro Cleaning &Line"), this);
     connect(act, SIGNAL(triggered()), this, SLOT(applyFilterCleaningLine()));
     act->setStatusTip(tr("Aplica el filtro Cleaning Line"));
     this->menuApplyFilterCleaningLine = act;
     return act;
}

QAction* MainWindow::createActionHistogram()
 {
     QAction *act;
     act = new QAction(tr("&Obtener Histograma"), this);
     connect(act, SIGNAL(triggered()), this, SLOT(getHistogram()));
     act->setStatusTip(tr("Calcula el histograma de la imagen en escala de grises"));
     this->menuHistogramGet = act;
     return act;
}

QAction* MainWindow::createActionContrastGammaCorrection()
 {
     QAction *act;
     act = new QAction(tr("Aplicar Corrección &Gamma"), this);
     connect(act, SIGNAL(triggered()), this, SLOT(applyContrastGammaCorrection()));
     act->setStatusTip(tr("Aplica la corrección Gamma sobre la imagen"));
     this->menuApplyContrastGammaCorrection = act;
     return act;
}

QAction* MainWindow::createActionContrastStretching()
 {
     QAction *act;
     act = new QAction(tr("Aplicar &Stretching"), this);
     connect(act, SIGNAL(triggered()), this, SLOT(applyContrastStretching()));
     act->setStatusTip(tr("Aplica el contraste Stretching (Expansion) sobre la imagen"));
     this->menuApplyContrastStretching = act;
     return act;
}

QAction* MainWindow::createActionContrastImprove()
 {
     QAction *act;
     act = new QAction(tr("Aplicar &Improve"), this);
     connect(act, SIGNAL(triggered()), this, SLOT(applyContrastImprove()));
     act->setStatusTip(tr("Aplica el contraste Improve sobre la imagen"));
     this->menuApplyContrastImprove = act;
     return act;
}

QAction* MainWindow::createActionEqualizer()
 {
     QAction *act;
     act = new QAction(tr("&Equalizar"), this);
     connect(act, SIGNAL(triggered()), this, SLOT(applyEqualizer()));
     act->setStatusTip(tr("Equaliza la imagen"));
     this->menuApplyEqualizer = act;
     return act;
}

QAction* MainWindow::createActionThresholdingDosPicos()
 {
     QAction *act;
     act = new QAction(tr("&Dos Picos"), this);
     connect(act, SIGNAL(triggered()), this, SLOT(getThresholdingDosPicos()));
     act->setStatusTip(tr(""));
     this->menuThresholdingDosPicosGet = act;
     return act;
}

QAction* MainWindow::createActionThresholdingOtsu()
 {
     QAction *act;
     act = new QAction(tr("&Otsu"), this);
     connect(act, SIGNAL(triggered()), this, SLOT(getThresholdingOtsu()));
     act->setStatusTip(tr(""));
     this->menuThresholdingOtsuGet = act;
     return act;
}

QAction* MainWindow::createActionThresholdingIsodata()
 {
     QAction *act;
     act = new QAction(tr("&Isodata"), this);
     connect(act, SIGNAL(triggered()), this, SLOT(getThresholdingIsodata()));
     act->setStatusTip(tr(""));
     this->menuThresholdingIsodataGet = act;
     return act;
}

QAction* MainWindow::createActionAbout()
 {
     QAction *act;
     act = new QAction(tr("&Acerca de.."), this);
     //act->setShortcuts(QKeySequence::SaveAs);
     connect(act, SIGNAL(triggered()), this, SLOT(showAbout()));
     act->setStatusTip(QObject::trUtf8("Acerca de la aplicación y sus creadores"));
     //this->menuAboutOf = act;
     return act;
}

void MainWindow::createMenus(){

    this->fileMenu = new QMenu(tr("&Archivo"));
    this->fileMenu->addAction(createActionOpenFile());
    this->fileMenu->addAction(createActionSaveFile());
    this->fileMenu->addAction(createActionCloseFile());
    this->menuSaveFile->setEnabled(false);
    this->menuCloseFile->setEnabled(false);



    this->filterMenu = new QMenu(tr("&Filtro"));
    this->filterMenu->addAction(createActionFilterMedian());
    this->filterMenu->addAction(createActionFilterSigma());
    this->filterMenu->addAction(createActionFilterCleaningPixel());
    this->filterMenu->addAction(createActionFilterCleaningLine());
    this->menuApplyFilterSigma->setEnabled(false);
    this->menuApplyFilterMedian->setEnabled(false);
    this->menuApplyFilterCleaningLine->setEnabled(false);
    this->menuApplyFilterCleaningPixel->setEnabled(false);



    this->histogramMenu = new QMenu(tr("&Histogram"));
    this->histogramMenu->addAction(createActionHistogram());
    this->histogramMenu->addAction(createActionThresholdingDosPicos());
    this->histogramMenu->addAction(createActionThresholdingIsodata());
    this->histogramMenu->addAction(createActionThresholdingOtsu());
    this->menuHistogramGet->setEnabled(false);
    this->menuThresholdingIsodataGet->setEnabled(false);
    this->menuThresholdingDosPicosGet->setEnabled(false);
    this->menuThresholdingOtsuGet->setEnabled(false);

    this->contrastMenu = new QMenu(tr("&Contraste"));
    this->contrastMenu->addAction(createActionContrastGammaCorrection());
    this->contrastMenu->addAction(createActionContrastStretching());
    this->contrastMenu->addAction(createActionContrastImprove());
    this->contrastMenu->addAction(createActionEqualizer());
    this->menuApplyContrastStretching->setEnabled(false);
    this->menuApplyContrastGammaCorrection->setEnabled(false);
    this->menuApplyContrastImprove->setEnabled(false);
    this->menuApplyEqualizer->setEnabled(false);



    this->helpMenu = new QMenu(tr("&Ayuda"));
    this->helpMenu->addAction(createActionAbout());



}



void MainWindow::openFile(){

    QString temp = QFileDialog::getOpenFileName( this,"Seleccionar Imagen a Buscar",this->path,"Imagenes pgm o Dicom (*.pgm *.ppm *dcm)");
    if(temp.isNull()){
        return;
    }
    if(!this->controler.getImageInLabel().isNull()){
        this->controler.clearAll();
    }
    this->path=temp;
    try{
        this->controler.openImage(path);

    }catch(ImageExeption& e){

        QMessageBox dialog(this);
        dialog.setText(QString(e.getMessage().c_str()));
        dialog.exec();
        return;
    }
    this->menuCloseFile->setEnabled(true);
    this->menuSaveFile->setEnabled(true);
    if(!controler.isppmImage()){
        this->menuHistogramGet->setEnabled(true);
        this->menuApplyFilterMedian->setEnabled(true);
        this->menuApplyFilterSigma->setEnabled(true);
        this->menuApplyContrastStretching->setEnabled(true);
        this->menuApplyContrastGammaCorrection->setEnabled(true);
        this->menuApplyContrastImprove->setEnabled(true);
        this->menuApplyEqualizer->setEnabled(true);
        this->menuThresholdingIsodataGet->setEnabled(true);
        this->menuThresholdingDosPicosGet->setEnabled(true);
        this->menuThresholdingOtsuGet->setEnabled(true);        
        this->menuApplyFilterCleaningLine->setEnabled(true);
        this->menuApplyFilterCleaningPixel->setEnabled(true);

    }else{
        this->menuApplyFilterMedian->setEnabled(false);
        this->menuApplyFilterSigma->setEnabled(false);
        this->menuHistogramGet->setEnabled(false);
        this->menuApplyContrastStretching->setEnabled(false);
        this->menuApplyContrastGammaCorrection->setEnabled(false);
        this->menuApplyContrastImprove->setEnabled(false);
        this->menuApplyEqualizer->setEnabled(false);
        this->menuThresholdingIsodataGet->setEnabled(false);
        this->menuThresholdingDosPicosGet->setEnabled(false);
        this->menuThresholdingOtsuGet->setEnabled(false);        
        this->menuApplyFilterCleaningLine->setEnabled(false);
        this->menuApplyFilterCleaningPixel->setEnabled(false);
    }



    ui->labelImageIn->setPixmap(QPixmap::fromImage(controler.getImageInLabel()));
    ui->labelImageIn->setScaledContents(true);
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageInLabel()));
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
        this->controler.saveImage(temp);
        this->menuSaveFile->setStatusTip(tr("El archivo se ha guardado correctamente"));

        return;

    }
    QString temp = QFileDialog::getSaveFileName(this,"Seleccionar lugar y nombre del archivo", this->path, "Imagenes pgm (*.pgm *.ppm)");
    if(temp.isNull()){
        return;
    }
    this->controler.saveImage(temp);
    this->menuSaveFile->setStatusTip(tr("El archivo se ha guardado correctamente"));
}

void MainWindow::closeFile(){

    this->controler.clearAll();

    ui->labelImageIn->setPixmap(QPixmap::fromImage(QImage()));
    ui->labelImageOut->setPixmap(QPixmap::fromImage(QImage()));
    ui->labelHistogram->setPixmap(QPixmap::fromImage(QImage()));

    this->menuCloseFile->setEnabled(false);
    this->menuSaveFile->setEnabled(false);
    this->menuApplyFilterMedian->setEnabled(false);
    this->menuApplyFilterSigma->setEnabled(false);
    this->menuApplyFilterCleaningLine->setEnabled(false);
    this->menuApplyFilterCleaningPixel->setEnabled(false);
    this->menuHistogramGet->setEnabled(false);
    this->menuApplyContrastStretching->setEnabled(false);
    this->menuApplyContrastGammaCorrection->setEnabled(false);
    this->menuApplyContrastImprove->setEnabled(false);
    this->menuApplyEqualizer->setEnabled(false);
    this->menuThresholdingIsodataGet->setEnabled(false);
    this->menuThresholdingDosPicosGet->setEnabled(false);
    this->menuThresholdingOtsuGet->setEnabled(false);


}

void MainWindow::applyFilterMedian(){
    bool ok;
    int value = QInputDialog::getInt(this, tr("Valor de calculo"),
                                     tr("Ingrese n:"), 3,0,100,1,&ok);
    this->controler.applyFilterMedian(value);
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOutLabel()));
    ui->labelImageOut->setStatusTip("Filtro Mediana Aplicado");
    ui->labelImageOut->setScaledContents(true);
    ui->labelImageOut->update();
}

void MainWindow::applyFilterSigma(){
    bool ok;
    int value = QInputDialog::getInt(this, tr("Valor de calculo"),
                                     tr("Ingrese sigma:"), 10,0,100,1,&ok);
    this->controler.applyFilterSigma(value);
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOutLabel()));
    ui->labelImageOut->setStatusTip("Filtro Sigma Aplicado");
    ui->labelImageOut->setScaledContents(true);
    ui->labelImageOut->update();

}

void MainWindow::applyFilterCleaningPixel(){
    bool ok;
    double value = QInputDialog::getDouble(this, tr("Valor de calculo"),
                                     tr("Ingrese el valor para delta:"), 10.0,0,100,2,&ok);
    this->controler.applyFilterCleaningPixel(value);
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOutLabel()));
    ui->labelImageOut->setStatusTip("Filtro Cleaning Pixel Aplicado");
    ui->labelImageOut->setScaledContents(true);
    ui->labelImageOut->update();
}

void MainWindow::applyFilterCleaningLine(){
    bool ok;
    double value = QInputDialog::getDouble(this, tr("Valor de calculo"),
                                     tr("Ingrese el valor para delta:"), 10.0,0,100,2,&ok);
    this->controler.applyFilterCleaningLine(value);
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOutLabel()));
    ui->labelImageOut->setStatusTip("Filtro Cleaning Pixel Aplicado");
    ui->labelImageOut->setScaledContents(true);
    ui->labelImageOut->update();
}

void MainWindow::applyContrastGammaCorrection(){
    bool ok;
    double value = QInputDialog::getDouble(this, tr("Valor de calculo"),
                                     tr("Ingrese el valor para calcular gamma:"), 2.2,0,100,2,&ok);
    this->controler.applyContrastCorrectionGamma(value);
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOutLabel()));
    ui->labelImageOut->setStatusTip(QObject::trUtf8("Corrección Gamma Aplicado"));
    ui->labelImageOut->setScaledContents(true);
    ui->labelImageOut->update();
}

void MainWindow::applyContrastStretching(){
    this->controler.applyContrastStretching();
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOutLabel()));
    ui->labelImageOut->setStatusTip(QObject::trUtf8("Contraste Stretching Aplicado"));
    ui->labelImageOut->setScaledContents(true);
    ui->labelImageOut->update();
}

void MainWindow::applyContrastImprove(){
    bool ok;
    int value = QInputDialog::getInt(this, tr("Valor de calculo"),
                                     tr("Ingrese para escoger uno de los metodos:"), 0,0,1,1,&ok);
    this->controler.applyContrastImprove(value);
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOutLabel()));
    ui->labelImageOut->setStatusTip(QObject::trUtf8("Contraste Improve Aplicado"));
    ui->labelImageOut->setScaledContents(true);
    ui->labelImageOut->update();
}

void MainWindow::applyEqualizer(){
    this->controler.applyEqualizer();
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOutLabel()));
    ui->labelImageOut->setStatusTip(QObject::trUtf8("Equalizador Aplicado"));
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

void MainWindow::getThresholdingDosPicos(){
    this->controler.getThresholdingDosPicos();
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOutLabel()));
    ui->labelImageOut->setStatusTip(QObject::trUtf8("Calculo de Dos Picos"));
    ui->labelImageOut->setScaledContents(true);
    ui->labelImageOut->update();
}

void MainWindow::getThresholdingIsodata(){
    this->controler.getThresholdingIsodata();
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOutLabel()));
    ui->labelImageOut->setStatusTip(QObject::trUtf8("Calculo de Isodata"));
    ui->labelImageOut->setScaledContents(true);
    ui->labelImageOut->update();
}

void MainWindow::getThresholdingOtsu(){
    this->controler.getThresholdingOtsu();
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOutLabel()));
    ui->labelImageOut->setStatusTip(QObject::trUtf8("Calculo de Otsu"));
    ui->labelImageOut->setScaledContents(true);
    ui->labelImageOut->update();
}

void MainWindow::showAbout(){
    QMessageBox dialog(this);
    dialog.setText(QObject::trUtf8("Aplicación para el manejo e implementacion de algoritmos para el procesamiento de imagenes.\n Integrantes:\n\tEdgar Andres Moncada\n\tYerminson Gonzalez"));
    dialog.exec();
}
