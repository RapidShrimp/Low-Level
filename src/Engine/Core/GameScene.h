#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
using namespace sf;

class Object;

class GameScene {

public:
	GameScene();
	~GameScene();

protected:
	std::vector<Object*> SceneObjects;

private:


public:
	void RegisterSpawnedObject(Object* RegisterObject);
	void RenderScene(RenderWindow& Renderer);
	virtual void LoadScene();
	virtual void UnloadScene();
};