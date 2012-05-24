#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->path = QDir::homePath();
    this->createMenus();
    this->createEvents();
    ui->menubar->addMenu(this->fileMenu);
    ui->menubar->addMenu(this->toolsMenu);
    ui->menubar->addMenu(this->filterMenu);
    ui->menubar->addMenu(this->histogramMenu);
    ui->menubar->addMenu(this->contrastMenu);
    ui->menubar->addMenu(this->helpMenu);
    //in = new ImageViewer(this);
    //out= new ImageViewer(this);
    //h= new ImageViewer(this);
    //this->labelImageIn = ui->labelImageIn= in->getImageLabel();
    //this->labelImageOut = ui->labelImageOut= out->getImageLabel();
    //this->labelHistogram = ui->labelHistogram= h->getImageLabel();
    //this->labelImageIn = new QLabel();
    //this->labelImageOut = new QLabel();
    //this->labelHistogram = new QLabel();
    //ui->scrollAreaIn->setWidget(in->centralWidget());
    //ui->scrollAreaOut->setWidget(out->centralWidget());
    //ui->scrollAreaHistogram->setWidget(h->centralWidget());

    setWindowTitle(tr("Image Processing"));
    //setWindowFlags(Qt::WindowFlags() | Qt::WindowStaysOnTopHint);
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
    y=20;

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

QAction* MainWindow::createActionConvertToGraySacale()
 {
     QAction *act;
     act = new QAction(tr("Convertir a Grises"), this);
     connect(act, SIGNAL(triggered()), this, SLOT(convertToGrayScale()));
     this->menuConvertToGrayScale = act;
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

QAction* MainWindow::createActionAddImages()
{
    QAction *act;
    act = new QAction(tr("Sumar dos Imagenes"), this);
    connect(act, SIGNAL(triggered()), this, SLOT(addImage()));
    act->setStatusTip(QObject::trUtf8("Sumar dos imagenes"));
    this->menuAddImages = act;
    return act;
}

QAction* MainWindow::createActionAddValue()
{
    QAction *act;
    act = new QAction(tr("Adicionar valor a la imagen"), this);
    connect(act, SIGNAL(triggered()), this, SLOT(addValue()));
    act->setStatusTip(QObject::trUtf8("Aumentada el nivel de la imagen"));
    this->menuAddValue = act;
    return act;
}

QAction* MainWindow::createActionDivValue()
{
    QAction *act;
    act = new QAction(tr("Dividir valor a la imagen"), this);
    connect(act, SIGNAL(triggered()), this, SLOT(divValue()));
    act->setStatusTip(QObject::trUtf8("Divide el nivel de la imagen"));
    this->menuDivValue = act;
    return act;
}

QAction* MainWindow::createActionMulValue()
{
    QAction *act;
    act = new QAction(tr("Multiplicar valor a la imagen"), this);
    connect(act, SIGNAL(triggered()), this, SLOT(mulValue()));
    act->setStatusTip(QObject::trUtf8("Multiplica el nivel de la imagen"));
    this->menuMulValue = act;
    return act;
}

QAction* MainWindow::createActionSubValue()
{
    QAction *act;
    act = new QAction(tr("Resta valor a la imagen"), this);
    connect(act, SIGNAL(triggered()), this, SLOT(subValue()));
    act->setStatusTip(QObject::trUtf8("Disminuye el nivel de la imagen"));
    this->menuSubValue = act;
    return act;
}

void MainWindow::createMenus(){

    this->fileMenu = new QMenu(tr("&Archivo"));
    this->fileMenu->addAction(createActionOpenFile());
    this->fileMenu->addAction(createActionSaveFile());
    this->fileMenu->addAction(createActionCloseFile());
    this->menuSaveFile->setEnabled(false);
    this->menuCloseFile->setEnabled(false);

    this->toolsMenu = new QMenu(tr("Herramientas"));
    this->toolsMenu->addAction(createActionConvertToGraySacale());
    this->toolsMenu->addAction(createActionAddImages());
    this->toolsMenu->addAction(createActionAddValue());
    this->toolsMenu->addAction(createActionSubValue());
    this->toolsMenu->addAction(createActionMulValue());
    this->toolsMenu->addAction(createActionDivValue());
    this->menuConvertToGrayScale->setEnabled(false);
    this->menuAddImages->setEnabled(false);
    this->menuAddValue->setEnabled(false);
    this->menuSubValue->setEnabled(false);
    this->menuDivValue->setEnabled(false);
    this->menuMulValue->setEnabled(false);

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


    ui->buttonShowIn->setEnabled(false);
    ui->buttonShowOut->setEnabled(false);
    ui->buttonRestore->setEnabled(false);
    ui->buttonHistogramIn->setEnabled(false);
    ui->buttonHistogramOut->setEnabled(false);

}

void MainWindow::createEvents(){

    QObject::connect(ui->buttonShowIn,SIGNAL(clicked()), this, SLOT(showImageFullIn()));
    QObject::connect(ui->buttonShowOut,SIGNAL(clicked()), this, SLOT(showImageFullOut()));
    QObject::connect(ui->buttonHistogramIn,SIGNAL(clicked()), this, SLOT(showImageFullHistogramIn()));
    QObject::connect(ui->buttonHistogramOut,SIGNAL(clicked()), this, SLOT(showImageFullHistogramOut()));
    QObject::connect(ui->buttonRestore,SIGNAL(clicked()), this, SLOT(restoreImage()));



}

void MainWindow::initActions(){
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

        this->menuConvertToGrayScale->setEnabled(false);

        this->menuAddImages->setEnabled(true);
        this->menuAddValue->setEnabled(true);
        this->menuSubValue->setEnabled(true);
        this->menuDivValue->setEnabled(true);
        this->menuMulValue->setEnabled(true);

        ui->buttonShowIn->setEnabled(true);
        ui->buttonShowOut->setEnabled(true);
        ui->buttonRestore->setEnabled(true);
        ui->buttonHistogramIn->setEnabled(true);
        ui->buttonHistogramOut->setEnabled(false);

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

        this->menuConvertToGrayScale->setEnabled(true);

        this->menuAddImages->setEnabled(false);
        this->menuAddValue->setEnabled(false);
        this->menuSubValue->setEnabled(false);
        this->menuDivValue->setEnabled(false);
        this->menuMulValue->setEnabled(false);

        ui->buttonShowIn->setEnabled(true);
        ui->buttonShowOut->setEnabled(false);
        ui->buttonRestore->setEnabled(false);
        ui->buttonHistogramIn->setEnabled(false);
        ui->buttonHistogramOut->setEnabled(false);

    }
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

    initActions();
    QPixmap tempPixmap;
    tempPixmap = QPixmap::fromImage(controler.getImageInLabel());
    //in->getImageLabel()->setPixmap(temp);
    //in->getImageLabel()->adjustSize();
    //this->labelImageIn->setPixmap(temp);
    ui->labelImageIn->setPixmap(tempPixmap);
    ui->labelImageIn->setScaledContents(true);

    //new ImageViewer(controler.getImageInLabel(),this);


    //tempPixmap = QPixmap::fromImage(controler.getImageInLabel());
    //this->labelImageOut->setPixmap(temp);
    //out->getImageLabel()->adjustSize();
    ui->labelImageOut->setPixmap(tempPixmap);
    ui->labelImageOut->setScaledContents(true);

    //this->labelHistogram->setPixmap(QPixmap::fromImage(QImage()));
    ui->labelHistogram->setScaledContents(true);

    ui->labelImageIn->update();
    ui->labelImageOut->update();
    //ui->labelHistogram->update();


    //this->showIn = new ShowImage(viewer.getWidget(), 0);

    //this->showIn = new ShowImage(controler.getImageInLabel(),"Imagen Original", this);
    //this->showIn->open();
   /* this->showOut = new ShowImage(controler.getImageOutLabel(),"Imagen Modificada",this);
    this->showOut->open();
    this->showOut->setImage(controler.getImageIn());/**/

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
    this->menuConvertToGrayScale->setEnabled(false);
    this->menuAddImages->setEnabled(false);
    this->menuAddValue->setEnabled(false);
    this->menuSubValue->setEnabled(false);
    this->menuDivValue->setEnabled(false);
    this->menuMulValue->setEnabled(false);


}

void MainWindow::convertToGrayScale(){
    if(controler.isppmImage()){
        QImage temp = this->controler.applyConvertToGrayScale(controler.getImageOut(), controler.getImageOutLabel());
        ui->labelImageOut->setPixmap(QPixmap::fromImage(temp));
        ui->labelImageOut->setStatusTip("Imagen convertida a PGM");
        ui->labelImageOut->setScaledContents(true);
        ui->labelImageOut->update();

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
        this->menuAddImages->setEnabled(true);
        this->menuAddValue->setEnabled(true);
        this->menuSubValue->setEnabled(true);
        this->menuDivValue->setEnabled(true);
        this->menuMulValue->setEnabled(true);


    }
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
                                     tr("Ingrese el valor para calcular é gamma:"), 2.2,0,100,2,&ok);
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
    ui->buttonHistogramOut->setEnabled(true);
    //this->labelHistogram->setScaledContents(true);
    //this->labelHistogram->update();
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

void MainWindow::addImage(){

    QString temp = QFileDialog::getOpenFileName( this,"Seleccionar Imagen a Adicionar",this->path,"Imagenes pgm o Dicom (*.pgm *.ppm *dcm)");
    if(temp.isNull()){
        return;
    }

    Image imageAdd(temp.toStdString());

    if(imageAdd.getWidth()!=controler.getImageOut()->getWidth() || imageAdd.getHeight()!=controler.getImageOut()->getHeight()){
        QMessageBox::information(this, tr("Error"), tr("No se puede sumar esat imagen"));
        return;
    }


    bool ok;
    double value = QInputDialog::getDouble(this, tr("Valor de calculo"),
                                     tr("Ingrese porcentaje de solapamiento:"), 0,0,1,2,&ok);
    this->controler.applyOperationAddImage(imageAdd, value);

    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOutLabel()));
    ui->labelImageOut->setStatusTip(QObject::trUtf8("Suma de Imagen aplicado"));
    ui->labelImageOut->setScaledContents(true);
    ui->labelImageOut->update();
}

void MainWindow::addValue(){
    bool ok;
    double value = QInputDialog::getDouble(this, tr("Valor de calculo"),
                                     tr("Ingrese el valor para Adicionar:"), 0,0,255,2,&ok);
    this->controler.applyOperationAddValue(value);
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOutLabel()));
    ui->labelImageOut->setStatusTip(QObject::trUtf8("Suma de nivel aplicado"));
    ui->labelImageOut->setScaledContents(true);
    ui->labelImageOut->update();
}

void MainWindow::divValue(){
    bool ok;
    double value = QInputDialog::getDouble(this, tr("Valor de calculo"),
                                     tr("Ingrese el valor para dividir:"), 1,0,100,2,&ok);
    this->controler.applyOperationDivValue(value);
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOutLabel()));
    ui->labelImageOut->setStatusTip(QObject::trUtf8("Division de nivel aplicado"));
    ui->labelImageOut->setScaledContents(true);
    ui->labelImageOut->update();
}

void MainWindow::mulValue(){
    bool ok;
    double value = QInputDialog::getDouble(this, tr("Valor de calculo"),
                                     tr("Ingrese el valor para Multiplicar:"), 1,0,100,2,&ok);
    this->controler.applyOperationMulValue(value);
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOutLabel()));
    ui->labelImageOut->setStatusTip(QObject::trUtf8("Multiplicación de nivel aplicado"));
    ui->labelImageOut->setScaledContents(true);
    ui->labelImageOut->update();
}

void MainWindow::subValue(){
    bool ok;
    double value = QInputDialog::getDouble(this, tr("Valor de calculo"),
                                     tr("Ingrese el valor para restar"), 0,0,100,2,&ok);
    this->controler.applyOperationSubValue(value);
    ui->labelImageOut->setPixmap(QPixmap::fromImage(controler.getImageOutLabel()));
    ui->labelImageOut->setStatusTip(QObject::trUtf8("Resta de nivel aplicado"));
    ui->labelImageOut->setScaledContents(true);
    ui->labelImageOut->update();
}


// buttons events

void MainWindow::showImageFullIn(){
    new ImageViewer(*controler.getImageIn(), controler.getImageInLabel(),"Imagen de Entrada", this);

}
void MainWindow::showImageFullOut(){
    new ImageViewer(*controler.getImageOut(), controler.getImageOutLabel(),"Imagen Modificada", this);

}
void MainWindow::showImageFullHistogramIn(){
    new ImageViewer(controler.gethistogramInLabel(),"Histograma Original", this);

}
void MainWindow::showImageFullHistogramOut(){
    new ImageViewer(controler.getHistogram(),"Histograma Imagen Modificada", this);

}

void MainWindow::restoreImage(){
    initActions();
    controler.openImage(path);
    ui->labelHistogram->setPixmap(QPixmap::fromImage(QImage()));
    QPixmap tempPixmap = QPixmap::fromImage(controler.getImageInLabel());
    ui->labelImageIn->setPixmap(tempPixmap);
    ui->labelImageOut->setPixmap(tempPixmap);
}
