#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter()
{
	m_Health = new HealthComponent();
	m_SpriteRenderer = new SpriteRenderer();
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
	RegisterComponent(m_SpriteRenderer, true, "PlayerSpriteRenderer");
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
