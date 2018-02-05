#ifndef GLWIDGET_H
#define GLWIDGET_H

#include<QOpenGLWidget>
#include<QOpenGLFunctions_4_5_Core>
#include "Object/object3d.h"
#include <QList>


class GlWidget:public QOpenGLWidget,protected QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    GlWidget(QWidget *parent=0);
    QString GlGetVersion();
    QList<Object3d *> *Objects();
    void Append(Object3d *);
    void Remove(Object3d *);
    ~GlWidget();

    static int ObjectsCount;
protected:
    void initializeGL() override;
    void paintGL() override;
private:
    QList<Object3d *> *mObjects;
};

#endif // GLWIDGET_H
