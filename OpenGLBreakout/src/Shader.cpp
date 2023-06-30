#include "Shader.h"
#include "GL/glew.h"
#include <iostream>

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
{
	m_ProgramID = glCreateProgram();
	m_VertexShaderID = CompileShader(GL_VERTEX_SHADER, vertexSource.c_str());
	m_FragmentShaderID = CompileShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());
	glAttachShader(m_ProgramID, m_VertexShaderID);
	glAttachShader(m_ProgramID, m_FragmentShaderID);
	glLinkProgram(m_ProgramID);
}

unsigned int Shader::CompileShader(GLenum shaderType, const char* shaderSource)
{
	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL); // vertex_shader_source is a GLchar* containing glsl shader source code
	glCompileShader(shader);

	GLint hasCompiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
	if (hasCompiled != GL_TRUE)
	{
		int length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		GLchar message[1024];
		glGetShaderInfoLog(shader, 1024, &length, message);
		
		std::string shaderTypeString =
				shaderType == GL_VERTEX_SHADER ? "VERTEX SHADER: " : "FRAGMENT SHADER: ";
		std::cout << "SHADER COMPILATION ERROR: "
			<< shaderTypeString
			<< message
			<< std::endl;
		
		return 0;
	}

	return shader;
}

Shader::~Shader()
{
	glDeleteProgram(m_ProgramID);
}

void Shader::Use()
{
	glUseProgram(m_ProgramID);
}
