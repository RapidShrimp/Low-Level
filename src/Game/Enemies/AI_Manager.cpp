#pragma once
#include "Game/Player/PlayerCharacter.h"
#include "Game/Misc/AsteroidManager.h"
#include "AI_Manager.h"

AI_Manager::AI_Manager()
{
	m_Collectors = new ObjectPooler<CollectorEnemy>(5, true);
	m_Shooters = new ObjectPooler<FiringEnemy>(3, true);


}

void AI_Manager::Init(Object* OwningObject)
{
	//Setting AI Locations
	for (GameObject* Enemy : m_Collectors->GetAllObjects()) {
		Enemy->m_Transform.Location = { Math::Random::Range(-600.0f,600.0f),Math::Random::Range(-600.0f,600.0f) };
	}
	for (GameObject* Enemys : m_Shooters->GetAllObjects()) {
		Enemys->m_Transform.Location = { Math::Random::Range(-600.0f,600.0f),Math::Random::Range(-600.0f,600.0f) };
	}


	//Collector Drone Bindings
	AsteroidManager* Manager = GameInstance::GetGameInstance()->GetWorld()->FindRegisteredObjectOfType<AsteroidManager>();
	for (Crystal* Cryst : Manager->GetPooledCrystals()->GetAllObjects()) {
		Cryst->OnCrystalAvaliable += std::bind(&AI_Manager::Handle_CrystalAppeared, this, std::placeholders::_1);
	}

	//Shooter Drone Death Bindings
	for (FiringEnemy* Shooter : m_Shooters->GetAllObjects()) 
	{
		Shooter->OnEnemyDeath += std::bind(&AI_Manager::Handle_ShooterDeath, this);
	}

}

void AI_Manager::BeginPlay()
{
	for (FiringEnemy* Shooter: m_Shooters->GetAllObjects()) {
		TargetPlayer(Shooter);
	}

	for (CollectorEnemy* Collector : m_Collectors->GetAllObjects()) {
		TargetPlayer(Collector);
	}
}

void AI_Manager::FixedUpdate(float deltaTime)
{


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

void AI_Manager::Handle_ShooterDeath()
{
 	m_Shooters->GetFreeObject()->Activate();
}
