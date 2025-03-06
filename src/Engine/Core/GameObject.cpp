#pragma once
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include <iostream>

void GameObject::Init()
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
	//Check for Fixed Update
}

void GameObject::FixedUpdate()
{
	m_Transform.Location += Math::Vector2(1, 1);
}



void GameObject::Render(sf::RenderWindow& Renderer)
{
	sf::CircleShape Shape(240.0f);
	Shape.setFillColor(sf::Color::Green);
	Shape.setPosition(sf::Vector2f(m_Transform.Location.x,m_Transform.Location.y));
	Renderer.draw(Shape);
}

void GameObject::OnDestroy()
{

}
