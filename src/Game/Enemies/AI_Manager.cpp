#pragma once
#include "Game/Player/PlayerCharacter.h"
#include "Game/Misc/AsteroidManager.h"
#include "Game/Enemies/CollectorEnemy.h"
#include "AI_Manager.h"

AI_Manager::AI_Manager()
{
	m_Collectors = new ObjectPooler<CollectorEnemy>(5, true);
	m_Shooters = new ObjectPooler<FiringEnemy>(3, true);
}

void AI_Manager::Init(Object* OwningObject)
{
	//Collectors
	for (CollectorEnemy* Enemy : m_Collectors->GetAllObjects()) {
		Enemy->m_Transform.Location = { Math::Random::Range(-600.0f,600.0f),Math::Random::Range(-600.0f,600.0f) };
		HealthComponent* EnemyHealth = Enemy->FindComponentOfType<HealthComponent>();
		if (EnemyHealth == nullptr) { continue; }
		EnemyHealth->OnDeath.AddListener(this,std::bind(& AI_Manager::Handle_CollectorDead, this));

		SteeringManager* Steering = Enemy->GetSteering();
		if (Steering == nullptr) { continue; }

		//Assign Separation Targets

		

		Separation* SeparationBehaviour = Steering->GetBehaviour<Separation>();
		std::vector<CollectorEnemy*> Enemies = m_Collectors->GetAllObjects();
		SeparationBehaviour->SetTargets(m_Collectors->GetObjectsAs<GameObject>());
	}

	//Shooter Drone Death Bindings
	for (FiringEnemy* Shooter : m_Shooters->GetAllObjects()) 
	{
		Shooter->m_Transform.Location = { Math::Random::Range(-600.0f,600.0f),Math::Random::Range(-600.0f,600.0f) };
		Shooter->OnEnemyDeath.AddListener(this,std::bind(&AI_Manager::Handle_ShooterDeath, this));

		//Assign Separation Targets

		SteeringManager* Steering = Shooter->GetSteering();
		if (Steering == nullptr) { continue; }

		Separation* SeparationBehaviour = Steering->GetBehaviour<Separation>();
		std::vector<FiringEnemy*> Enemies = m_Shooters->GetAllObjects();
		SeparationBehaviour->SetTargets(m_Shooters->GetObjectsAs<GameObject>());
	}

	//Crystal Bindings
	AsteroidManager* Manager = GameInstance::GetGameInstance()->GetWorld()->FindRegisteredObjectOfType<AsteroidManager>();
	for (Crystal* Cryst : Manager->GetPooledCrystals()->GetAllObjects()) {
		Cryst->OnCrystalAvaliable.AddListener(this,std::bind(&AI_Manager::Handle_CrystalAppeared, this, std::placeholders::_1));
	}


}

void AI_Manager::BeginPlay()
{
	for (FiringEnemy* Shooter: m_Shooters->GetAllObjects()) {
		TargetPlayer(Shooter);
	}

	for (CollectorEnemy* Collector : m_Collectors->GetAllObjects()) {
		Collector->GetSteering()->GetBehaviour<Flee>()->SetTarget(GameInstance::GetGameInstance()->GetWorld()->GetPlayerCharacter());
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
	Timer* ShooterRespawn = new Timer(15.0f);
	ShooterRespawn->OnTimerCompleted.AddListener(this, std::bind(&AI_Manager::SpawnShooter, this));
	GameInstance::GetWorld()->AddSingleUseTimer(ShooterRespawn);
}

void AI_Manager::Handle_CollectorDead()
{
	Timer* RespawnTimer = new Timer(15.0f, 0.0f);
	RespawnTimer->OnTimerCompleted.AddListener(this,std::bind(&AI_Manager::SpawnCollector, this));
}

void AI_Manager::SpawnShooter()
{
	m_Shooters->GetFreeObject()->Activate();
}

void AI_Manager::SpawnCollector()
{
	m_Collectors->GetFreeObject()->Activate();
}

void AI_Manager::OnDestroy()
{
	GameObject::OnDestroy();
	m_Collectors = nullptr;
	m_Shooters = nullptr;
}
