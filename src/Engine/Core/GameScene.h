#pragma once
#include "SFML/Graphics.hpp"
#include "Engine/Core/Events/Event.h"
#include <SFML/Graphics/RenderWindow.hpp>
using namespace sf;

class Object;

class GameScene {

public:
	SinStr::Event<int> OnSomething;
	GameScene();
	~GameScene();

protected:
	std::vector<Object*> SceneObjects;

private:


public:
	void RegisterSpawnedObject(Object* RegisterObject);
	void RenderScene(RenderWindow& Renderer);
	void Update();
	virtual void LoadScene();
	virtual void UnloadScene();
};