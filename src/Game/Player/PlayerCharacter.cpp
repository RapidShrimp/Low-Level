#pragma once
#include "PlayerCharacter.h"
#include "Engine/Core/Libs/GameFunctionLib.h"
#include <iostream>

PlayerCharacter::PlayerCharacter()
{
	m_Health = new HealthComponent();
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::MovePlayer(Math::Vector2 MoveDirection)
{
	
}

void PlayerCharacter::FireWeapon()
{
	
}

void PlayerCharacter::Init(Object* OwningObject)
{
	Object::Init(OwningObject);
	RegisterComponent(m_Health,true,"Health Component");

}

void PlayerCharacter::BeginPlay()
{
	GameFucntionLib::ApplyDamage(this, 25.0f);
}

void PlayerCharacter::Update()
{
	m_Health->Update();
	//Debug::Log(this, E_LogType::Display, "Hello World");
}
