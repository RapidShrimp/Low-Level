#pragma once
#include "Game/Scenes/GameLevel.h"
#include "Game/Scenes/MainMenu.h"
#include "GameInstance.h"
#include "Engine/Core/AudioManager.h"
#include "Engine/Core/Input/InputSystem.h"
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Game/Player/PlayerCharacter.h"

InputEventHandler* InputEventHandler::m_InputSystemInstance = nullptr;
AudioManger* AudioManger::m_AudioManger = nullptr;

GameInstance::~GameInstance()
{
}

void GameInstance::LoadScene(GameScene* NewScene)
{
	m_CurrentScene->UnloadScene();
	m_CurrentScene = NewScene;
	m_CurrentScene->OnLoadScene();
	m_CurrentScene->OnSceneLoaded();
}

const PlayerCharacter* GameInstance::GetPlayer()
{
	if (m_CurrentScene == nullptr) {
		Debug::Log(nullptr, Error, "No Scene Loaded when calling get player, Fatal Error");
		return nullptr;
	}
	if(m_CurrentScene->GetPlayerCharacter() == nullptr)
	{
		Debug::Log(nullptr, Warning, "No Player Loaded into the scene");
		return nullptr;
	}
	return m_CurrentScene->GetPlayerCharacter();;
}

void GameInstance::Init(/*TODO - Game Scene ClassType To Load Into*/)
{
  	m_GameWindow = sf::RenderWindow(sf::VideoMode({ WINDOW_WIDTH,WINDOW_HEIGHT }), "Sinistar 2025 Remake");
	m_Camera = sf::View(sf::FloatRect{ {0,0},{WINDOW_WIDTH,WINDOW_HEIGHT} });
	m_Camera.setCenter({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
	
	m_HUD = sf::View(sf::FloatRect{ {0,0},{WINDOW_WIDTH,WINDOW_HEIGHT} });

	//Subsystem Singletons
	InputEventHandler::GetInstance();
	AudioManger::GetAudioInstance();

	//Load Main Menu
	m_CurrentScene = new MainMenu();
	m_CurrentScene->OnLoadScene();
}

void GameInstance::Update()
{

	std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
	float deltaTime = 0;
	float timeSinceLastPhysics = 0.0f;
	float physicsTimeStep = 2; // 2 milliseconds
	while (m_GameWindow.isOpen())
	{
		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastTime).count();
		lastTime = std::chrono::steady_clock::now();
		timeSinceLastPhysics += deltaTime;

		
		//Exit Game
		while (const optional event = m_GameWindow.pollEvent()) {
			if (event->is<sf::Event::Closed>())
			{
				CloseGame();
				return;
			}
		}


		while (timeSinceLastPhysics >= physicsTimeStep)
		{
			FixedUpdate(physicsTimeStep);
			OnFixedUpdate.Invoke(physicsTimeStep);
			timeSinceLastPhysics -= physicsTimeStep;

		}

		OnUpdate.Invoke();
		m_CurrentScene->Update();
		Render();
		InputEventHandler::GetInstance()->PollInputEvents();
		
		ClearWaitingObjects();
	}
}

void GameInstance::FixedUpdate(float deltaTime)
{
	m_CurrentScene->FixedUpdate(deltaTime);
}

void GameInstance::Render() 
{
	m_GameWindow.clear();
	
	//Gameplay
	m_CurrentScene->RenderScene(m_GameWindow);
	if (m_CurrentScene->GetPlayerCharacter() != nullptr) {
		m_Camera.setCenter((m_CurrentScene->GetPlayerCharacter()->m_Transform.Location).ToSF() - sf::Vector2f(0,70));
		m_GameWindow.setView(m_Camera);
	}

	//UI
	m_GameWindow.setView(m_HUD);
	m_CurrentScene->RenderUI(m_GameWindow);
	// set the shape color to green


	//Final Draw
	m_GameWindow.setView(m_Camera);
	m_GameWindow.display();
}

void GameInstance::CloseGame()
{
	m_CurrentScene->UnloadScene();
	m_GameWindow.close();
}

void GameInstance::ClearWaitingObjects()
{
	for (Object* Obj : m_ToDelete) {
		delete Obj;
	}

	m_ToDelete.clear();
}
