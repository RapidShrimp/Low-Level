#pragma once
#include "Transform.h"
#include "Engine/Core/Components/Collider.h"
#include "GameObject.h"
#include <iostream>


GameObject::GameObject()
{
	m_Transform = SinStr::Transform();
}

GameObject::GameObject(SinStr::Transform SpawnTransform)
{
	m_Transform = SpawnTransform;
}

GameObject::GameObject(Math::Vector2 SpawnLocation)
{
	m_Transform.Location = SpawnLocation;
}

GameObject::~GameObject()
{
}

void GameObject::RegisterComponent(Component* InRegisterComponent, SinStr::Transform(StartTransform), bool Activate, std::string DisplayName)
{
	if (std::find(m_Components.begin(), m_Components.end(), InRegisterComponent) != m_Components.end())
	{
		cout << "Warning: Component Already Registered, avoid calling Register Component more than once" << endl;
		return;
	}
	m_Components.push_back(InRegisterComponent);
	InRegisterComponent->GetLocalTransform() = StartTransform;
	InRegisterComponent->SetName(DisplayName);
	InRegisterComponent->Init(this);
	Collider* ColliderCheck = dynamic_cast<Collider*>(InRegisterComponent);
	if (ColliderCheck != nullptr) { m_Colliders.push_back(ColliderCheck); }
	InRegisterComponent->BeginPlay();
	if (Activate) { InRegisterComponent->Activate(); }
}

void GameObject::RegisterComponent(Component* InRegisterComponent, Math::Vector2(StartLocation), bool Activate, std::string DisplayName)
{
	RegisterComponent(InRegisterComponent, SinStr::Transform(StartLocation, Math::Vector2(1, 1), 0), Activate, DisplayName);
}

void GameObject::RegisterComponent(Component* InRegisterComponent, bool Activate, std::string DisplayName)
{
	RegisterComponent(InRegisterComponent, SinStr::Transform({ 0,0 }), Activate, DisplayName);
}

void GameObject::Init(Object* OwningObject)
{
	//Create and Register All Components;
}

void GameObject::OnActivate()
{
	/*
	* EnableComponents
	* EnableRenderer
	*/ 
}

void GameObject::OnDeactivate()
{
	/*
	* DisableComponents
	* DisableRenderer
	*/
}

void GameObject::BeginPlay()
{
	//Override Functionality Here:
}

void GameObject::Update()
{
	//Override Functionality Here:
	for (int ComponentIndex = 0; ComponentIndex < m_Components.size(); ComponentIndex++) 
	{
		m_Components[ComponentIndex]->Update();
	}
}

void GameObject::FixedUpdate(float deltaTime)
{
	for (int ComponentIndex = 0; ComponentIndex < m_Components.size(); ComponentIndex++)
	{
		m_Components[ComponentIndex]->FixedUpdate(deltaTime);
	}
}

void GameObject::Render(sf::RenderWindow& Renderer)
{
	//TODO - Set a default sprite to render here
	for (int Comp = 0; Comp < m_Components.size(); Comp++) 
	{
		if (m_Components[Comp] == nullptr) { continue; }
		m_Components[Comp]->Render(Renderer);
	}

	sf::CircleShape circle;
	circle.setRadius(2);
	circle.setPosition(sf::Vector2f(m_Transform.Location.x-2,m_Transform.Location.y-2));
	Renderer.draw(circle);

}

void GameObject::OnDestroy()
{
	//Loop through components and call destroy
	for (int i = 0; i < m_Components.size(); i++) {
		m_Components[i]->OnDestroy();
	}
	m_Components.clear();
}