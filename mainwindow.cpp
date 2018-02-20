#include "mainwindow.h"
#include <glwidget.h>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include "Object/triangle.h"
#include "Object/plane.h"
#include "Object/ripplemesh.h"
#include "addobjectcommand.h"

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

    mUndoStack=new QUndoStack(this);
    initMenu();    
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
    addObject();
}

void MainWindow::initMenu()
{
    mFileMenu=menuBar()->addMenu("File");
    mEditMenu=menuBar()->addMenu("Edit");
    mUndoAction=mUndoStack->createUndoAction(this,"Undo");
    mRedoAction=mUndoStack->createRedoAction(this,"Redo");
    mEditMenu->addAction(mUndoAction);
    mEditMenu->addAction(mRedoAction);
}

void MainWindow::addObject()
{
    QString pathVertex("../Resources/Shaders/shader.vert");
    QString pathFragment("../Resources/Shaders/shader.frag");
    QString pathVertex1("../Resources/Shaders/ripple.vert");
    QString pathFragment2("../Resources/Shaders/ripple.frag");
//    Triangle *tri=new Triangle(pathVertex,pathFragment);
//    tri->Bind();
//    mUndoStack->push(new AddObjectCommand(mGlWidget,tri));

//    plane *plan=new plane(pathVertex,pathFragment);
//    plan->Bind();
//    mUndoStack->push(new AddObjectCommand(mGlWidget,plan));

    RippleMesh *ripple=new RippleMesh(pathVertex1,pathFragment2,width(),height());
    ripple->Bind();
    mUndoStack->push(new AddObjectCommand(mGlWidget,ripple));
}
