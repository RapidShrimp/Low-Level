#pragma once
#include "Object.h"
#include "SFML/Graphics.hpp"
#include "GameScene.h"

using namespace std;
using namespace sf;

class GameInstance {


public:

	GameInstance();
	~GameInstance();

	bool m_GameExit = false;
protected:
	shared_ptr<GameScene> m_CurrentScene;
	shared_ptr<GameScene> m_NextScene;
	RenderWindow m_GameWindow;

public:
	void Init();
	void Update();
	void Render();
	void CloseGame();
};