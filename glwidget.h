#ifndef GLWIDGET_H
#define GLWIDGET_H

#include<QOpenGLWidget>
#include<QOpenGLFunctions>

class GlWidget:public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GlWidget(QWidget *parent=0);
    QString GlGetVersion();
    ~GlWidget();
protected:
    void initializeGL() override;
    void paintGL() override;
};

#endif // GLWIDGET_H
