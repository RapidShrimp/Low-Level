#pragma once
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include <iostream>


GameObject::GameObject()
{
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
}

void GameObject::FixedUpdate()
{
	//Override Functionality Here:
}

void GameObject::Render(sf::RenderWindow& Renderer)
{
	//TODO - Set a default sprite to render here
	sf::CircleShape Shape(240.0f);
	Shape.setFillColor(sf::Color::Green);
	Shape.setPosition(sf::Vector2f(m_Transform.Location.x,m_Transform.Location.y));
	Renderer.draw(Shape);
}

void GameObject::OnDestroy()
{
	//Loop through components and call destroy
}
