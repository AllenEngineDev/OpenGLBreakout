#pragma once
#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

#include "Texture.h"
#include "Shader.h"

class Quad
{
public:
	Quad();
	~Quad();
	void Render();
	void SetTexture(const char* filepath, unsigned int textureUnit, GLenum format);
	void SetShader(const char* filepath);
	void Translate(glm::vec3 by);
	void Rotate(float degrees);
	void Scale(glm::vec3 vector);
private:
	unsigned int m_Vertices[3 + 3 + 2];
	unsigned int m_Indices[6];
	Texture m_Texture;
	Shader m_Shader;
	glm::mat4 m_Transformation;
};
