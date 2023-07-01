#include "ResourceManager.h"
#include <fstream>
#include <iostream>
#include <sstream>     
#include "Log.h"
using namespace std;

Shader ResourceManager::LoadShader(const char* shaderFile)
{
    ifstream file(shaderFile);
    if (!file)
    {
        LOG_ERROR("Could not find shader file!");
        __debugbreak();
    }

    LOG_INFO("Found shader file!");
    string line;
    Shader::ShaderType currentReadType = Shader::NONE; 
    stringstream ss[2];

    while (getline(file, line))
    {
        if (line.find("#shader") != string::npos)
        {
            if (line.find("vertex") != string::npos)
            {
                currentReadType = Shader::VERTEX;
            }
            else if (line.find("fragment") != string::npos)
            {
                currentReadType = Shader::FRAGMENT;
            }
        }
        else if (currentReadType != Shader::NONE)
        {
            ss[currentReadType] << line << "\n";
        }
    }

    file.close();

    return Shader(ss[Shader::VERTEX].str(), ss[Shader::FRAGMENT].str());

}
