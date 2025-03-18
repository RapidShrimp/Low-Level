#pragma once
#include "Object.h"
#include "SFML/Graphics.hpp"
#include "GameScene.h"

class GameInstance {

private:
	GameInstance() {}; //Prevent Direct Instantiate
	GameInstance(const GameInstance&) = delete; //Prevent Copy Constructor
	GameInstance& operator=(const GameInstance&) = delete; //Prevent Copy Assign
	static GameInstance* m_GameInstance;
	~GameInstance();

public:
	static inline GameInstance* GetGameInstance() /*Create / Get;*/
	{
		if (m_GameInstance == nullptr) { m_GameInstance = new GameInstance(); }
		return m_GameInstance;
	};

	GameScene* GetWorld() { return m_CurrentScene; }

protected:
	sf::RenderWindow m_GameWindow;
	GameScene* m_CurrentScene;
	GameScene* m_NextScene;

public:
	bool m_GameExit = false;

	void Init();
	void Update();
	void FixedUpdate(float deltaTime);
	void Render();
	void CloseGame();
};

