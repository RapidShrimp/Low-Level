#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Engine/Core/GameInstance.h"
#include "Engine/Core/ObjectPooler.h"
#include "Game/Projectiles/Projectile.h"
#include "Game/Scenes/GameLevel.h"
#include "FiringEnemy.h"

FiringEnemy::FiringEnemy()
{
	m_Health = new HealthComponent(10);
	m_RigidBody = new Rigidbody(1, true);
	m_SpriteRenderer = new SpriteRenderer("Assets/SinistarSpriteSheet.png",{ 15,15 }, { 37,101 });
	m_SpriteRenderer->SetSpriteScale(2, 2);
	m_SteeringManager = new SteeringManager();
	m_Collider = new Collider(false, 16.0f);
	m_MinimapDraw = E_MinimapType::E_Enemy;
	m_MoveSpeed = 0.5f;
	m_KeepDistance = 200;

	m_FiringTimer = new Timer(1.5f, true, 0.4);

}

void FiringEnemy::Init(Object* OwningObject) 
{
	Enemy::Init(OwningObject);
	m_SteeringManager->AddBehaviour(new Separation(300),5);

	m_FiringTimer->OnTimerCompleted += std::bind(&FiringEnemy::FireWeapon, this);
 	m_FiringTimer->StartTimer();
}

void FiringEnemy::BeginPlay()
{
	m_RigidBody->Deactivate();
}

void FiringEnemy::OnActivate()
{
	GameObject::OnActivate();
	m_Transform.Location = { 0,0};
}

void FiringEnemy::AI_Logic(float DeltaTime)
{

 	if (m_Target == nullptr)
	{
		Debug::Log(this, Error, "No Target Firing");
		return;
	}

	Math::Vector2 Dir = m_Target->m_Transform.Location - m_Transform.Location;
	if (Dir.Length() > m_KeepDistance) {
		m_Transform.Location += Dir.Normalised() * m_MoveSpeed;
	}
	


	m_Transform.SetRotation(Dir.Normalised().GetRadians());
	m_Transform.Location += m_SteeringManager->GetDirection();


	//TODO - Get Velocity and fire
	//Rigidbody* rb = m_Target->FindComponentOfType<Rigidbody>();
	//m_Target->m_Transform.Location + rb->m_Velocity


}

void FiringEnemy::Handle_EnemyDeath()
{
	Enemy::Handle_EnemyDeath();
}

void FiringEnemy::FireWeapon() 
{
	if (!isActive) { return; }
	Math::Vector2 Dir = m_Target->m_Transform.Location - m_Transform.Location;
	if (Dir.Length() > 400) 
	{
		Debug::Log(this, Display, "Started Firing");
		return;
	}
	GameLevel* CurrGameScene = dynamic_cast<GameLevel*>(GameInstance::GetGameInstance()->GetWorld());
	if (CurrGameScene == nullptr) { return; }

	ObjectPooler<Projectile>* BulletObejctPooler = CurrGameScene->m_BulletPooler;
	Projectile* Bullet = BulletObejctPooler->GetFreeObject();
	Bullet->m_Transform = m_Transform;
	Bullet->Activate();

	//Get Mouse Direction 
	Math::Vector2::Normalise(Dir);
	Bullet->OnFired(this, Dir);
}