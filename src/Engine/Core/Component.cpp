#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Component.h"
void Component::Init(Object* Owner)
{
	Object::Init(Owner);
	//Override Functionality Here:
	
}

void Component::OnActivate()
{
	Object::OnActivate();
}

void Component::OnDeactivate()
{
	Object::OnDeactivate();
}

void Component::BeginPlay()
{
	Object::BeginPlay();
}

void Component::Update()
{
	Object::Update();
}

void Component::FixedUpdate()
{
	Object::FixedUpdate();
}

void Component::Render(sf::RenderWindow& Renderer)
{
	Object::Render(Renderer);
}

void Component::OnDestroy()
{
	Object::OnDestroy();
}
