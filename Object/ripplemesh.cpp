#include "ripplemesh.h"
#include<QSet>

const int RippleMesh::mGridX=5;
const int RippleMesh::mGridZ=5;

RippleMesh::RippleMesh(QString &_pathVertex,QString &_pathFragment):Object3d()
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
            _vertices[k]=i/(mGridX);
            _vertices[k+1]=0;
            _vertices[k+2]=j/(mGridZ);
            k+=3;
        }
    mVertices=&_vertices[0];

    k=0;
    int vi=0;
    unsigned int _indices[mGridX*mGridZ*6];
    for(int j=0;j<mGridZ;j++)
        for(int i=0;i<mGridX;i++)
        {
            _indices[k]=vi;
            _indices[k+1]=mGridX+vi+1;
            _indices[k+2]=vi+1;
            _indices[k+3]=mGridX+vi+1;
            _indices[k+4]=mGridX+vi+2;
            _indices[k+5]=vi+1;
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
        mOpenGLFunctions->glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*mGridX*mGridZ*6,mIndices,GL_STATIC_DRAW);
        mOpenGLFunctions->glEnableVertexAttribArray(0);
        mOpenGLFunctions->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    mOpenGLFunctions->glBindVertexArray(0);
}

void RippleMesh::Draw()
{
    //projection and modelview matrices
    //setup the projection matrix
    glm::mat4  P = glm::ortho(-1,1,-1,1);
    glm::mat4 MV = glm::mat4(1);

    mShader->Use();
//    GLint mvpAttrib=mOpenGLFunctions->glGetUniformLocation(mShader->ShaderProgram()->programId(),"MVP");
//    mOpenGLFunctions->glUniformMatrix4fv(mvpAttrib,1,GL_FALSE,glm::value_ptr(P*MV));
    mOpenGLFunctions->glBindVertexArray(mVao);
    mOpenGLFunctions->glDrawElements(GL_TRIANGLES,mGridX*mGridZ*6,GL_UNSIGNED_INT,0);
    mOpenGLFunctions->glBindVertexArray(0);
}
