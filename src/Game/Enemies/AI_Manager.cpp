#pragma once
#include "AI_Manager.h"

AI_Manager::AI_Manager()
{

}

void AI_Manager::Init(Object* OwningObject)
{
	m_Collectors = new ObjectPooler<CollectorEnemy>(5, true);
	
	for (GameObject* Enemy : m_Collectors->GetAllObjects()) {
		Enemy->m_Transform.Location = { Math::Random::Range(-600.0f,600.0f),Math::Random::Range(-600.0f,600.0f) };
	}
}
