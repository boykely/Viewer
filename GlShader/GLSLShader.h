#pragma once
#include <map>
#include <string>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QList>

using namespace std;

class GLSLShader
{
public:
    GLSLShader(QString &_pathVertex,QString &_pathFragment);
	~GLSLShader(void);		
    void CreateAndCompileShader();
	void CreateAndLinkProgram();
	void Use();
	void UnUse();
	void DeleteShaderProgram();
    QOpenGLShaderProgram *ShaderProgram(){return &shaderProgram;}


private:
    QString LoadFromFile(const string& filename);

	enum ShaderType {VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER};
    QList<QOpenGLShader*> *codeShader;
    QOpenGLShaderProgram shaderProgram;
    GLuint	mProgram;
    GLuint mVertexShader;
    GLuint mFragmentShader;
    QOpenGLFunctions_4_5_Core *mOpenglFunction;
    QString mPathVertex;
    QString mPathFragment;
};	
