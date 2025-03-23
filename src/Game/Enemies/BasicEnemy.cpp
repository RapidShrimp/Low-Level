#pragma once
#include "Engine/Core/Components/Collider.h"

#include "Game/Enemies/BasicEnemy.h"

Enemy::Enemy()
{
	m_Health = new HealthComponent();
	m_SpriteRenderer = new SpriteRenderer("Assets/SinistarSpriteSheet.png", {116,16}, {2,82},8,1);
	m_SpriteRenderer->SetSpriteScale(2, 2);
	m_Collider = new Collider(false, 16.0f);
}

void Enemy::Init(Object* OwningObject)
{
	Object::Init(OwningObject);
	RegisterComponent(m_Health, true, "EnemyHealth");
	RegisterComponent(m_SpriteRenderer, true, "EnemySpriteRenderer");
	RegisterComponent(m_Collider, true, "EnemyCollider");

	m_Health->OnDeath += std::bind(&Enemy::Handle_EnemyDeath, this);
}

void Enemy::BeginPlay()
{
}

void Enemy::Update()
{
	GameObject::Update();
}

void Enemy::FixedUpdate(float DeltaTime)
{
	GameObject::FixedUpdate(DeltaTime);
}

void Enemy::Handle_EnemyDeath()
{
	GameObject::OnDestroy();
}
