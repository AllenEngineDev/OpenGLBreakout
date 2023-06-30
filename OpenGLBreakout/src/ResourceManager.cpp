#include "ResourceManager.h"
#include <fstream>
#include <iostream>
#include <sstream>      // std::stringstream
using namespace std;

Shader ResourceManager::LoadShader(const char* shaderFile)
{
    ifstream file(shaderFile);
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

    std::cout << "VERTEX SOURCE: \n" << ss[Shader::VERTEX].str() << std::endl;
    std::cout << "FRAGMENT SOURCE: \n" << ss[Shader::FRAGMENT].str() << std::endl;

    file.close();

    return Shader(ss[Shader::VERTEX].str(), ss[Shader::FRAGMENT].str());

}
