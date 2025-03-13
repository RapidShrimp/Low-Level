#pragma once
#include "Object.h"
#include "SFML/Graphics.hpp"
#include "GameScene.h"
class InputEventHandler;
class GameInstance {
public:
	
	GameInstance();
	~GameInstance();

	bool m_GameExit = false;
protected:
	shared_ptr<GameScene> m_CurrentScene;
	shared_ptr<GameScene> m_NextScene;
	sf::RenderWindow m_GameWindow;
	InputEventHandler* m_InputSystem;
public:
	void Init();
	void Update();
	void FixedUpdate(float deltaTime);
	void Render();
	void CloseGame();
};