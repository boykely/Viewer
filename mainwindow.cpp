#include "mainwindow.h"
#include <glwidget.h>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mGlWidget=new GlWidget();
    mLayout=new QHBoxLayout();
    mLayout->addWidget(mGlWidget);
    mLayout->addWidget(new QPushButton("kj"));
    QWidget *central=new QWidget();
    central->setLayout(mLayout);
    setCentralWidget(central);    
}

MainWindow::~MainWindow()
{
}
void MainWindow::showMaximized()
{
    QMainWindow::showMaximized();
    setWindowTitle("Learn OpenGL - "+mGlWidget->GlGetVersion());
}
void MainWindow::show()
{
    QRect geometryWindow=QApplication::desktop()->geometry();
    setFixedSize(geometryWindow.width(),(geometryWindow.height()/2));
    QMainWindow::show();
    setWindowTitle("Learn OpenGL - "+mGlWidget->GlGetVersion());
}
