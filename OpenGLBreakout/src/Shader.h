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
	~Shader();
	void Use();
private:
	unsigned int m_ProgramID;
	unsigned int m_FragmentShaderID;
	unsigned int m_VertexShaderID;

	unsigned int CompileShader(GLenum shaderType, const char* shaderSource);
};

