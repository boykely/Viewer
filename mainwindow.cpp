#include "mainwindow.h"
#include <glwidget.h>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include "Object/triangle.h"
#include "Object/plane.h"

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
    addTriangle();
    addPlane();
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

void MainWindow::addTriangle()
{
    QString pathVertex("../sans_titre/Resources/Shaders/shader.vert");
    QString pathFragment("../sans_titre/Resources/Shaders/shader.frag");
    Triangle *tri=new Triangle(pathVertex,pathFragment);
    tri->Bind();
    mGlWidget->Append(tri);
}

void MainWindow::addPlane()
{
    QString pathVertex("../sans_titre/Resources/Shaders/shader.vert");
    QString pathFragment("../sans_titre/Resources/Shaders/shader.frag");
    plane *plan=new plane(pathVertex,pathFragment);
    plan->Bind();
    mGlWidget->Append(plan);
}
