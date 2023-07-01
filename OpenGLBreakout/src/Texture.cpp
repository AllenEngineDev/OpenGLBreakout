#include "Texture.h"
#include "stb_image.h"
#include "Log.h"

Texture::Texture()
{
	glGenTextures(1, &m_glID);
}

Texture::Texture( int xWrap,  int yWrap,  int minFilter,  int magFilter)
{
	glGenTextures(1, &m_glID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, yWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, xWrap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

Texture::~Texture()
{
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_glID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::LoadImg(const char* imageLocation, GLenum format)
{
	stbi_set_flip_vertically_on_load(true);
	// Image loading
	unsigned char* data = stbi_load(imageLocation, &m_TextureWidth, &m_TextureHeight, &m_NumberColorChannels, 0);
	this->Bind();
	//LOG_INFO("Texture with ID {0} bound!", m_glID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_TextureWidth, m_TextureHeight, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	this->Unbind();
	//LOG_INFO("Texture with ID {0} unbound!", m_glID);
}

void Texture::SetParamI(unsigned int param, unsigned int to)
{
	glTexParameteri(GL_TEXTURE_2D, param, to);
}

void Texture::BindToTextureUnit(unsigned int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_glID);
}
