#pragma once
#include "CollectorEnemy.h"
#include <iostream>
#include "Game/Pickups/Crystal.h"
#include "Game/Scenes/GameLevel.h"
#include "Game/Player/PlayerCharacter.h"
#include "Game/Misc/AsteroidManager.h"
#include "Game/Enemies/Boss.h"

CollectorEnemy::CollectorEnemy()
{
	m_Health = new HealthComponent(10);
	m_RigidBody = new Rigidbody(1, true);
	m_SpriteRenderer = new SpriteRenderer("Assets/SinistarSpriteSheet.png", { 116,16 }, { 2,82 }, 8, 1);
	m_SpriteRenderer->SetSpriteScale(2, 2);
	m_Collider = new Collider(false, 16.0f);

	m_MinimapDraw = E_MinimapType::E_Enemy;

}

void CollectorEnemy::AI_Logic(float Deltatime)
{

	//Valid Target Check
	if (m_Target == nullptr) 
	{
		Debug::Log(this, Error, "No Target");
		return; 
	}

	/*Moved to steering behaviours*/
	//Direction Towards Target
	//Math::Vector2 Dir = m_Target->m_Transform.Location - m_Transform.Location;

	//if (Dir.Length() > m_KeepDistance) {
	//	m_RigidBody->AddVelocity(Dir.Normalised() * m_MoveSpeed);
	//}
	//else 
	//{
	//	m_RigidBody->AddVelocity(Dir.Normalised() * m_MoveSpeed);

	//}



	m_RigidBody->AddVelocity(m_SteeringManager->GetDirection().Normalised());

	//Orient towards Movement Direction
	m_Transform.SetRotation(m_RigidBody->m_Velocity.Normalised().GetRadians());

	//Holding Crystal Behaviour
	if (m_HeldCrystal == nullptr) { return; }
	
	//Give Sinistar Crystal if in Range
	if ((m_Target->m_Transform.Location - m_Transform.Location).Length() < 50)
	{
		Boss* Sinistar = dynamic_cast<Boss*>(m_Target);
		if (Sinistar == nullptr) { return; }

		Sinistar->GiveCrystal(m_HeldCrystal);
		m_HeldCrystal = nullptr;
		Handle_CrystalLost(this);
	}

}

void CollectorEnemy::Handle_EnemyDeath()
{
	Enemy::Handle_EnemyDeath();
	if (m_HeldCrystal != nullptr) {
		
		m_HeldCrystal->m_Transform.Location = m_Transform.Location;
		m_HeldCrystal->Activate();
		m_HeldCrystal = nullptr;
	}
}

void CollectorEnemy::CollectCrystal(Crystal* InCrystal)
{
	if (m_HeldCrystal != nullptr) { return; }
	m_HeldCrystal = InCrystal;
	InCrystal->m_RigidBody->m_Velocity = { 0,0 };
	InCrystal->Deactivate();
	SetNewTarget(GameInstance::GetGameInstance()->GetWorld()->FindRegisteredObjectOfType<Boss>());
	Debug::Log(this, DebugNone, "Collected Crystal");
}

void CollectorEnemy::TargetCrystal(Crystal* InCrystal)
{
	if (InCrystal == nullptr) {
		return;
	}

	m_Target = InCrystal;
 	InCrystal->OnCrystalCollided += std::bind(&CollectorEnemy::Handle_CrystalLost, this, std::placeholders::_1);
}

void CollectorEnemy::Handle_CrystalLost(GameObject* Collided)
{
	m_RigidBody->Activate();
	SetNewTarget(GameInstance::GetGameInstance()->GetWorld()->GetPlayerCharacter());
}


