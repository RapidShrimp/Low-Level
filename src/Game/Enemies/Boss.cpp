#pragma once
#include "Boss.h"
#include "Engine/Core/Components/Collider.h"
#include "Game/Pickups/Crystal.h"

Boss::Boss()
{
	m_Health = new HealthComponent(1000);
	m_RigidBody = new Rigidbody(1);
	m_SpriteRenderer = new SpriteRenderer("Assets/SinistarSpriteSheet.png", { 298,174 }, { 299,127 }, 11, 4);
	m_SpriteRenderer->SetSpriteScale(2, 2);
	m_Collider = new Collider(false, 32.0f);
}

void Boss::Init(Object* OwningObject)
{
	Enemy::Init(OwningObject);

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

bool Boss::GiveCrystal(Crystal* InPeice)
{
	return false;
}

void Boss::Handle_EnemyDeath()
{
	//Call Event Here
}

void Boss::AI_Logic(float DeltaTime)
{

	if (!IsCreated()) { return; }

}
