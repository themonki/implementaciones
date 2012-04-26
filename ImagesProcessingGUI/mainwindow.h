#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QPainter>
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
    QAction *menuApplyFilterSigma;
    QAction *menuApplyFilterMedian;
    QAction *menuHistogramGet;


    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QMenu *filterMenu;
    QMenu *HistogramMenu;
    QMenu *helpMenu;

    void createMenus();
    QAction* createActionOpenFile();
    QAction* createActionSaveFile();
    QAction* createActionFilterSigma();
    QAction* createActionFilterMedian();
    QAction* createActionHistogram();



private slots:

    void openFile();
    void saveFile();
    void applyFilterSigma();
    void applyFilterMedian();
    void getHistogram();

};

#endif // MAINWINDOW_H
