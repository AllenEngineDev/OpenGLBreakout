#include "ResourceManager.h"
#include "Game.h"
#include "Shader.h"
#include <iostream>


Game::Game()
{
	this->Init();
}

Game::~Game()
{
}

void Game::Init()
{
	// Initialize 
	std::cout << "Game has been initialized" << std::endl;

	// Vertex Array
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Vertex Buffer 
	// Quad
	float positions[] = {
		-0.5f,  0.5f, // 0
		 0.5f,  0.5f, // 1
		 0.5f, -0.5f, // 2
		-0.5f, -0.5f  // 3
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 2, positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	// Index Buffer
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3 * 2, indices, GL_STATIC_DRAW);

	// Shader
	Shader shader = ResourceManager::LoadShader("res/shaders/Basic.shader");
	shader.Use();
}

void Game::ProcessInput()
{
}

void Game::Update()
{
}

void Game::Render()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
