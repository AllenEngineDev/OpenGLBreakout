#pragma once
#include "GL/glew.h"
#include <string>

class Shader
{
public:
	enum ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	Shader(const std::string& vertexSource, const std::string& fragmentSource);
	Shader();
	~Shader();
	void LoadSources(const std::string& vertexSource, const std::string& fragmentSource);
	void Use();
	unsigned int GetID();
	void SetInt(const char* name, int to);
	void SetMat4(const char* name, const GLfloat* value);
private:
	unsigned int m_ProgramID;
	unsigned int m_FragmentShaderID;
	unsigned int m_VertexShaderID;

	unsigned int CompileShader(GLenum shaderType, const char* shaderSource);
};

