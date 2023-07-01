#pragma once
#include "Shader.h"

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
private:
	bool keys[1024];
	float containerRotation = 0;
	Shader containerShader;
public:
	Game();
	~Game();

	GameState state;

	// Load shaders and texture data
	void Init();
	void InitTextures();

	// Game Loop
	void ProcessInput();
	void Update();
	void Render();
};

