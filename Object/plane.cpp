#include "plane.h"
#include <QDebug>

plane::plane(QString &_pathVertex,QString &_pathFragment):Object3d()
{
    mShader=new GLSLShader(_pathVertex,_pathFragment);
}

void plane::Bind()
{
    //Vertex data
    float _vertices[]={
        -0.5,-0.5,0,
        0.5,-0.5,0,
        0.5,0.5,0,
        -0.5,0.5,0
    };
    float _colors[]={
        1,0,0,
        1,1,0,
        1,0,1,
        0,0,1
    };
    unsigned int _indices[]={
        0,3,1,
        3,2,1
    };;
    mVertices=&_vertices[0];
    mColors=&_colors[0];
    mIndices=&_indices[0];

    mOpenGLFunctions=QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();
    mShader->CreateAndCompileShader();
    mShader->CreateAndLinkProgram();
    //Init EBO
    mOpenGLFunctions->glGenBuffers(1,&mEbo);
    //Init VBO
    mOpenGLFunctions->glGenBuffers(1,&mVbo);
    mOpenGLFunctions->glGenBuffers(1,&mVbo2);
    //Init VAO
    mOpenGLFunctions->glGenVertexArrays(1,&mVao);
    //Bind VAO
    mOpenGLFunctions->glBindVertexArray(mVao);
        //Use VBO and EBO for VAO
        mOpenGLFunctions->glBindBuffer(GL_ARRAY_BUFFER,mVbo);
        mOpenGLFunctions->glBufferData(GL_ARRAY_BUFFER,sizeof(float)*12,mVertices,GL_STATIC_DRAW);
        mOpenGLFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEbo);
        mOpenGLFunctions->glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*6,mIndices,GL_STATIC_DRAW);
        mOpenGLFunctions->glEnableVertexAttribArray(0);
        mOpenGLFunctions->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);

        //Use VBO2 for VAO
        mOpenGLFunctions->glBindBuffer(GL_ARRAY_BUFFER,mVbo2);
        mOpenGLFunctions->glBufferData(GL_ARRAY_BUFFER,sizeof(float)*12,mColors,GL_STATIC_DRAW);
        mOpenGLFunctions->glEnableVertexAttribArray(1);
        mOpenGLFunctions->glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    mOpenGLFunctions->glBindVertexArray(0);
}

void plane::Draw()
{
    //projection and modelview matrices
    //setup the projection matrix
    glm::mat4  P = glm::ortho(-1,1,-1,1);
    glm::mat4 MV = glm::mat4(1);

    mShader->Use();
    GLint mvpAttrib=mOpenGLFunctions->glGetUniformLocation(mShader->ShaderProgram()->programId(),"MVP");
    mOpenGLFunctions->glUniformMatrix4fv(mvpAttrib,1,GL_FALSE,glm::value_ptr(P*MV));
    mOpenGLFunctions->glBindVertexArray(mVao);
    mOpenGLFunctions->glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    mOpenGLFunctions->glBindVertexArray(0);
}
