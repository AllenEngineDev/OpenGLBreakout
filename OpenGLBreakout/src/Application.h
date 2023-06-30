#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Game.h"

class Application
{
public:
	Application(unsigned int width, unsigned int height, const char* title);
	~Application();
	void Run();
private:
	Game* m_Game;
	GLFWwindow* m_Window;
	unsigned int m_WindowWidth;
	unsigned int m_WindowHeight;
	const char* m_WindowTitle;

	void CreateWindow();
};

