#include "Shader.h"
#include "GL/glew.h"
#include <iostream>
#include "Log.h"

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
{
	m_ProgramID = glCreateProgram();
	m_VertexShaderID = CompileShader(GL_VERTEX_SHADER, vertexSource.c_str());
	m_FragmentShaderID = CompileShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());
	glAttachShader(m_ProgramID, m_VertexShaderID);
	glAttachShader(m_ProgramID, m_FragmentShaderID);
	glLinkProgram(m_ProgramID);
}

Shader::Shader()
{
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

	LOG_INFO("Shader has compiled successfully! Type - {0} ",
		shaderType == GL_VERTEX_SHADER ? "VERTEX SHADER" : "FRAGMENT SHADER");

	return shader;
	
	
}

Shader::~Shader()
{
	glDeleteProgram(m_ProgramID);
}

void Shader::LoadSources(const std::string& vertexSource, const std::string& fragmentSource)
{
	m_VertexShaderID = CompileShader(GL_VERTEX_SHADER, vertexSource.c_str());
	m_FragmentShaderID = CompileShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());

	glAttachShader(m_ProgramID, m_VertexShaderID);
	glAttachShader(m_ProgramID, m_FragmentShaderID);
	glLinkProgram(m_ProgramID);
}

void Shader::Use()
{
	glUseProgram(m_ProgramID);
}

unsigned int Shader::GetID()
{
	return m_ProgramID;
}

void Shader::SetInt(const char* name, int to)
{
	glUniform1i(glGetUniformLocation(m_ProgramID, name), to);
}

void Shader::SetMat4(const char* name, const GLfloat* value)
{
	unsigned int location = glGetUniformLocation(m_ProgramID, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, value);
}
