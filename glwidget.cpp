#include "glwidget.h"
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
    glClearColor(1, 0, 0,1);
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

