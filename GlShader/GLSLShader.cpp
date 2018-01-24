#include "GLSLShader.h"
#include <iostream>
#include <fstream>
#include <QDebug>

GLSLShader::GLSLShader(QString &_pathVertex,QString &_pathFragment):mPathVertex(_pathVertex),mPathFragment(_pathFragment)
{
    mOpenglFunction=QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();
    if(!mOpenglFunction)
    {
        qDebug()<<"Le contexte opengl lance une erreur"<<endl;
        exit(0);
    }
}

GLSLShader::~GLSLShader(void)
{

}

void GLSLShader::CreateAndCompileShader()
{
    codeShader=new QList<QOpenGLShader*>();
    codeShader->append(new QOpenGLShader(QOpenGLShader::Vertex));
    if(!codeShader->at(0)->compileSourceFile(mPathVertex))
    {
        qDebug()<<"VERTEX SHADER COMPILATION ERROR:"<<codeShader->at(0)->log()<<endl;
    }
    mVertexShader=codeShader->at(0)->shaderId();

    codeShader->append(new QOpenGLShader(QOpenGLShader::Fragment));
    if(!codeShader->at(1)->compileSourceFile(mPathFragment))
    {
        qDebug()<<"FRAGMENT SHADER COMPILATION ERROR:"<<codeShader->at(1)->log()<<endl;
    }
    mFragmentShader=codeShader->at(1)->shaderId();
    //

}

void GLSLShader::DeleteShaderProgram() {	
}

void GLSLShader::CreateAndLinkProgram() {
    if(!shaderProgram.create())
        qDebug()<<"Shader program not created"<<endl;
    mProgram=shaderProgram.programId();
    shaderProgram.addShader(codeShader->at(0));
    shaderProgram.addShader(codeShader->at(1));
    if(!shaderProgram.link())
        qDebug()<<"LINKAGE SHADER ERROR:"<<shaderProgram.log()<<endl;

    mOpenglFunction->glDeleteShader(mVertexShader);
    mOpenglFunction->glDeleteShader(mFragmentShader);

}

void GLSLShader::Use() {
    shaderProgram.bind();
}

void GLSLShader::UnUse() {
    shaderProgram.release();
}

QString GLSLShader::LoadFromFile(const string& filename){
	ifstream fp;
	fp.open(filename.c_str(), ios_base::in);
	if(fp) {		 
        string line,buffer;
		while(getline(fp, line)) {
			buffer.append(line);
			buffer.append("\r\n");
        }
        //qDebug()<<QString(buffer.c_str())<<endl;
        return QString(buffer.c_str());
	} else {
        qDebug()<<"Error loading shader: "<<filename.c_str()<<endl;
        exit(0);
	}
}
