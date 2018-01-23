#include "glwidget.h"
#include "Object/triangle.h"
#include <QDebug>

GlWidget::GlWidget(QWidget *parent):QOpenGLWidget(parent)
{    
}
GlWidget::~GlWidget()
{

}
void GlWidget::initializeGL()
{
    initializeOpenGLFunctions();
    //qDebug()<<width()<<" - "<<height()<<endl;
    glViewport(0,0,width(),height());
    glClearColor(0.2f, 0.3f,0.3f,1);
    Triangle tri;
    tri.Bind();
    tri.Draw();
}
void GlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
}
QString GlWidget::GlGetVersion()
{
    const char* version=(const char*)glGetString(GL_VERSION);
    return QString(version);
}

