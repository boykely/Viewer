#include "plane.h"
#include <QSet>
#include <QDebug>
#include <QtMath>

const int Plane::mGridX=5;
const int Plane::mGridZ=5;

Plane::Plane(QString &_pathVertex,QString &_pathFragment,bool circle,int _w,int _h):Object3d(_w,_h),isCircle(circle)
{
    mShader=new GLSLShader(_pathVertex,_pathFragment);
}

void Plane::Bind()
{
    //Construct vertex data
    if(isCircle)
    {
        double step=qDegreesToRadians(1.0);
        double tour=qDegreesToRadians(360.0);
        double angle=0.0;
        mVertices.append(0);
        mVertices.append(0);
        mVertices.append(0);
        while(angle<tour)
        {
            mVertices.append(qCos(angle));
            mVertices.append(0);
            mVertices.append(qSin(angle));
            angle+=step;
        }
        for(int i=0;i<mVertices.count();i++)
        {
            if(i==mVertices.count()-1)
            {
                mIndices.append(0);
                mIndices.append(1);
                mIndices.append(i);
            }
            else
            {
                mIndices.append(0);
                mIndices.append(i+2);
                mIndices.append(i+1);
            }
        }
    }
    else
    {
        int k=0;
        for(int j=0;j<mGridZ;j++)
            for(int i=0;i<mGridX;i++)
            {
                mVertices.append((float)i/(mGridX));
                mVertices.append(0);
                mVertices.append((float)j/(mGridZ));
                k+=3;
            }

        k=0;
        int vi=0;
        for(int j=0;j<mGridZ-1;j++)
            for(int i=0;i<mGridX-1;i++)
            {
                mIndices.append(vi+j);
                mIndices.append((mGridX-1)+(vi+j)+1);
                mIndices.append((vi+j)+1);
                mIndices.append((mGridX-1)+(vi+j)+1);
                mIndices.append((mGridX-1)+(vi+j)+2);
                mIndices.append((vi+j)+1);
                vi++;
                k+=6;
            }
    }

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
        mOpenGLFunctions->glBufferData(GL_ARRAY_BUFFER,sizeof(float)*mVertices.count(),&mVertices.front(),GL_STATIC_DRAW);
        mOpenGLFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEbo);
        mOpenGLFunctions->glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*mIndices.count(),&mIndices.front(),GL_STATIC_DRAW);
        mOpenGLFunctions->glEnableVertexAttribArray(0);
        mOpenGLFunctions->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    mOpenGLFunctions->glBindVertexArray(0);
}

void Plane::Draw()
{
    mOpenGLFunctions->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    //projection and modelview matrices
    //setup the projection matrix
//    qDebug()<<ScreenWidth<<"-"<<ScreenHeight<<endl;
//    mOpenGLFunctions->glViewport(0,0,ScreenWidth,ScreenHeight);
//    glm::mat4  P = glm::perspective(45.0f,(float)ScreenWidth/ScreenHeight,1.0f,1000.f);
    glm::mat4 model,view;
    model=glm::rotate(model,glm::radians(0.0f),glm::vec3(1,0,0));
    model=glm::translate(model,glm::vec3(0,0,0));
    model=glm::scale(model,glm::vec3(15,1,15));

    view=glm::translate(view,glm::vec3(0,-2.5,-23));
//    glm::mat4 perspective=glm::perspective(45.0f,(float)ScreenWidth/ScreenHeight,0.01f,100.0f);
    glm::mat4 perspective=glm::perspective(45.0f,(float)1080/720,0.01f,100.0f);

    mShader->Use();
    GLint mvpAttrib=mOpenGLFunctions->glGetUniformLocation(mShader->ShaderProgram()->programId(),"MVP");

    mOpenGLFunctions->glUniformMatrix4fv(mvpAttrib,1,GL_FALSE,glm::value_ptr(perspective*view*model));

    mOpenGLFunctions->glBindVertexArray(mVao);
    mOpenGLFunctions->glDrawElements(GL_TRIANGLES,mIndices.count(),GL_UNSIGNED_INT,0);
    mOpenGLFunctions->glBindVertexArray(0);
}
