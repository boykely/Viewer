#include "mainwindow.h"
#include <glwidget.h>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include <QFileDialog>
#include "Object/triangle.h"
#include "Object/plane.h"
#include "Object/cube.h"
#include "addobjectcommand.h"
#include "Common/commons.h"

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
//    setFixedSize(geometryWindow.width(),(geometryWindow.height()/2));
//    QMainWindow::show();
    QMainWindow::showMaximized();
    setWindowTitle("Learn OpenGL - "+mGlWidget->GlGetVersion());
    addObject();
}

void MainWindow::initMenu()
{
    mFileMenu=menuBar()->addMenu("File");
    mEditMenu=menuBar()->addMenu("Edit");
    mUndoAction=mUndoStack->createUndoAction(this,"Undo");
    mRedoAction=mUndoStack->createRedoAction(this,"Redo");
    //Edit menu
    mEditMenu->addAction(mUndoAction);
    mEditMenu->addAction(mRedoAction);
    //File menu
    QAction *importAction=mFileMenu->addAction("Import 3D file");
    QAction *exportAction=mFileMenu->addAction("Export");
    QAction *quitAction=mFileMenu->addAction("Quit");

    connect(importAction,SIGNAL(triggered(bool)),this,SLOT(import3dFileDialog(bool)));
}

void MainWindow::addObject()
{
    QString pathVertex2("../Resources/Shaders/ripple.vert");
    QString pathFragment2("../Resources/Shaders/ripple.frag");

    Cube *cb=new Cube(pathVertex2,pathFragment2,width(),height());
    cb->Bind();
    glm::mat4 cbModel;
    cbModel=glm::rotate(cbModel,glm::radians(40.0f),glm::vec3(0,1,0));
    cbModel=glm::translate(cbModel,glm::vec3(0,0,0));
    cbModel=glm::scale(cbModel,glm::vec3(5,5,5));
    cb->Model=cbModel;
    mUndoStack->push(new AddObjectCommand(mGlWidget,cb));

    Cube *cb2=new Cube(pathVertex2,pathFragment2,width(),height());
    cb2->Bind();
    glm::mat4 cbModel2;
    cbModel2=glm::rotate(cbModel2,glm::radians(40.0f),glm::vec3(0,1,0));
    cbModel2=glm::translate(cbModel2,glm::vec3(0,5,-10));
    cbModel2=glm::scale(cbModel2,glm::vec3(5,5,5));
    cb2->Model=cbModel2;
    mUndoStack->push(new AddObjectCommand(mGlWidget,cb2));
}

void MainWindow::import3dFileDialog(bool checked)
{
    QString fileName=QFileDialog::getOpenFileName(this,"Import 3d file",Commons::DesktopDir(),
                                                  "Obj file (*.obj);;Stl file (*.stl);;Fpbx file (*.fpbx)");
}
