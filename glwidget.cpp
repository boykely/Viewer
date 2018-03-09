#include "glwidget.h"
#include "Object/plane.h"
#include "Object/triangle.h"
#include <QDebug>

int GlWidget::ObjectsCount=0;

GlWidget::GlWidget(QWidget *parent):QOpenGLWidget(parent)
{    
    QSurfaceFormat format;
    format.setVersion(4,5);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
    mObjects=new QList<Object3d *>();
    mCam = new Camera(width(),height(),glm::vec3(0,10,-25));
}
GlWidget::~GlWidget()
{

}
void GlWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glViewport(0,0,width(),height());
    glClearColor(0.0f, 0.0f,0.0f,1);
    glEnable(GL_DEPTH_TEST);
}
void GlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(int i=0;i<mObjects->count();i++)
    {
        mObjects->at(i)->Draw(mCam);
    }

}
QString GlWidget::GlGetVersion()
{
    const char* version=(const char*)glGetString(GL_VERSION);
    return QString(version);
}

QList<Object3d *> *GlWidget::Objects()
{
    return mObjects;
}

void GlWidget::Append(Object3d *_obj)
{
    _obj->Id=mObjects->count();
    mObjects->append(_obj);
    ObjectsCount=mObjects->count();
}

void GlWidget::Remove(Object3d *_obj)
{
    for(int i=0;i<mObjects->count();i++)
    {
        if(_obj->Id==mObjects->at(i)->Id)
            mObjects->removeAt(i);
    }
}

void GlWidget::wheelEvent(QWheelEvent *event)
{
    if(mCam!=nullptr)
        mCam->wheelEvent(event);
    update();
}

