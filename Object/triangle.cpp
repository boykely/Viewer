#include "triangle.h"
#include <QDebug>

Triangle::Triangle()
{
    float _vertices[]={
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    //qDebug()<<sizeof(_vertices)<<endl;
    mVertices=&_vertices[0];    
}
void Triangle::Bind()
{
    mOpenGLFunctions=QOpenGLContext::currentContext()->functions();
    //qDebug()<<sizeof(float)*9<<endl;
    mShader=new GLSLShader();
    mShader->CreateAndCompileShader(QString("../Viewer/Resources/Shaders/shader.vert"),
                                    QString("../Viewer/Resources/Shaders/shader.frag"));
    mShader->CreateAndLinkProgram();
    mOpenGLFunctions->glGenBuffers(1,&mVbo);
    mOpenGLFunctions->glBindBuffer(GL_ARRAY_BUFFER,mVbo);
    mOpenGLFunctions->glBufferData(GL_ARRAY_BUFFER,sizeof(float)*9,mVertices,GL_STATIC_DRAW);   
    mOpenGLFunctions->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    mOpenGLFunctions->glEnableVertexAttribArray(0);
}

void Triangle::Draw()
{
    mShader->Use();
    mOpenGLFunctions->glDrawArrays(GL_TRIANGLES,0,9);
}
