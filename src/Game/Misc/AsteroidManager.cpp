#pragma once
#include "AsteroidManager.h"

AsteroidManager::AsteroidManager()
{
	m_PooledAsteroids = new ObjectPooler<Asteroid>(30, true);
	m_PooledCrystals = new ObjectPooler<Crystal>(30, true);

}

void AsteroidManager::Init(Object* OwningObject)
{

	vector<Object*> Asteroids = m_PooledAsteroids->GetAllObjects();

	for (int i = 0; i < Asteroids.size(); i++) {

		Asteroid* Ast = dynamic_cast<Asteroid*>(Asteroids[i]);
		if (Ast == nullptr) { return; }
		Ast->m_Transform.Location = { Math::Random::Range(0.0f,800.0f),Math::Random::Range(0.0f,800.0f) };

	}
}

void AsteroidManager::FixedUpdate(float deltaTime)
{
}
