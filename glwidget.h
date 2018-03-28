#ifndef GLWIDGET_H
#define GLWIDGET_H

#include<QOpenGLWidget>
#include<QOpenGLFunctions_4_5_Core>
#include "Object/object3d.h"
#include "camera.h"
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
    Camera *cam() const;

protected:
    void initializeGL() override;
    void paintGL() override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    QList<Object3d *> *mObjects;
    Camera *mCam = nullptr;
};

#endif // GLWIDGET_H
