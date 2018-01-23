#pragma once
#include <map>
#include <string>
#include <QOpenGLFunctions>

using namespace std;

class GLSLShader
{
public:
	GLSLShader(void);
	~GLSLShader(void);		
    void CreateAndCompileShader(const string &vertexFile,const string &fragmentFile);
	void CreateAndLinkProgram();
	void Use();
	void UnUse();
	void DeleteShaderProgram();


private:
    const char* LoadFromFile(const string& filename);

	enum ShaderType {VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER};
    GLuint	mProgram;
    GLuint mVertexShader;
    GLuint mFragmentShader;
    QOpenGLFunctions *mOpenglFunction;
};	
