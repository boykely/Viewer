#include "cube.h"

Cube::Cube(QString &_pathVertex,QString &_pathFragment,int _w,int _h):Object3d(_w,_h)
{
    mShader=new GLSLShader(_pathVertex,_pathFragment);
}

void Cube::Bind()
{
    //Construct vertex data    
    float _vertices[]={
        // front
            -1.0, -1.0,  1.0,
             1.0, -1.0,  1.0,
             1.0,  1.0,  1.0,
            -1.0,  1.0,  1.0,
            // back
            -1.0, -1.0, -1.0,
             1.0, -1.0, -1.0,
             1.0,  1.0, -1.0,
            -1.0,  1.0, -1.0,
    };

    for(int i=0;i<24;i++)
        mVertices.append(_vertices[i]);

    unsigned int _indices[]={
        // front
                0, 1, 2,
                2, 3, 0,
                // top
                1, 5, 6,
                6, 2, 1,
                // back
                7, 6, 5,
                5, 4, 7,
                // bottom
                4, 0, 3,
                3, 7, 4,
                // left
                4, 5, 1,
                1, 0, 4,
                // right
                3, 2, 6,
                6, 7, 3,
    };

    for(int i=0;i<36;i++)
        mIndices.append(_indices[i]);

    float _colors[]={
        // front colors
           1.0, 0.0, 0.0,
           0.0, 1.0, 0.0,
           0.0, 0.0, 1.0,
           1.0, 1.0, 1.0,
           // back colors
           1.0, 0.0, 0.0,
           0.0, 1.0, 0.0,
           0.0, 0.0, 1.0,
           1.0, 1.0, 1.0,
    };

    for(int i=0;i<24;i++)
        mColors.append(_colors[i]);

    mOpenGLFunctions=QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();
    mShader->CreateAndCompileShader();
    mShader->CreateAndLinkProgram();
    //Init EBO
    mOpenGLFunctions->glGenBuffers(1,&mEbo);
    //Init VBO
    mOpenGLFunctions->glGenBuffers(1,&mVbo);
    //Init VBO for COlors
    mOpenGLFunctions->glGenBuffers(1,&mVboColor);
    //Init VAO
    mOpenGLFunctions->glGenVertexArrays(1,&mVao);
    //Bind VAO
    mOpenGLFunctions->glBindVertexArray(mVao);
        //Use VBO vertex, VBO colors and EBO for VAO
        mOpenGLFunctions->glBindBuffer(GL_ARRAY_BUFFER,mVbo);
        mOpenGLFunctions->glBufferData(GL_ARRAY_BUFFER,sizeof(float)*mVertices.count(),&mVertices.front(),GL_STATIC_DRAW);
        mOpenGLFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEbo);
        mOpenGLFunctions->glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*mIndices.count(),&mIndices.front(),GL_STATIC_DRAW);
        mOpenGLFunctions->glEnableVertexAttribArray(0);
        mOpenGLFunctions->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);

        mOpenGLFunctions->glBindBuffer(GL_ARRAY_BUFFER,mVboColor);
        mOpenGLFunctions->glBufferData(GL_ARRAY_BUFFER,sizeof(float)*mColors.count(),&mColors.front(),GL_STATIC_DRAW);
        mOpenGLFunctions->glEnableVertexAttribArray(1);
        mOpenGLFunctions->glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    mOpenGLFunctions->glBindVertexArray(0);
}

void Cube::Draw(Camera *_cam)
{
    mOpenGLFunctions->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glm::mat4 model;
    model=glm::rotate(model,glm::radians(40.0f),glm::vec3(0,1,0));
    model=glm::translate(model,glm::vec3(0,0,0));
    model=glm::scale(model,glm::vec3(5,5,5));

    glm::mat4 view=_cam->View;
//    glm::mat4 perspective=glm::perspective(45.0f,(float)ScreenWidth/ScreenHeight,0.01f,100.0f);
    glm::mat4 perspective=glm::perspective(45.0f,(float)1080/720,0.01f,100.0f);
    float time=100.0f;

    mShader->Use();
    GLint mvpAttrib=mOpenGLFunctions->glGetUniformLocation(mShader->ShaderProgram()->programId(),"MVP");
    GLint timeAttrib=mOpenGLFunctions->glGetUniformLocation(mShader->ShaderProgram()->programId(),"time");

    mOpenGLFunctions->glUniform1f(timeAttrib,time);
    mOpenGLFunctions->glUniformMatrix4fv(mvpAttrib,1,GL_FALSE,glm::value_ptr(perspective*view*model));

    mOpenGLFunctions->glBindVertexArray(mVao);
    mOpenGLFunctions->glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
    mOpenGLFunctions->glBindVertexArray(0);
}
