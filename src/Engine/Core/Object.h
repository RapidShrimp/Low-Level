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
	bool isActive = false;
private:
	std::string m_DisplayName = "Unassigned";

public:
	virtual void Init(Object* OwningObject);
	virtual void BeginPlay();

	void Activate();
	void Deactivate();

	virtual void Update();
	virtual void FixedUpdate(float deltaTime);
	virtual void Render(sf::RenderWindow& Renderer);
	virtual void OnDestroy();


protected:
	virtual void OnActivate();
	virtual void OnDeactivate();

public:
	void SetName(std::string NewName) { m_DisplayName = NewName; }
	std::string GetName() { return m_DisplayName; }
	virtual Object* GetOwner() { return m_Owner; }
	virtual void SetOwner(Object& NewOwner) { *m_Owner = NewOwner; }

	virtual bool GetIsActive() { return isActive; }

};