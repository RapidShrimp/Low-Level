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
	if (Context.Started) {
		Debug::Log(this, Display, "Fire Started");
	}
	else if (Context.Cancelled) 
	{
		Debug::Log(this, Display, "Fire Cancelled");
	}
}

void PlayerCharacter::Init(Object* OwningObject)
{
	Object::Init(OwningObject);
	RegisterComponent(m_Health,true,"Health Component");
	RegisterComponent(m_SpriteRenderer, true, "PlayerSpriteRenderer");

	BindableInput* FireKey = InputEventHandler::GetInstance()->CreateKeyInput(sf::Keyboard::Key::Space);
	BindableInput* UpKey = InputEventHandler::GetInstance()->CreateKeyInput(sf::Keyboard::Key::Space);

	//TODO - This 
	if (FireKey) { FireKey->OnInputUpdate += std::bind(&PlayerCharacter::FireWeapon, this, std::placeholders::_1);}

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

