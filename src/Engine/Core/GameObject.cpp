#pragma once
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"

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
}

void GameObject::FixedUpdate()
{
}



void GameObject::Render(sf::RenderWindow& Renderer)
{
	sf::CircleShape Shape(240.0f);
	Shape.setFillColor(sf::Color::Green);
	Renderer.draw(Shape);
}

void GameObject::OnDestroy()
{

}
