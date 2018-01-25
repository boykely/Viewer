#ifndef GLWIDGET_H
#define GLWIDGET_H

#include<QOpenGLWidget>
#include<QOpenGLFunctions_4_5_Core>

class Triangle;
class plane;

class GlWidget:public QOpenGLWidget,protected QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    GlWidget(QWidget *parent=0);
    QString GlGetVersion();
    ~GlWidget();
protected:
    void initializeGL() override;
    void paintGL() override;
private:
    Triangle *mTri;
    plane *mPlane;
};

#endif // GLWIDGET_H
