#include "GLSLShader.h"
#include <iostream>
#include <fstream>
#include <QDebug>

GLSLShader::GLSLShader(void)
{
    mOpenglFunction=QOpenGLContext::currentContext()->functions();
    if(!mOpenglFunction)
    {
        qDebug()<<"Le contexte opengl lance une erreur"<<endl;
        exit(0);
    }
}

GLSLShader::~GLSLShader(void)
{

}

void GLSLShader::CreateAndCompileShader(const string &vertexFile,const string &fragmentFile)
{
    mOpenglFunction->glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSourceShader=LoadFromFile(vertexFile);
    mOpenglFunction->glShaderSource(mVertexShader,1,&vertexSourceShader,NULL);
    mOpenglFunction->glCompileShader(mVertexShader);
    int success;
    char infoLog[512];
    mOpenglFunction->glGetShaderiv(mVertexShader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        mOpenglFunction->glGetShaderInfoLog(mVertexShader,512,NULL,infoLog);
        qDebug()<<"VERTEX Shader compilation error:"<<QString(infoLog)<<endl;
    }
    mOpenglFunction->glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSourceShader=LoadFromFile(fragmentFile);
    mOpenglFunction->glShaderSource(mFragmentShader,1,&fragmentSourceShader,NULL);
    mOpenglFunction->glCompileShader(mFragmentShader);
    mOpenglFunction->glGetShaderiv(mFragmentShader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        mOpenglFunction->glGetShaderInfoLog(mVertexShader,512,NULL,infoLog);
        qDebug()<<"FRAGMENT Shader compilation error:"<<infoLog<<endl;
    }
}

void GLSLShader::DeleteShaderProgram() {	
}

void GLSLShader::CreateAndLinkProgram() {
    mProgram= mOpenglFunction->glCreateProgram();
    mOpenglFunction->glAttachShader(mProgram,mVertexShader);
    mOpenglFunction->glAttachShader(mProgram,mFragmentShader);
    mOpenglFunction->glLinkProgram(mProgram);
    int success;
    char infoLog[512];
    mOpenglFunction->glGetProgramiv(mProgram,GL_LINK_STATUS,&success);
    if(!success)
    {
        mOpenglFunction->glGetProgramInfoLog(mProgram,512,NULL,infoLog);
        qDebug()<<"LINKAGE SHader error:"<<infoLog<<endl;
    }
    mOpenglFunction->glDeleteShader(mVertexShader);
    mOpenglFunction->glDeleteShader(mFragmentShader);
}

void GLSLShader::Use() {
    mOpenglFunction->glUseProgram(mProgram);
}

void GLSLShader::UnUse() {
    mOpenglFunction->glDeleteProgram(mProgram);
}

const char *GLSLShader::LoadFromFile(const string& filename){
	ifstream fp;
	fp.open(filename.c_str(), ios_base::in);
	if(fp) {		 
		string line, buffer;
		while(getline(fp, line)) {
			buffer.append(line);
			buffer.append("\r\n");
        }
        return buffer.c_str();
	} else {
        qDebug()<<"Error loading shader: "<<filename.c_str()<<endl;
        return NULL;
	}
}
