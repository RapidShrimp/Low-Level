#pragma once
#include "GameInstance.h"
#include <Game/Scenes/GameLevel.h>

GameInstance::GameInstance()
{
}

GameInstance::~GameInstance()
{
}

void GameInstance::Init(/*TODO - Game Scene ClassType To Load Into*/)
{
	m_GameWindow = RenderWindow(VideoMode({ 800,800 }), "Sinistar 2025 Remake");
	m_CurrentScene = make_shared<GameLevel>();
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
			if (event->is<Event::Closed>())
			{
				CloseGame();
				return;
			}
		}
		m_CurrentScene->Update();


		while (timeSinceLastPhysics >= physicsTimeStep)
		{
			FixedUpdate(deltaTime);
			timeSinceLastPhysics -= physicsTimeStep;
		}


		Render();
	}
}

void GameInstance::FixedUpdate(float deltaTime)
{
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
