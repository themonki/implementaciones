#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QPainter>
#include <QMessageBox>
#include <QInputDialog>
#include "controler.h"
#include "imageviewer.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    Controler controler;
    ImageViewer *in, *out, *h;
    //QLabel *labelImageIn,*labelImageOut, *labelHistogram;
    //ShowImage* showIn, *showOut, *ShowHistogram;

    QString path;
    QAction *menuOpenFile;
    QAction *menuSaveFile;
    QAction *menuCloseFile;
    QAction *menuConvertToGrayScale;
    QAction *menuApplyFilterSigma;
    QAction *menuApplyFilterMedian;
    QAction *menuApplyFilterCleaningPixel;
    QAction *menuApplyFilterCleaningLine;
    QAction *menuApplyContrastGammaCorrection;
    QAction *menuApplyContrastStretching;
    QAction *menuApplyContrastImprove;
    QAction *menuApplyEqualizer;
    QAction *menuThresholdingDosPicosGet;
    QAction *menuThresholdingIsodataGet;
    QAction *menuThresholdingOtsuGet;
    QAction *menuHistogramGet;
    QAction *menuAddImages;
    QAction *menuAddValue;
    QAction *menuDivValue;
    QAction *menuMulValue;
    QAction *menuSubValue;
    QAction *menuInvertImage;
    QAction *menuApplyEdgeDetectorCanny;
    QAction *menuApplyEdgeDetectorSobel;


    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QMenu *toolsMenu;
    QMenu *filterMenu;
    QMenu *histogramMenu;
    QMenu *contrastMenu;
    QMenu *edgeMenu;
    QMenu *helpMenu;

    void createMenus();
    void createEvents();
    void initActions();
    QAction* createActionOpenFile();
    QAction* createActionSaveFile();
    QAction* createActionCloseFile();
    QAction* createActionConvertToGraySacale();
    QAction* createActionFilterSigma();
    QAction* createActionFilterMedian();    
    QAction* createActionFilterCleaningPixel();
    QAction* createActionFilterCleaningLine();
    QAction* createActionContrastGammaCorrection();
    QAction* createActionContrastStretching();
    QAction* createActionContrastImprove();
    QAction* createActionEqualizer();
    QAction* createActionHistogram();
    QAction* createActionThresholdingDosPicos();
    QAction* createActionThresholdingIsodata();
    QAction* createActionThresholdingOtsu();
    QAction* createActionAbout();
    QAction* createActionAddImages();
    QAction* createActionAddValue();
    QAction* createActionDivValue();
    QAction* createActionMulValue();
    QAction* createActionSubValue();
    QAction* createActionInvertImage();
    QAction* createActionApplyEdgeDectectorCanny();
    QAction* createActionApplyEdgeDectectorSobel();

private slots:
    //menu events
    void openFile();
    void saveFile();
    void closeFile();
    void convertToGrayScale();
    void applyFilterSigma();
    void applyFilterMedian();
    void applyFilterCleaningPixel();
    void applyFilterCleaningLine();
    void applyContrastGammaCorrection();
    void applyContrastStretching();
    void applyContrastImprove();
    void applyEqualizer();
    void getHistogram();
    void getThresholdingDosPicos();
    void getThresholdingIsodata();
    void getThresholdingOtsu();
    void showAbout();
    void addImage();
    void addValue();
    void divValue();
    void mulValue();
    void subValue();
    void invertImage();
    void applyEdgeDetectorCanny();
    void applyEdgeDetectorSobel();

    //buttons events
    void showImageFullIn();
    void showImageFullOut();
    void showImageFullHistogramIn();
    void showImageFullHistogramOut();
    void restoreImage();

    void on_sliderWindow_sliderMoved(int position);
    void on_sliderLevel_sliderMoved(int position);
};

#endif // MAINWINDOW_H
