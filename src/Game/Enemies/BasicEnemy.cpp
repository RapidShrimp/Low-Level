#pragma once
#include "Engine/Core/Components/Collider.h"
#include "Engine/Core/GameInstance.h"
#include "Game/Enemies/BasicEnemy.h"
#include "Game/Player/PlayerCharacter.h"
#include <Engine/Core/Libs/GameFunctionLib.h>

Enemy::Enemy()
{
	m_Health = new HealthComponent(10);
	m_RigidBody = new Rigidbody(1,true);
	m_SpriteRenderer = new SpriteRenderer("Assets/SinistarSpriteSheet.png", {116,16}, {2,82},8,1);
	m_SpriteRenderer->SetSpriteScale(2, 2);
	m_Collider = new Collider(false, 16.0f);

	m_MinimapDraw = E_MinimapType::E_Enemy;
}

void Enemy::Init(Object* OwningObject)
{
	Object::Init(OwningObject);
	RegisterComponent(m_Health, true, "EnemyHealth");
	RegisterComponent(m_SpriteRenderer, true, "EnemySpriteRenderer");
	RegisterComponent(m_Collider, true, "EnemyCollider");
	RegisterComponent(m_RigidBody,true,"Rigid Body");

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
	AI_Logic(DeltaTime);
}

void Enemy::SetNewTarget(GameObject* NewTarget)
{
	if (NewTarget == nullptr) { return; }
	m_Target = NewTarget;
}

void Enemy::AI_Logic(float DeltaTime)
{
	//Override Here
}



void Enemy::Handle_EnemyDeath()
{
	Deactivate();
}
