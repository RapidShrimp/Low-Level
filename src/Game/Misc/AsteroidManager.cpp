#pragma once
#include "AsteroidManager.h"
#include "Game/Player/PlayerCharacter.h"

AsteroidManager::AsteroidManager()
{
	m_PooledAsteroids = new ObjectPooler<Asteroid>(30, true);
	m_PooledCrystals = new ObjectPooler<Crystal>(10, false);

}

void AsteroidManager::Init(Object* OwningObject)
{

	vector<Object*> Asteroids = m_PooledAsteroids->GetAllObjects();

	for (int i = 0; i < Asteroids.size(); i++) {

		Asteroid* Ast = dynamic_cast<Asteroid*>(Asteroids[i]);
		if (Ast == nullptr) { return; }
		Ast->m_Transform.Location = { Math::Random::Range(0.0f,800.0f),Math::Random::Range(0.0f,800.0f) };
		Ast->OnSpawnCrystal += std::bind(&AsteroidManager::OnSpawnCrystal, this, std::placeholders::_1);
		Ast->OnAsteroidDestroyed += std::bind(&AsteroidManager::OnAsteroidDestroyed, this);
		//TODO - Ast->FindComponentOfType<Rigidbody>()->SetVelocity({ Math::Random::Range(-0.5f,0.5f), Math::Random::Range(-0.5f, 0.5f) });
	}
}

void AsteroidManager::FixedUpdate(float deltaTime)
{
}

void AsteroidManager::OnAsteroidDestroyed()
{
	PlayerCharacter* Player = GameInstance::GetGameInstance()->GetWorld()->GetPlayerCharacter();
	if (!Player) {
		Debug::Log(this, Error, "No Player Found");
		return;
	}
	Player->AddScore(150);
}

void AsteroidManager::OnSpawnCrystal(Math::Vector2(Location))
{
	Crystal* NewCrystal = m_PooledCrystals->GetFreeObject();
	NewCrystal->m_Transform.Location = Location;
	NewCrystal->Activate();

	PlayerCharacter* Player = GameInstance::GetGameInstance()->GetWorld()->GetPlayerCharacter();
	if (!Player) {
		Debug::Log(this, Error, "No Player Found");
		return;
	}
	Player->AddScore(100);
}