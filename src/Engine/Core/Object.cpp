#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Object.h"


Object::Object() {}
Object::~Object() 
{

	if (m_Owner == nullptr) {
		return;
	}
	delete m_Owner;
	m_Owner = nullptr;
};

void Object::Init(Object* OwningObject) { OwningObject = OwningObject; };
void Object::OnActivate() {};
void Object::OnDeactivate() {};
void Object::BeginPlay() {};
void Object::Update() {};
void Object::FixedUpdate() {};
void Object::Render(sf::RenderWindow& Renderer) {};
void Object::OnDestroy() {};

const Object* Object::GetOwner()
{
	return m_Owner;
}
;
