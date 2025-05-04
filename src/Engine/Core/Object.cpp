#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Object.h"


Object::Object() {}
Object::~Object() 
{
	m_Owner = nullptr;
};

void Object::Init(Object* OwningObject) { m_Owner = OwningObject; }
void Object::Activate()
{
	if (isActive) { return; }
	isActive = true;
	OnActivate();
}
void Object::Deactivate()
{
	if (!isActive) { return; }
	isActive = false;
	OnDeactivate();
}
void Object::OnActivate() {};
void Object::OnDeactivate() {};
void Object::BeginPlay() {};
void Object::Update() {};
void Object::FixedUpdate(float deltaTime) {};
void Object::Render(sf::RenderWindow& Renderer) {};
void Object::OnDestroy() {};
