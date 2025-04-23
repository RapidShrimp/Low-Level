#pragma once
#include "CollectorEnemy.h"
#include <iostream>
#include "Game/Pickups/Crystal.h"
#include "Game/Scenes/GameLevel.h"
#include "Game/Misc/AsteroidManager.h"
void CollectorEnemy::AI_Logic(float Deltatime)
{

	if (m_Target == nullptr) { return; }
	
	if (m_HeldCrystal == nullptr) 
	{
		m_KeepDistance = 0;
		//TargetSinistar();
	}



	m_KeepDistance = 25;
	if (m_Target == nullptr) { return; }


	//if (m_CurrentDelayTime <= m_SweepDelayTime) {
	//	m_CurrentDelayTime += Deltatime;
	//	m_RigidBody->AddVelocity(m_RigidBody->m_Velocity.Normalised()*m_MoveSpeed);
	//	return;
	//}
	

	//Movement
 	Math::Vector2 Dir = m_Target->m_Transform.Location - m_Transform.Location;

	if (Dir.Length() > m_KeepDistance) {
		m_RigidBody->AddVelocity(Dir.Normalised() * m_MoveSpeed);
	}
	else 
	{
		m_RigidBody->AddVelocity(Dir.Normalised() * -m_MoveSpeed);
	}
	m_Transform.Location += m_RigidBody->m_Velocity * Deltatime;
	
	//Orient towards Movement Direction
	m_Transform.SetRotation(m_RigidBody->m_Velocity.Normalised().GetRadians());

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
	Debug::Log(this, Confirm, "Collected Crystal");
}

void CollectorEnemy::TargetCrystal(Crystal* InCrystal)
{
	if (InCrystal == nullptr) {
		return;
	}
	m_Target = InCrystal;
}

