#include "AsteroidManager.h"
#pragma once
#include "AsteroidManager.h"

AsteroidManager::AsteroidManager()
{
	m_PooledAsteroids = new ObjectPooler<Asteroid>(30, true);
	m_PooledCrystals = new ObjectPooler<Crystal>(10, true);

}

void AsteroidManager::Init(Object* OwningObject)
{

	vector<Object*> Asteroids = m_PooledAsteroids->GetAllObjects();

	for (int i = 0; i < Asteroids.size(); i++) {

		Asteroid* Ast = dynamic_cast<Asteroid*>(Asteroids[i]);
		if (Ast == nullptr) { return; }
		Ast->m_Transform.Location = { Math::Random::Range(0.0f,800.0f),Math::Random::Range(0.0f,800.0f) };
		Ast->OnSpawnCrystal += std::bind(&AsteroidManager::OnSpawnCrystal, this, std::placeholders::_1);

	}
}

void AsteroidManager::FixedUpdate(float deltaTime)
{
}

void AsteroidManager::OnSpawnCrystal(Math::Vector2(Location))
{
	Crystal* NewCrystal = m_PooledCrystals->GetFreeObject();
	NewCrystal->m_Transform.Location = Location;
	NewCrystal->Activate();
}