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

 #ifndef IMAGEVIEWER_H
 #define IMAGEVIEWER_H

 #include <QMainWindow>
 #include <QPrinter>
 #include "operationgeometric.h"

 class QAction;
 class QLabel;
 class QMenu;
 class QScrollArea;
 class QScrollBar;

 class ImageViewer : public QMainWindow
 {
     Q_OBJECT

 public:
     ImageViewer(QWidget *parent = 0);
     ImageViewer(Image, QImage,QString,QWidget *parent = 0);
     ImageViewer(QImage,QString,QWidget *parent = 0);

     QLabel* getImageLabel();
     QWidget* getWidget();
     void initComponents(QImage image, QString title);

private:
     void createActions();
     void createMenus();
     void scaleImage(double factor);

     QLabel *imageLabel;
     QScrollArea *scrollArea;
     double scaleFactor;
     Image *img;

     QAction *exitAct;
     QAction *zoomInAct;
     QAction *zoomOutAct;

     QMenu *fileMenu;
     QMenu *viewMenu;

 public slots:
     void scaleUp();
     void scaleDown();


 protected:
     void changeEvent(QEvent *e);
     void resizeEvent(QResizeEvent *e); //Added
     void wheelEvent(QWheelEvent *e);
 };

 #endif
