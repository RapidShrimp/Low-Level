#pragma once
#include "Object.h"
#include "Transform.h"
#include "Libs/Maths.h"
#include "Engine/Core/Events/Event.h"

class Component;
class Collider;

class GameObject : public Object
{
public:
	/*
	OnTakeDamage
	Float - Incoming Health Change
	GameObject - Causing GameObject
	*/
	SinStr::Event<float, GameObject*> OnTakeDamage;
	SinStr::Transform m_Transform;

protected:
	vector<Component*> m_Components;
	vector<Collider*> m_Colliders;

public:
	GameObject();
	GameObject(SinStr::Transform SpawnTransform);
	GameObject(Math::Vector2 SpawnLocation);
	~GameObject();

	void RegisterComponent(Component* InRegisterComponent, SinStr::Transform(StartTransform) = SinStr::Transform(), bool Activate = true, std::string DisplayName = "");
	void RegisterComponent(Component* InRegisterComponent, Math::Vector2(StartLocation) = Math::Vector2(0, 0),bool Activate = true, std::string DisplayName = "");
	void RegisterComponent(Component* InRegisterComponent, bool Activate = true, std::string DisplayName = "");

	virtual void Init(Object* OwningObject) override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void BeginPlay() override;
	virtual void Update() override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Render(sf::RenderWindow& Renderer) override;
	virtual void OnDestroy() override;
	virtual Collider* GetCollider(int ColliderIndex = 0) 
	{ 
		if (m_Colliders.size() == 0) { return nullptr; }
		return m_Colliders[ColliderIndex]; }

};