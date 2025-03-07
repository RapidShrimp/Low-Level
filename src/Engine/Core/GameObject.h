#pragma once
#include "Object.h"
#include "Transform.h"
#include "Libs/Maths.h"

class Component;

class GameObject : public Object
{

public:
	SinStr::Transform m_Transform;

protected:
	
	vector<Component*> m_Components;

public:
	GameObject();
	GameObject(SinStr::Transform SpawnTransform);
	GameObject(Math::Vector2 SpawnLocation);
	~GameObject();

	virtual void Init(Object* OwningObject) override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void BeginPlay() override;
	virtual void Update() override;
	virtual void FixedUpdate() override;
	virtual void Render(sf::RenderWindow& Renderer) override;
	virtual void OnDestroy() override;


};