#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QPainter>
#include <QMessageBox>
#include <QInputDialog>
#include "controler.h"



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

    QString path;
    QAction *menuOpenFile;
    QAction *menuSaveFile;
    QAction *menuCloseFile;
    QAction *menuApplyFilterSigma;
    QAction *menuApplyFilterMedian;
    QAction *menuApplyContrastGammaCorrection;
    QAction *menuApplyContrastExpansion;
    QAction *menuApplyContrastImprove;
    QAction *menuApplyEqualizer;
    QAction *menuThresholdingDosPicosGet;
    QAction *menuThresholdingIsodataGet;
    QAction *menuThresholdingOtsuGet;
    QAction *menuHistogramGet;


    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QMenu *filterMenu;
    QMenu *histogramMenu;
    QMenu *contrastMenu;
    QMenu *helpMenu;

    void createMenus();
    QAction* createActionOpenFile();
    QAction* createActionSaveFile();
    QAction* createActionCloseFile();
    QAction* createActionFilterSigma();
    QAction* createActionFilterMedian();
    QAction* createActionContrastGammaCorrection();
    QAction* createActionContrastExpansion();
    QAction* createActionContrastImprove();
    QAction* createActionEqualizer();
    QAction* createActionHistogram();
    QAction* createActionThresholdingDosPicos();
    QAction* createActionThresholdingIsodata();
    QAction* createActionThresholdingOtsu();
    QAction* createActionAbout();




private slots:

    void openFile();
    void saveFile();
    void closeFile();
    void applyFilterSigma();
    void applyFilterMedian();
    void applyContrastGammaCorrection();
    void applyContrastExpansion();
    void applyContrastImprove();
    void applyEqualizer();
    void getHistogram();
    void getThresholdingDosPicos();
    void getThresholdingIsodata();
    void getThresholdingOtsu();
    void showAbout();

};

#endif // MAINWINDOW_H
