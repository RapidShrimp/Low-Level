#pragma once
#include "Game/Player/PlayerCharacter.h"
#include "Game/Misc/AsteroidManager.h"
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

	AsteroidManager* Manager = GameInstance::GetGameInstance()->GetWorld()->FindRegisteredObjectOfType<AsteroidManager>();
	for (Crystal* Cryst : Manager->GetPooledCrystals()->GetAllObjects()) {
		Cryst->OnCrystalAvaliable += std::bind(&AI_Manager::Handle_CrystalAppeared, this, std::placeholders::_1);
	}
	for (CollectorEnemy* Collector : m_Collectors->GetAllObjects()) {
		TargetPlayer(Collector);
	}
}

void AI_Manager::FixedUpdate(float deltaTime)
{

	//Collectors Logic

	
}

void AI_Manager::Handle_CrystalAppeared(GameObject* InCrystal)
{
	Debug::Log(this, Confirm, "Crystal Appeared");
	CollectorEnemy* rand =  m_Collectors->GetAllObjects()[Math::Random::Range(0, m_Collectors->GetAllObjects().size())];
 	rand->TargetCrystal(dynamic_cast<Crystal*>(InCrystal));

}

void AI_Manager::TargetPlayer(Enemy* EnemyToTarget)
{
	GameObject* Player = dynamic_cast<GameObject*>(GameInstance::GetGameInstance()->GetWorld()->GetPlayerCharacter());
	if (Player != nullptr) 
	{
		EnemyToTarget->SetNewTarget(Player);
	}
}

