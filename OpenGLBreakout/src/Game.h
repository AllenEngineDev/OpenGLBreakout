#pragma once

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
public:
	Game();
	~Game();

	GameState state;

	// Load shaders and texture data
	void Init();

	// Game Loop
	void ProcessInput();
	void Update();
	void Render();
};

