#pragma once
#include "Game/Scenes/GameLevel.h"
#include "Game/Scenes/MainMenu.h"
#include "GameInstance.h"
#include "Engine/Core/Input/InputSystem.h"
#include "Engine/Core/Libs/GameFunctionLib.h"

InputEventHandler* InputEventHandler::m_InputSystemInstance = nullptr;

GameInstance::~GameInstance()
{
}

void GameInstance::LoadScene(GameScene* NewScene)
{
	m_CurrentScene->UnloadScene();
	m_CurrentScene = NewScene;
	m_CurrentScene->OnLoadScene();
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
	m_GameWindow = sf::RenderWindow(sf::VideoMode({ 720,960}), "Sinistar 2025 Remake");
	InputEventHandler::GetInstance();
	m_CurrentScene = new MainMenu();
	//m_CurrentScene = new GameLevel();
	m_CurrentScene->OnLoadScene();
}

void GameInstance::Update()
{

	std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
	float deltaTime = 0;
	float timeSinceLastPhysics = 0.0f;
	float physicsTimeStep = 2000;

	while (m_GameWindow.isOpen())
	{

		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - lastTime).count();
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

		if (timeSinceLastPhysics >= physicsTimeStep)
		{
			//Convert from Micro to Miliseconds
			FixedUpdate(deltaTime / 1000.f);
			timeSinceLastPhysics -= physicsTimeStep;
		}
		m_CurrentScene->Update();
		Render();
		InputEventHandler::GetInstance()->PollInputEvents();
		
	}
}

void GameInstance::FixedUpdate(float deltaTime)
{
	m_CurrentScene->FixedUpdate(deltaTime);
}

void GameInstance::Render() 
{
	m_GameWindow.clear();
	m_CurrentScene->RenderScene(m_GameWindow);
	m_GameWindow.display();
}

void GameInstance::CloseGame()
{
	m_CurrentScene->UnloadScene();
	m_GameWindow.close();
}
