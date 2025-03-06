#pragma once
#include "GameInstance.h"
#include <iostream>

GameInstance::GameInstance()
{
}

GameInstance::~GameInstance()
{
}

void GameInstance::Init()
{
	m_GameWindow = RenderWindow(VideoMode({ 800,800 }), "Sinistar 2025 Remake");
	m_CurrentScene = make_shared<GameScene>();
	m_CurrentScene->LoadScene();
}

void GameInstance::Update()
{
	while (m_GameWindow.isOpen())
	{
		//Exit Game
		while (const optional event = m_GameWindow.pollEvent()) {
			if (event->is<Event::Closed>())
			{
				CloseGame();
			}
		}
		m_CurrentScene->Update();
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
