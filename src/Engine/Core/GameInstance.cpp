#pragma once
#include "GameInstance.h"



void GameInstance::Init()
{
	RenderWindow GameWindow(VideoMode({ 800,800 }), "Sinistar 2025 Remake");
	CurrentScene = make_shared<GameScene>();
}

void GameInstance::Update()
{
	Render();
}


void GameInstance::Render() {
	
	while (GameWindow.isOpen())
	{
		while (const optional event = GameWindow.pollEvent()) {
			if (event->is<Event::Closed>())
			{
				GameWindow.close();
			}
		}

		CircleShape Shape(240.0f);
		Shape.setFillColor(Color::Green);

		GameWindow.clear();
		GameWindow.draw(Shape);
		//CurrentScene->RenderScene(GameWindow);
		//Draw Game Object Loop
		GameWindow.display();
	}
}