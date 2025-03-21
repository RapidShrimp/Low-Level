#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Engine/Core/Components/Collider.h"

#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter()
{
	m_Health = new HealthComponent();
	m_SpriteRenderer = new SpriteRenderer("Assets/SinistarSpriteSheet.png", { 106,14 }, {2,42},8,1);
	m_SpriteRenderer->GetLocalTransform().SetScale(5, 5);
	m_Collider = new Collider(false, {32,32});
	MoveDirection = Math::Vector2::Zero();
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::MovePlayer(CallbackContext Context, Math::Vector2 MoveVector)
{
	if (Context.Triggering) 
	{
		MoveDirection = MoveVector;
	}
	if (Context.Cancelled) 
	{
		MoveDirection = Math::Vector2::Zero();
	}

}

void PlayerCharacter::FireWeapon(CallbackContext Context)
{
	if (Context.Started) {
		Debug::Log(this, Display, "Fire Started");
		//m_SpriteRenderer->SetSprite(m_SpriteRenderer->GetSpriteIndexes().x + 1, m_SpriteRenderer->GetSpriteIndexes().y);
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
	RegisterComponent(m_Collider, true, "PlayerCircleCollider");

	AxisActionMapping MoveKeys = AxisActionMapping(sf::Keyboard::Key::W, sf::Keyboard::Key::S, sf::Keyboard::Key::A, sf::Keyboard::Key::D);
	AxisInput* MoveInput = InputEventHandler::GetInstance()->CreateAxisInput(MoveKeys);
	BindableInput* FireKey = InputEventHandler::GetInstance()->CreateKeyInput(sf::Keyboard::Key::Space);

	//TODO - This 
	if (FireKey) { FireKey->OnInputUpdate += std::bind(&PlayerCharacter::FireWeapon, this, std::placeholders::_1);}
	if (MoveInput) { MoveInput->OnAxisInputUpdate += std::bind(&PlayerCharacter::MovePlayer, this, std::placeholders::_1, std::placeholders::_2); }

}

void PlayerCharacter::BeginPlay()
{
	GameFucntionLib::ApplyDamage(this, 25.0f);
}

void PlayerCharacter::Update()
{
	GameObject::Update();
	//Debug::Log(this, E_LogType::Display, "Hello World");
}

void PlayerCharacter::FixedUpdate(float DeltaTime)
{
	GameObject::FixedUpdate(DeltaTime);
	m_Transform.Location += MoveDirection * m_MoveSpeed;
}
