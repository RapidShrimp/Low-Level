#pragma once
#include "Engine/Core/Collider.h"

#include "Game/Enemies/BasicEnemy.h"

Enemy::Enemy()
{
	m_Health = new HealthComponent();
	m_SpriteRenderer = new SpriteRenderer("Assets/CircleTest.png", {32,32});
	m_Collider = new Collider(false, 16.0f);
}

void Enemy::Init(Object* OwningObject)
{
	Object::Init(OwningObject);
	RegisterComponent(m_Health, true, "EnemyHealth");
	RegisterComponent(m_SpriteRenderer, true, "EnemySpriteRenderer");
	RegisterComponent(m_Collider, true, "EnemyCollider");
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
