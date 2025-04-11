#pragma once
#include "main.h"
#include <iostream>
#include "Engine/Core/GameInstance.h"

GameInstance* GameInstance::m_GameInstance = nullptr;

int main()
{
	InitialiseEngine();
	Shutdown();
	return 0;
}

void InitialiseEngine() 
{
	cout << "Initialise Sinistar" << endl;
	GameInstance::GetGameInstance()->Init();
	GameInstance::GetGameInstance()->Update();
}

void Shutdown()
{
	cout << "Sinistar Shut Down..." << endl;
}



//#include <SFML/Graphics.hpp>

/*
    This version of the SFML "hello world" is statically linked, you may wish to try the dynamically linked version as well.
*/
//#define WINDOW_HEIGHT 480
//#define WINDOW_WIDTH 640
//#ifdef _DEBUG
//int main()
//#else
//int WinMain()
//#endif
//{
//    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "SFML works!");
//    // create a view with the rectangular area of the 2D world to show
//    sf::View gameView(sf::FloatRect({ 0.f, 0.f }, { WINDOW_WIDTH, WINDOW_HEIGHT }));
//    sf::View minimapView(sf::FloatRect({ 0.f, 0.f }, { WINDOW_WIDTH, WINDOW_HEIGHT }));
//
//    // the game view (full window)
//    gameView.setViewport(sf::FloatRect({ 0.f, 0.f }, { 1.f, 1.f }));
//    // mini-map (upper-right corner)
//    minimapView.setViewport(sf::FloatRect({ 0.75f, 0.f }, { 0.25f, 0.25f }));
//
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//    sf::CircleShape shape2(100.f);
//    shape2.setFillColor(sf::Color::Cyan);
//    shape2.setPosition({ 300.0f, 50.0f });
//
//    sf::RectangleShape rectangle({ WINDOW_WIDTH - 20, WINDOW_HEIGHT - 20 });
//    rectangle.setOrigin({ -10.0f, -10.0f });
//    rectangle.setFillColor(sf::Color(0, 0, 0, 128));
//    rectangle.setOutlineThickness(10.f);
//    rectangle.setOutlineColor(sf::Color(255, 0, 0));
//
//    while (window.isOpen())
//    {
//        // Event polling section of code - this must be done in the thread which created the window
//        // we will talk about threading later, but essentially this must be done here
//        while (const std::optional event = window.pollEvent())
//        {
//            if (event->is<sf::Event::Closed>())
//                window.close();
//        }
//
//        window.clear();
//        // draw full size game
//        window.setView(gameView);
//        window.draw(shape);
//        window.draw(shape2);
//        // draw minimap
//        window.setView(minimapView);
//        window.draw(rectangle);
//        window.draw(shape);
//        window.draw(shape2);
//        window.display();
//    }
//}
