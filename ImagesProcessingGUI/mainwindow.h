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


    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;

    void createMenus();
    QAction* createActionOpenFile();
    QAction* createActionSaveFile();



private slots:

    void openFile();
    void saveFile();

};

#endif // MAINWINDOW_H
