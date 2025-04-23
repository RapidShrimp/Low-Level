#pragma once
#include "Boss.h"
#include "Engine/Core/Components/Collider.h"
#include "Game/Pickups/Crystal.h"
#include "Engine/Core/Libs/GameFunctionLib.h"

Boss::Boss()
{
	m_Health = new HealthComponent(100);
	m_RigidBody = new Rigidbody(1);
	m_SpriteRenderer = new SpriteRenderer("Assets/SinistarSpriteSheet.png", { 298,174 }, { 299,127 }, 11, 4);
	m_SpriteRenderer->SetSpriteScale(2, 2);
	m_Collider = new Collider(false, 32.0f);
	m_Pieces = 9;
}

void Boss::Init(Object* OwningObject)
{
	Enemy::Init(OwningObject);
	m_Health->OnDamageTaken += std::bind(&Boss::Handle_TakeDamage, this, std::placeholders::_1);
	//m_Collider->OnCollisionEvent += std::bind(&Boss::Handle_CollisionEvent, )
}

void Boss::BeginPlay()
{
	//m_SpriteRenderer->StartAnimation();
	m_SpriteRenderer->SetSprite(0, 0);

}

void Boss::Update()
{
}

void Boss::FixedUpdate(float DeltaTime)
{
	GameObject::FixedUpdate(DeltaTime);
}

void Boss::GiveCrystal(Crystal* InPeice)
{
	Debug::Log(this, Display, "Boss Recieved Crystal" + std::to_string(m_Health->GetHealthPercent()));

	
	InPeice->Deactivate();
	m_Pieces++;
	m_Health->SetHealth(m_Pieces * 100);
	if (m_Pieces == 10) {
		m_Created = true;
		Debug::Log(this, Error, ".....SINISTAR IS ACTIVE.....");

	}
}

void Boss::Handle_TakeDamage(float Damage)
{
	Debug::Log(this, Display, "Boss Took Damage" + std::to_string(m_Health->GetHealthPercent()));
	
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

}
