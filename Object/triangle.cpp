#include "triangle.h"
#include <QDebug>

Triangle::Triangle()
{

}
void Triangle::Bind()
{
    //Vertex data
    float _vertices[]={
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f/*
        // first triangle
             0.5f,  0.5f, 0.0f,  // top right
             0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f,  0.5f, 0.0f,  // top left
            // second triangle
             0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left*/
    };

    mVertices=&_vertices[0];

    mOpenGLFunctions=QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();
    mShader=new GLSLShader();
    QString pathVertex("../sans_titre/Resources/Shaders/shader.vert");
    QString pathFragment("../sans_titre/Resources/Shaders/shader.frag");
    mShader->CreateAndCompileShader(pathVertex,pathFragment);
    mShader->CreateAndLinkProgram();
    //Init VBO
    mOpenGLFunctions->glGenBuffers(1,&mVbo);
    //Init VAO
    mOpenGLFunctions->glGenVertexArrays(1,&mVao);
    //Bind VAO
    mOpenGLFunctions->glBindVertexArray(mVao);
    //Use VBO for VAO
    mOpenGLFunctions->glBindBuffer(GL_ARRAY_BUFFER,mVbo);
    mOpenGLFunctions->glBufferData(GL_ARRAY_BUFFER,sizeof(float)*9,mVertices,GL_STATIC_DRAW);
    //mOpenGLFunctions->glBufferData(GL_ARRAY_BUFFER,sizeof(float)*18,mVertices,GL_STATIC_DRAW);
    mOpenGLFunctions->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);

    mOpenGLFunctions->glEnableVertexAttribArray(0);
    mOpenGLFunctions->glBindBuffer(GL_ARRAY_BUFFER,0);
    mOpenGLFunctions->glBindVertexArray(0);
}

void Triangle::Draw()
{
    mShader->Use();
    mOpenGLFunctions->glBindVertexArray(mVao);
    mOpenGLFunctions->glDrawArrays(GL_TRIANGLES,0,3);
}
