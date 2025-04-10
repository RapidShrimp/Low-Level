#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "string"
#include "Engine/Core/Events/Event.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Object;
class Transform;
class PlayerCharacter;

class GameScene : public Object{

public:
	GameScene();
	~GameScene();

	void RenderScene(sf::RenderWindow& Renderer);
	void FixedUpdate(float DeltaTime);
	void Update();
	virtual void OnLoadScene();
	virtual void UnloadScene();
	virtual PlayerCharacter* GetPlayerCharacter() { return nullptr; } //Override this in Child Scene
protected:
	std::string m_SceneName = "Unassigned";
	std::vector<GameObject*> SceneObjects;

public:	
	GameObject* SpawnObject(GameObject* Spawnable, SinStr::Transform SpawnTransform, bool StartActive = true, std::string DisplayName = "Unassigned");
	GameObject* SpawnObject(GameObject* Spawnable, Math::Vector2 SpawnLocation, bool StartActive = true, std::string DisplayName = "Unassigned");
	const std::vector<GameObject*> GetGameObjects() { return SceneObjects; }
private:

	void RegisterSpawnedObject(GameObject* RegisterObject, bool Activate);
};