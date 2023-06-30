#include "Application.h"

int main()
{
	Application* app = new Application(800, 600, "Breakout!");
	app->Run();

	delete app;
}