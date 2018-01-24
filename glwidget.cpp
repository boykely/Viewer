#include "glwidget.h"
#include "Object/triangle.h"
#include <QDebug>

GlWidget::GlWidget(QWidget *parent):QOpenGLWidget(parent)
{    
    QSurfaceFormat format;
    format.setVersion(4,5);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
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
    QString pathVertex("../sans_titre/Resources/Shaders/shader.vert");
    QString pathFragment("../sans_titre/Resources/Shaders/shader.frag");
    mTri=new Triangle(pathVertex,pathFragment);
    mTri->Bind();
}
void GlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
    mTri->Draw();
}
QString GlWidget::GlGetVersion()
{
    const char* version=(const char*)glGetString(GL_VERSION);
    return QString(version);
}

