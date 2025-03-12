#pragma once
#include "Object.h"
#include "SFML/Graphics.hpp"
#include "GameScene.h"
#include "Engine/Core/Input/InputSystem.h"


class GameInstance {
public:

	GameInstance();
	~GameInstance();

	bool m_GameExit = false;
protected:
	shared_ptr<GameScene> m_CurrentScene;
	shared_ptr<GameScene> m_NextScene;
	sf::RenderWindow m_GameWindow;
	InputEventHandler* InputEvents = nullptr;
public:
	void Init();
	void Update();
	void FixedUpdate(float deltaTime);
	void Render();
	void CloseGame();
};