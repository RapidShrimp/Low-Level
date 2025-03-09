#pragma once
#include <string>
#include "SFML/Graphics.hpp"
	//Some basic functionality that all game objects should have

class Object
{
public:
	Object();
	~Object();

protected:
	Object* m_Owner = nullptr;

private:
	std::string m_DisplayName = "Unassigned";

public:
	virtual void Init(Object* OwningObject);
	virtual void OnActivate();
	virtual void OnDeactivate();
	virtual void BeginPlay();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void Render(sf::RenderWindow& Renderer);
	virtual void OnDestroy();

	void SetName(std::string NewName) { m_DisplayName = NewName; }
	std::string GetName() { return m_DisplayName; }
	Object* GetOwner() { return m_Owner;}
};