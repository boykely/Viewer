#include "triangle.h"
#include <QDebug>

Triangle::Triangle(QString &_pathVertex,QString &_pathFragment):Object3d()
{
    mShader=new GLSLShader(_pathVertex,_pathFragment);
}
void Triangle::Bind()
{
    //Vertex data

    float _vertices[]={
        -1,-1,0,
        0,1,0,
        1,-1,0

/*
        // first triangle
             0.5f,  0.5f, 0.0f,  // top right
             0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f,  0.5f, 0.0f,  // top left
            // second triangle
             0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left*/
    };
    float _colors[]={
        1,0,0,
        0,1,0,
        0,0,1
    };

    mVertices=&_vertices[0];
    mColors=&_colors[0];

    mOpenGLFunctions=QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();
    mShader->CreateAndCompileShader();
    mShader->CreateAndLinkProgram();
    //Init VBO
    mOpenGLFunctions->glGenBuffers(1,&mVbo);
    mOpenGLFunctions->glGenBuffers(1,&mVbo2);
    //Init VAO
    mOpenGLFunctions->glGenVertexArrays(1,&mVao);
    //Bind VAO
    mOpenGLFunctions->glBindVertexArray(mVao);
        //Use VBO for VAO
        mOpenGLFunctions->glBindBuffer(GL_ARRAY_BUFFER,mVbo);
        mOpenGLFunctions->glBufferData(GL_ARRAY_BUFFER,sizeof(float)*9,mVertices,GL_STATIC_DRAW);
        mOpenGLFunctions->glEnableVertexAttribArray(0);
        mOpenGLFunctions->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);

        //Use VBO2 for VAO
        mOpenGLFunctions->glBindBuffer(GL_ARRAY_BUFFER,mVbo2);
        mOpenGLFunctions->glBufferData(GL_ARRAY_BUFFER,sizeof(float)*9,mColors,GL_STATIC_DRAW);
        mOpenGLFunctions->glEnableVertexAttribArray(1);
        mOpenGLFunctions->glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);

        mOpenGLFunctions->glBindBuffer(GL_ARRAY_BUFFER,0);

    mOpenGLFunctions->glBindVertexArray(0);
}

void Triangle::Draw()
{
    //projection and modelview matrices
    //setup the projection matrix
    glm::mat4  P = glm::ortho(-1,1,-1,1);
    glm::mat4 MV = glm::mat4(1);

    mShader->Use();
    GLint mvpAttrib=mOpenGLFunctions->glGetUniformLocation(mShader->ShaderProgram()->programId(),"MVP");
    mOpenGLFunctions->glUniformMatrix4fv(mvpAttrib,1,GL_FALSE,glm::value_ptr(P*MV));
    mOpenGLFunctions->glBindVertexArray(mVao);
    //Third parameter is the size of vertices which formed the triangles
    mOpenGLFunctions->glDrawArrays(GL_TRIANGLES,0,3);
}
