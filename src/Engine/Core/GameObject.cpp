#pragma once
#include "Engine/Core/Components/Component.h"
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

void GameObject::RegisterComponent(Component* RegisterComponent, bool Activate, std::string DisplayName, SinStr::Transform StartTransform)
{
	if (std::find(m_Components.begin(), m_Components.end(), RegisterComponent) != m_Components.end())
	{
		cout << "Warning: Component Already Registered, avoid calling Register Component more than once" << endl;
		return;
	}
	m_Components.push_back(RegisterComponent);
	RegisterComponent->GetLocalTransform() = StartTransform;
	RegisterComponent->SetName(DisplayName);
	RegisterComponent->Init(this);
	Collider* ColliderCheck = dynamic_cast<Collider*>(RegisterComponent);
	if (ColliderCheck != nullptr) { m_Colliders.push_back(ColliderCheck);}
	RegisterComponent->BeginPlay();
	if (Activate) { RegisterComponent->Activate(); }
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

}

void GameObject::OnDestroy()
{
	//Loop through components and call destroy
	for (int i = 0; i < m_Components.size(); i++) {
		m_Components[i]->OnDestroy();
	}
	m_Components.clear();
}