#pragma once
#include "Boss.h"
#include "Engine/Core/Components/Collider.h"

Boss::Boss()
{
	m_Health = new HealthComponent(100);
	m_RigidBody = new Rigidbody(1);
	m_SpriteRenderer = new SpriteRenderer("Assets/SinistarSpriteSheet.png", { 298,174 }, { 299,127 }, 11, 4);
	m_SpriteRenderer->SetSpriteScale(2, 2);
	m_Collider = new Collider(false, 32.0f);
}

void Boss::Init(Object* OwningObject)
{
	Enemy::Init(OwningObject);
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
