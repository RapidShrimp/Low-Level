#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Object.h"


Object::Object() {}
Object::~Object() 
{

	if (OwningObject == nullptr) {
		return;
	}
	delete OwningObject;
	OwningObject = nullptr;
};

void Object::Init() {};
void Object::OnActivate() {};
void Object::OnDeactivate() {};
void Object::BeginPlay() {};
void Object::Update() {};
void Object::FixedUpdate() {};
void Object::Render(sf::RenderWindow& Renderer) {};
void Object::OnDestroy() {}

const Object* Object::GetOwner()
{
	return OwningObject;
}
;
