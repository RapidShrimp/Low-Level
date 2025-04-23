#pragma once
#include "CollectorEnemy.h"
#include <iostream>
#include "Game/Pickups/Crystal.h"
void CollectorEnemy::AI_Logic(float Deltatime)
{
	TargetPlayer();
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
		m_CurrentDelayTime = 0;
	}
	m_Transform.Location += m_RigidBody->m_Velocity * Deltatime;
	
	//Orient towards Movement Direction
	m_Transform.SetRotation(m_RigidBody->m_Velocity.Normalised().GetRadians());

}

void CollectorEnemy::Handle_EnemyDeath()
{
	Enemy::Handle_EnemyDeath();
}

void CollectorEnemy::CollectCrystal(Crystal* InCrystal)
{
	InCrystal->m_RigidBody->m_Velocity = { 0,0 };

}
