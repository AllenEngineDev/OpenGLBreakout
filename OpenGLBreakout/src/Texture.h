#pragma once
#include "GL/glew.h"

class Texture
{
public:
	Texture();
	Texture(int xWrap,  int yWrap,  int minFilter,  int magFilter);
	~Texture();
	void Bind();
	void Unbind();
	void LoadImg(const char* imageLocation, GLenum format);
	void SetParamI(unsigned int param, unsigned int to);
	void BindToTextureUnit(unsigned int unit);
private:
	unsigned int m_glID = 0;
	int m_TextureWidth = 0;
	int m_TextureHeight = 0;
	int m_NumberColorChannels = 0;
};

