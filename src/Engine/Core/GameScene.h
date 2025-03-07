#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "Engine/Core/Events/Event.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Object;
class Transform;

class GameScene : public Object{

public:
	GameScene();
	~GameScene();

protected:
	std::vector<Object*> SceneObjects;

private:

	void RegisterSpawnedObject(Object* RegisterObject);


public:
	GameObject* SpawnObject(GameObject* Spawnable, SinStr::Transform SpawnTransform);
	GameObject* SpawnObject(GameObject* Spawnable, Math::Vector2 SpawnLocation);

	void RenderScene(sf::RenderWindow& Renderer);
	void Update();
	virtual void LoadScene();
	virtual void UnloadScene();
};