#pragma once
#include "Shader.h"

class ResourceManager
{
public:
    static Shader LoadShader(const char* shaderFile);
};
