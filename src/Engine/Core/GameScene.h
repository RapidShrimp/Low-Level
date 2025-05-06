#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "string"
#include "Engine/Core/Events/Event.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "UI/UI_Base.h"

class Object;
class Transform;
class AsteroidManager;
class PlayerCharacter;

class GameScene : public Object{

public:
	GameScene();
	~GameScene();

	SinStr::Event<bool> OnPausedChanged;

	void RenderScene(sf::RenderWindow& Renderer);
	void RenderUI(sf::RenderWindow& Renderer);

	void FixedUpdate(float DeltaTime);
	void Update();
	virtual void OnLoadScene();
	virtual void OnSceneLoaded();
	virtual void UnloadScene();
	virtual PlayerCharacter* GetPlayerCharacter() { return nullptr; } //Override this in Child Scene

	//Pauses All core Game loop Elements && Independant Timers will not tick
	//*Note* UI Will still update when the game is paused
	void SetGamePaused(bool isPaused) {  m_GamePaused = isPaused; OnPausedChanged(m_GamePaused);}
	bool IsGamePaused() { return m_GamePaused; }
protected:

	std::string m_SceneName = "Unassigned";
	std::vector<GameObject*> SceneObjects;
	std::vector<UI_Base*> UI_Elements;


	bool m_GamePaused = false; 
public:	
	UI_Base* SpawnUIElement(UI_Base* Spawnable, SinStr::Transform UI_Transform, bool StartEnabled);
	UI_Base* SpawnUIElement(UI_Base* Spawnable, Math::Vector2 UI_Location, bool StartEnabled);

	GameObject* SpawnObject(GameObject* Spawnable, SinStr::Transform SpawnTransform, bool StartActive = true, std::string DisplayName = "Unassigned");
	GameObject* SpawnObject(GameObject* Spawnable, Math::Vector2 SpawnLocation, bool StartActive = true, std::string DisplayName = "Unassigned");
	const std::vector<GameObject*> GetGameObjects() { return SceneObjects; }

	/*
	Finds the first registered Object of a specific type
	returns nullptr if no object found
	*/
	template<typename U> 
	U* FindRegisteredObjectOfType();

	/*
	* Finds all registered objects of a specific type
	* This is a slow operation, use sparingly
	* Returns empty vector if no objects exist
	*/
	template<typename U>
	vector<U*> FindAllRegisteredObjectsOfType();

private:

	void RegisterSpawnedObject(GameObject* RegisterObject, bool Activate);
};

template<typename U>
inline U* GameScene::FindRegisteredObjectOfType()
{
	for (int ObjectIndex = 0; ObjectIndex < SceneObjects.size(); ObjectIndex++)
	{
		U* FoundObject = dynamic_cast<U*>(SceneObjects[ObjectIndex]);
		if (FoundObject != nullptr) { return FoundObject; }
	}
	return nullptr;
}

template<typename U>
inline vector<U*> GameScene::FindAllRegisteredObjectsOfType()
{
	std::vector<U*> foundObjects;

	for (int ObjectIndex = 0; ObjectIndex < SceneObjects.size(); ObjectIndex++)
	{
		U* FoundObject = dynamic_cast<U*>(SceneObjects[ObjectIndex]);
		if (FoundObject != nullptr) 
		{
			foundObjects.push_back(FoundObject);
		}
	}

	return foundObjects;
}
