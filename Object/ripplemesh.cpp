#include "ripplemesh.h"
#include <QSet>
#include <QDebug>

const int RippleMesh::mGridX=5;
const int RippleMesh::mGridZ=5;

RippleMesh::RippleMesh(QString &_pathVertex,QString &_pathFragment,int _w,int _h):Object3d(_w,_h)
{
    mShader=new GLSLShader(_pathVertex,_pathFragment);
}

void RippleMesh::Bind()
{
    //Construct vertex data
    float _vertices[mGridX*mGridZ*3];
    int k=0;
    for(int j=0;j<mGridZ;j++)
        for(int i=0;i<mGridX;i++)
        {
            _vertices[k]=(float)i/(mGridX);
            _vertices[k+1]=0;
            _vertices[k+2]=(float)j/(mGridZ);
            k+=3;
        }
    mVertices=&_vertices[0];

    k=0;
    int vi=0;
    unsigned int _indices[(mGridX-1)*(mGridZ-1)*6];
    for(int j=0;j<mGridZ-1;j++)
        for(int i=0;i<mGridX-1;i++)
        {
            _indices[k]=(vi+j);
            _indices[k+1]=(mGridX-1)+(vi+j)+1;
            _indices[k+2]=(vi+j)+1;
            _indices[k+3]=(mGridX-1)+(vi+j)+1;
            _indices[k+4]=(mGridX-1)+(vi+j)+2;
            _indices[k+5]=(vi+j)+1;
            vi++;
            k+=6;
        }
    mIndices=&_indices[0];

    mOpenGLFunctions=QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();
    mShader->CreateAndCompileShader();
    mShader->CreateAndLinkProgram();
    //Init EBO
    mOpenGLFunctions->glGenBuffers(1,&mEbo);
    //Init VBO
    mOpenGLFunctions->glGenBuffers(1,&mVbo);
    //Init VAO
    mOpenGLFunctions->glGenVertexArrays(1,&mVao);
    //Bind VAO
    mOpenGLFunctions->glBindVertexArray(mVao);
        //Use VBO and EBO for VAO
        mOpenGLFunctions->glBindBuffer(GL_ARRAY_BUFFER,mVbo);
        mOpenGLFunctions->glBufferData(GL_ARRAY_BUFFER,sizeof(float)*mGridX*mGridZ*3,mVertices,GL_STATIC_DRAW);
        mOpenGLFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEbo);
        mOpenGLFunctions->glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*(mGridX-1)*(mGridZ-1)*6,mIndices,GL_STATIC_DRAW);
        mOpenGLFunctions->glEnableVertexAttribArray(0);
        mOpenGLFunctions->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    mOpenGLFunctions->glBindVertexArray(0);
}

void RippleMesh::Draw()
{
    //projection and modelview matrices
    //setup the projection matrix
//    qDebug()<<ScreenWidth<<"-"<<ScreenHeight<<endl;
//    mOpenGLFunctions->glViewport(0,0,ScreenWidth,ScreenHeight);
//    glm::mat4  P = glm::perspective(45.0f,(float)ScreenWidth/ScreenHeight,1.0f,1000.f);
    glm::mat4 model,view;
    model=glm::rotate(model,glm::radians(0.0f),glm::vec3(1,0,0));
    model=glm::translate(model,glm::vec3(-5,0,0));
    model=glm::scale(model,glm::vec3(15,1,15));

    view=glm::translate(view,glm::vec3(0,-2.5,-23));
//    glm::mat4 perspective=glm::perspective(45.0f,(float)ScreenWidth/ScreenHeight,0.01f,100.0f);
    glm::mat4 perspective=glm::perspective(45.0f,(float)1080/720,0.01f,100.0f);
    float time=100.0f;

    mShader->Use();
    GLint mvpAttrib=mOpenGLFunctions->glGetUniformLocation(mShader->ShaderProgram()->programId(),"MVP");
    GLint timeAttrib=mOpenGLFunctions->glGetUniformLocation(mShader->ShaderProgram()->programId(),"time");

    mOpenGLFunctions->glUniform1f(timeAttrib,time);
    mOpenGLFunctions->glUniformMatrix4fv(mvpAttrib,1,GL_FALSE,glm::value_ptr(perspective*view*model));

    mOpenGLFunctions->glBindVertexArray(mVao);
    mOpenGLFunctions->glDrawElements(GL_TRIANGLES,(mGridX-1)*(mGridZ-1)*6,GL_UNSIGNED_INT,0);
    mOpenGLFunctions->glBindVertexArray(0);
}
