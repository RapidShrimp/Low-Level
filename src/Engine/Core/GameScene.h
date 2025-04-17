#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "string"
#include "Engine/Core/Events/Event.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "UI/UI_Base.h"

class Object;
class Transform;
class PlayerCharacter;

class GameScene : public Object{

public:
	GameScene();
	~GameScene();

	void RenderScene(sf::RenderWindow& Renderer);
	void RenderUI(sf::RenderWindow& Renderer);

	void FixedUpdate(float DeltaTime);
	void Update();
	virtual void OnLoadScene();
	virtual void UnloadScene();
	virtual PlayerCharacter* GetPlayerCharacter() { return nullptr; } //Override this in Child Scene
protected:
	std::string m_SceneName = "Unassigned";
	std::vector<GameObject*> SceneObjects;
	std::vector<UI_Base*> UI_Elements;

public:	
	UI_Base* SpawnUIElement(UI_Base* Spawnable, SinStr::Transform UI_Transform, bool StartEnabled);
	UI_Base* SpawnUIElement(UI_Base* Spawnable, Math::Vector2 UI_Location, bool StartEnabled);

	GameObject* SpawnObject(GameObject* Spawnable, SinStr::Transform SpawnTransform, bool StartActive = true, std::string DisplayName = "Unassigned");
	GameObject* SpawnObject(GameObject* Spawnable, Math::Vector2 SpawnLocation, bool StartActive = true, std::string DisplayName = "Unassigned");
	const std::vector<GameObject*> GetGameObjects() { return SceneObjects; }
private:

	void RegisterSpawnedObject(GameObject* RegisterObject, bool Activate);
};