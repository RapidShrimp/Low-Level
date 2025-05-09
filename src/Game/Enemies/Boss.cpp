#pragma once
#include "Boss.h"
#include "Engine/Core/Components/Collider.h"
#include "Game/Pickups/Crystal.h"
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Game/Player/PlayerCharacter.h"
#include <Engine/Core/AudioManager.h>

Boss::Boss()
{
	m_MinimapDraw = E_SINISTAR;

	m_Health = new HealthComponent(90);
	m_RigidBody = new Rigidbody(1);
	m_SpriteRenderer = new SpriteRenderer("Assets/SinistarSpriteSheet.png", { 297,126 }, { 298,174 }, 9, 3);
	m_SteeringManager = new SteeringManager();
	m_SpriteRenderer->SetSpriteScale(2, 2);
	m_Collider = new Collider(false, 32.0f);

	m_AttackTimer = new Timer(5, true);

	
	m_MovePause = new Timer(3.4f, false);
	
	m_Pieces = 8;
}

void Boss::Init(Object* OwningObject)
{
	Enemy::Init(OwningObject);
	m_Health->OnDamageTaken.AddListener(this,std::bind(& Boss::Handle_TakeDamage, this, std::placeholders::_1));
	m_AttackTimer->OnTimerCompleted.AddListener(this,std::bind(&Boss::ChargePlayer, this));
	m_MovePause->OnTimerCompleted.AddListener(this,std::bind(&Boss::StopMoving, this));
	//m_Collider->OnCollisionEvent.AddListener(this,std::bind(&Boss::Handle_CollisionEvent, )
}

void Boss::BeginPlay()
{
	//m_SpriteRenderer->StartAnimation();
	m_SpriteRenderer->SetSprite(0, 0);
	//m_SpriteRenderer->StartAnimation();

	GiveCrystal(new Crystal());
}

void Boss::Update()
{
}

void Boss::FixedUpdate(float DeltaTime)
{
	GameObject::FixedUpdate(DeltaTime);
	AI_Logic(DeltaTime);
}

void Boss::OnDestroy()
{
	Enemy::OnDestroy();
}

void Boss::Render(sf::RenderWindow& Renderer)
{
	GameObject::Render(Renderer);

}

void Boss::GiveCrystal(Crystal* InPeice)
{
	Debug::Log(this, Display, "Boss Recieved Crystal: " + std::to_string((int)m_Health->GetHealthPercent()));

	InPeice->Deactivate();
	if (m_Created) { return; }
	m_Pieces++;
	m_Health->SetHealth(m_Pieces * 100);
	if (m_Pieces == 10 && m_Created == false) {
		m_Created = true;
		m_Collider->SetRadius(50.0f);
		m_AttackTimer->StartTimer();
		Debug::Log(this, Error, ".....SINISTAR IS ACTIVE.....");
		AudioManger::PlaySound("Beware_i_Live.mp3");
	}
}

void Boss::ChargePlayer()
{
	PlayerCharacter* Player = GameInstance::GetGameInstance()->GetWorld()->GetPlayerCharacter();

	m_AttackDirection = Player->m_Transform.Location - m_Transform.Location;

	/*Rigidbody* PlayerRB = Player->FindComponentOfType<Rigidbody>();
	m_AttackDirection = m_AttackDirection + PlayerRB->m_Velocity * 2;*/
	
	/*if (PlayerRB == nullptr) { return; }
	m_AttackDirection = Player->m_Transform.Location + (PlayerRB->m_Velocity * PlayerRB->m_MaxSpeed * m_AttackDirection.Length());*/

	m_MoveSpeed = 1.2f;
	m_MovePause->ResetTimer();
  	m_MovePause->StartTimer();
}

void Boss::StopMoving()
{
	m_MoveSpeed = 0;
}


void Boss::Handle_TakeDamage(float Damage)
{
	Debug::Log(this, Display, "Boss Took Damage");
	m_Pieces = (int) m_Health->GetCurrentHealth() / 100;
	//TODO - Update Sprite Composition
}

void Boss::Handle_EnemyDeath()
{
	if (m_Created == true)
	{

		Debug::Log(this, Error, "Boss Dead");
	}
	else {
		Debug::Log(this, Warning, "Boss Hasn't Been Created Yet");

	}

}

void Boss::AI_Logic(float DeltaTime)
{
	if (!IsCreated()) { return; }

	m_Transform.Location += m_AttackDirection.Normalised() * m_MoveSpeed;
}
