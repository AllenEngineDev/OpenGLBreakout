#include "Application.h"
#include "Game.h"
#include "GLFW/glfw3.h"

Application::Application(unsigned int width, unsigned int height, const char* title)
	: m_WindowWidth(width), m_WindowHeight(height), m_WindowTitle(title)
{
	glfwInit();
	CreateWindow();

	m_Game = new Game;
}

Application::~Application()
{
	glfwTerminate();
	delete m_Game;
}

void Application::CreateWindow() 
{
	m_Window = glfwCreateWindow(
		m_WindowWidth,
		m_WindowHeight,
		m_WindowTitle,
		NULL,
		NULL
	);

	glfwMakeContextCurrent(m_Window);
	glewInit();
}

void Application::Run()
{
	while (!glfwWindowShouldClose(m_Window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.8f, 0.2f, 1.0f);

		m_Game->Render();
		m_Game->ProcessInput();
		m_Game->Update();

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}
