#pragma once
#include "Object.h"
#include "SFML/Graphics.hpp"
#include "Events/Event.h"
#include "GameScene.h"


#define WINDOW_HEIGHT 960
#define WINDOW_WIDTH 720

#define MINIMAP_SIZE 2300
#define MINIMAP_SCREENSIZE 140

class GameInstance {

private:
	GameInstance() {}; //Prevent Direct Instantiate
	GameInstance(const GameInstance&) = delete; //Prevent Copy Constructor
	GameInstance& operator=(const GameInstance&) = delete; //Prevent Copy Assign
	static GameInstance* m_GameInstance;
	~GameInstance();

public:

	//Called Just before primary Update loop, should only be used for timers or other subsystems
	SinStr::Event<> OnUpdate;
	//Called Just before primary Update loop, should only be used for timers or other subsystems
	//float - PhysicsTimeStep
	SinStr::Event<float> OnFixedUpdate; 

	static inline GameInstance* GetGameInstance() /*Create / Get;*/
	{
		if (m_GameInstance == nullptr) { m_GameInstance = new GameInstance(); }
		return m_GameInstance;
	};

	GameScene* GetWorld() { return m_CurrentScene; }
	bool ShouldDrawDebug() { return m_Debug; }
	bool ShouldLogDisplay() { return m_LogDisplay; }

	sf::View& GetUI() { return m_HUD; }
	sf::View& GetCamera() { return m_Camera; }
	const sf::RenderWindow& GetWindow() { return m_GameWindow; }
	const PlayerCharacter* GetPlayer();
	
	void QueueGameScene(GameScene* Next) { m_NextScene = Next; }
	void QueueFree(Object* InObject) { m_ToDelete.push_back(InObject); }
protected:
	void LoadScene();
	sf::RenderWindow m_GameWindow;
	sf::View m_Camera;
	sf::View m_HUD;
	GameScene* m_CurrentScene;
	GameScene* m_NextScene = nullptr;

public:
	bool m_GameExit = false;

	void Init();
	void Update();
	void FixedUpdate(float deltaTime);
	void Render();
	void CloseGame();

private:
	bool m_Debug = false;
	bool m_LogDisplay = true;


	void ClearWaitingObjects();
	std::vector<Object*> m_ToDelete;
};

