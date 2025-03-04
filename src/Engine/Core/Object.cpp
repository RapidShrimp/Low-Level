#pragma once
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
void Object::FixedUpdate() {}
void Object::Render() {};
void Object::OnDestroy() {};
