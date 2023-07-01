#include "ResourceManager.h"
#include "Game.h"
#include <iostream>
#include "Log.h"
#include "stb_image.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Quad.h"

Game::Game()
{
	this->Init();
}

Game::~Game()
{
}

void Game::Init()
{
	// Initialize logger
	Log::Init(spdlog::level::info);

	// Vertex Array
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Vertex Buffer 
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	float texCoords[] = {
		1.0f, 0.0f,	// Bottom Right
		0.0f, 0.0f,	// Bottom Left
		1.0f, 0.0f	// Top Center
	};


	InitTextures();	

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture Attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


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

	// Identity matrix - Initializing transformation
	glm::mat4 trans = glm::mat4(1.0f);
	// Rotating trans by 90 degrees (converted to radians) around the Z axis
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	// Scaling trans by 0.5 on all axis
	trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

	shader.SetInt("ourTexture", 0);
	shader.SetInt("ourTexture2", 1);
	shader.SetMat4("transform", glm::value_ptr(trans));

	containerShader = shader;

	Quad e;
	e.SetTexture("res/images/container.jpg", 0, GL_RGB);
	e.SetTexture("res/images/awesomeface.png", 1, GL_RGBA);
	e.SetShader("res/shaders/Basic.shader");
	e.Translate(glm::vec3(1.0f, 0.0f, 0.0f));
	e.Rotate(90.0f);
	e.Scale(glm::vec3(0.5f, 0.5f, 0.5f));
}

void Game::ProcessInput()
{
}

void Game::Update()
{
}

void Game::Render()
{
	glm::mat4 trans = glm::mat4(1.0f);
	containerRotation += 0.1f;
	trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0f));
	trans = glm::rotate(trans, glm::radians(containerRotation), glm::vec3(0.0f, 0.0f, 1.0f));
	containerShader.SetMat4("transform", glm::value_ptr(trans));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Game::InitTextures()
{
	Texture texture(
		GL_MIRRORED_REPEAT,
		GL_MIRRORED_REPEAT,
		GL_LINEAR_MIPMAP_LINEAR,
		GL_LINEAR
	);

	Texture texture2(
		GL_MIRRORED_REPEAT,
		GL_MIRRORED_REPEAT,
		GL_LINEAR_MIPMAP_LINEAR,
		GL_LINEAR
	);

	// Image loading
	texture.LoadImg("res/images/container.jpg", GL_RGB);
	texture2.LoadImg("res/images/awesomeface.png", GL_RGBA);

	texture.BindToTextureUnit(0);
	texture2.BindToTextureUnit(1);
}