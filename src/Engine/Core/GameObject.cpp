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

void GameObject::OnDestroy()
{
	
}

Vector2 GameObject::GetLocation() 
{
	return ObjectTransform.Location;
}

Vector2 GameObject::GetScale() {
	return ObjectTransform.Scale;
}

float GameObject::GetRotation() {
	return ObjectTransform.Rotation;
}