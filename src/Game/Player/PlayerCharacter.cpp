#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter()
{
	m_Health = new HealthComponent();
	m_SpriteRenderer = new SpriteRenderer("Assets/SinistarSprites.jpg");
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::MovePlayer(Math::Vector2 MoveDirection)
{
	
}

void PlayerCharacter::FireWeapon(CallbackContext Context)
{
	
}

void PlayerCharacter::Init(Object* OwningObject)
{
	Object::Init(OwningObject);
	RegisterComponent(m_Health,true,"Health Component");
	RegisterComponent(m_SpriteRenderer, true, "PlayerSpriteRenderer");

	BindableInput* UpKey = InputEventHandler::GetInstance()->CreateKeyInput(sf::Keyboard::Key::W);
	//TODO - This Errors
	UpKey->OnInputUpdate += std::bind(&PlayerCharacter::FireWeapon, this, std::placeholders::_1);
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

