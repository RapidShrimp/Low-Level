#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Object.h"


Object::Object() {}
Object::~Object() 
{
	m_Owner = nullptr;
};

void Object::Init(Object* OwningObject) { m_Owner = OwningObject; };
void Object::OnActivate() {};
void Object::OnDeactivate() {};
void Object::BeginPlay() {};
void Object::Update() {};
void Object::FixedUpdate() {};
void Object::Render(sf::RenderWindow& Renderer) {};
void Object::OnDestroy() {};
