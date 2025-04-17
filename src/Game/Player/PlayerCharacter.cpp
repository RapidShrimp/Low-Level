#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Engine/Core/GameInstance.h"
#include "Engine/Core/ObjectPooler.h"
#include <Game/Scenes/GameLevel.h>
#include "Game/Projectiles/Projectile.h"
#include "Game/Projectiles/Sinibomb.h"
#include "Game/UI/UI_HUD.h"
#include "PlayerCharacter.h"


PlayerCharacter::PlayerCharacter()
{
	m_Health = new HealthComponent();
	m_SpriteRenderer = new SpriteRenderer("Assets/SinistarSpriteSheet.png", { 106,14 }, { 2,42 }, 8, 1);
	m_SpriteRenderer->SetSpriteScale(3, 3);

	m_Collider = new Collider(false, { 32,32 });
	m_RigidBody = new Rigidbody(0.5f);

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

		GameLevel* CurrGameScene = dynamic_cast<GameLevel*>(GameInstance::GetGameInstance()->GetWorld());
		if (CurrGameScene == nullptr) { return; }

		ObjectPooler<Projectile>* BulletObejctPooler = CurrGameScene->m_BulletPooler;
		Projectile* Bullet = BulletObejctPooler->GetFreeObject();
		Bullet->m_Transform = m_Transform;
		Bullet->Activate();

		//Get Mouse Direction 
		sf::Vector2f MousePos =  InputEventHandler::GetInstance()->GetMousePosition();
		Math::Vector2 Dir = Math::Vector2(MousePos.x, MousePos.y) - m_Transform.Location;
		Math::Vector2::Normalise(Dir);
		Bullet->OnFired(this,Dir);
	}
}

void PlayerCharacter::FireSinibomb(CallbackContext Context)
{
	if (Context.Started) {

		if (m_SinibombsHeld == 0) { return; }

		GameLevel* CurrGameScene = dynamic_cast<GameLevel*>(GameInstance::GetGameInstance()->GetWorld());
		if (CurrGameScene == nullptr) { return; }

		
		ObjectPooler<Sinibomb>* BombObejctPooler = CurrGameScene->m_BombPooler;
		if (BombObejctPooler == nullptr) 
		{ 
			Debug::Log(this, Error, "No Sinibomb Object Pooler in scene");
			return; 
		}
		Sinibomb* Bomb = BombObejctPooler->GetFreeObject();
		Bomb->m_Transform = m_Transform;
		Bomb->Activate();

		//Get Mouse Direction 
		sf::Vector2f MousePos = InputEventHandler::GetInstance()->GetMousePosition();
		Math::Vector2 Dir = Math::Vector2(MousePos.x, MousePos.y) - m_Transform.Location;
		Math::Vector2::Normalise(Dir);
		m_SinibombsHeld--;
		Bomb->OnFired(this, Dir);
	}
}

void PlayerCharacter::CollectSinibomb()
{
	if (m_SinibombsHeld == 20) { return; }
	m_SinibombsHeld++; 
	Debug::Log(this, Display, "Sinibomb Collected:" + to_string(m_SinibombsHeld));
	OnSinibombUpdated(m_SinibombsHeld);

}

void PlayerCharacter::AddScore(int AddedScore)
{
	Score += AddedScore;
	OnScoreUpdated(Score);
}

void PlayerCharacter::RemoveScore(int RemovedScore)
{
	Score += RemovedScore;
	OnScoreUpdated(Score);
}

void PlayerCharacter::OnCollisionEventCallback(Collider* OtherCollider, E_CollisionEvent Response)
{
	//Debug::Log(this, Display, "Collision Event Callback");

}

void PlayerCharacter::Init(Object* OwningObject)
{
	Object::Init(OwningObject);
	RegisterComponent(m_Health,true,"Health Component");
	RegisterComponent(m_SpriteRenderer, true, "SpriteRenderer");
	RegisterComponent(m_Collider, Math::Vector2(-10, -10), true, "Circle Collider");
	RegisterComponent(m_RigidBody, true, "Rigid Body");

	m_SpriteRenderer->GetLocalTransform().SetRotation(1.5708);
	m_Collider->OnCollisionEvent += std::bind(&PlayerCharacter::OnCollisionEventCallback, this, std::placeholders::_1, std::placeholders::_2);

	AxisActionMapping MoveKeys = AxisActionMapping(sf::Keyboard::Key::W, sf::Keyboard::Key::Unknown, sf::Keyboard::Key::Unknown, sf::Keyboard::Key::Unknown);
	AxisInput* MoveInput = InputEventHandler::GetInstance()->CreateAxisInput(MoveKeys);
	BindableInput* MoveKey = InputEventHandler::GetInstance()->CreateKeyInput(sf::Keyboard::Key::W);
	BindableInput* FireKey = InputEventHandler::GetInstance()->CreateKeyInput(sf::Keyboard::Key::Space);
	BindableInput* Sinibomb = InputEventHandler::GetInstance()->CreateKeyInput(sf::Keyboard::Key::LShift);

	MouseInput* MouseInputs = InputEventHandler::GetInstance()->CreateMouseInput();
	if (FireKey) { FireKey->OnInputUpdate += std::bind(&PlayerCharacter::FireWeapon, this, std::placeholders::_1);}
	if (Sinibomb) { Sinibomb->OnInputUpdate += std::bind(&PlayerCharacter::FireSinibomb, this, std::placeholders::_1); }

	if (MoveInput) { MoveInput->OnAxisInputUpdate += std::bind(&PlayerCharacter::MovePlayer, this, std::placeholders::_1, std::placeholders::_2); }

	GameInstance::GetGameInstance()->GetWorld()->SpawnUIElement(new UI_HUD(*this) , { 0,0 }, true);
}

void PlayerCharacter::BeginPlay()
{
}

void PlayerCharacter::Update()
{
	GameObject::Update();
}

void PlayerCharacter::Render(sf::RenderWindow& Renderer)
{
	GameObject::Render(Renderer);
}

void PlayerCharacter::FixedUpdate(float DeltaTime)
{
	GameObject::FixedUpdate(DeltaTime);

	sf::Vector2f MousePos = InputEventHandler::GetInstance()->GetMousePosition();
	Math::Vector2 Dir = Math::Vector2(MousePos.x, MousePos.y) - m_Transform.Location;

	if (MoveDirection != Math::Vector2::Zero() && Dir.Length() > 0.1f) //P  revent NaN Error 
	{
		m_RigidBody->AddVelocity(Math::Vector2::GetDirectionFromRadians(m_Transform.Rotation)*m_MoveSpeed);
	}


	
	m_Transform.SetRotation(Dir.Normalised().GetRadians());
}