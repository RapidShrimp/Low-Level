#pragma once
#include "AsteroidManager.h"
#include "Game/Player/PlayerCharacter.h"
#include "Engine/Core/Components/Rigidbody.h"

AsteroidManager::AsteroidManager()
{
	m_PooledAsteroids = new ObjectPooler<Asteroid>(60, true);
	m_PooledCrystals = new ObjectPooler<Crystal>(10, false);

}

void AsteroidManager::Init(Object* OwningObject)
{
	playerRef = GameInstance::GetGameInstance()->GetWorld()->GetPlayerCharacter();

	vector<Asteroid*> Asteroids = m_PooledAsteroids->GetAllObjects();

	for (int i = 0; i < Asteroids.size(); i++) {

		Asteroid* Ast = dynamic_cast<Asteroid*>(Asteroids[i]);
		if (Ast == nullptr) { return; }
		Ast->OnSpawnCrystal.AddListener(this,std::bind(&AsteroidManager::OnSpawnCrystal, this, std::placeholders::_1));
		Ast->OnAsteroidDestroyed.AddListener(this,std::bind(&AsteroidManager::OnAsteroidDestroyed, this));
		InitialPlaceAsteroid(Ast);
		Rigidbody* rb = Ast->FindComponentOfType<Rigidbody>();
		if (rb != nullptr) 
		{ 
			rb->SetVelocity({ Math::Random::Range(-0.5f,0.5f), Math::Random::Range(-0.5f, 0.5f) }); 
		}

	}
	Object::Init(OwningObject);
}

void AsteroidManager::FixedUpdate(float deltaTime)
{
	vector<Crystal*> Crystals = m_PooledCrystals->GetAllObjects();

	//for (Crystal* Cryst : Crystals.begin(), Crystals.end()) 
	//{
	//	if (Cryst->GetIsActive() && !Cryst->isAttached) {
	//		
	//	}
	//}
}

void AsteroidManager::OnDestroy()
{

	vector<Asteroid*> Asteroids = m_PooledAsteroids->GetAllObjects();

	for (int i = 0; i < Asteroids.size(); i++) {

		Asteroid* Ast = dynamic_cast<Asteroid*>(Asteroids[i]);
		if (Ast == nullptr) { return; }
		Ast->OnSpawnCrystal.RemoveListener(this, std::bind(&AsteroidManager::OnSpawnCrystal, this, std::placeholders::_1));
		Ast->OnAsteroidDestroyed.RemoveListener(this, std::bind(&AsteroidManager::OnAsteroidDestroyed, this));

	}

	GameObject::OnDestroy();
	m_PooledAsteroids = nullptr;
	m_PooledCrystals = nullptr;
	playerRef = nullptr;
}

void AsteroidManager::InitialPlaceAsteroid(GameObject* Asteroid)
{
	do
	{
		const Math::Vector2 PlayerTrans = GameInstance::GetGameInstance()->GetPlayer()->m_Transform.Location;
		float xPos = Math::Random::Range(PlayerTrans.x - MINIMAP_SIZE, PlayerTrans.x + MINIMAP_SIZE);
		float yPos = Math::Random::Range(PlayerTrans.y - MINIMAP_SIZE, PlayerTrans.y + MINIMAP_SIZE);
		Asteroid->m_Transform.Location = { xPos,yPos };
		Asteroid->GetCollider()->Update();
	} while (Asteroid->GetCollider()->IsOverlapping());

}

void AsteroidManager::PlaceAsteroid(GameObject* Asteroid)
{
	Math::Vector2 PlayerPos = playerRef->m_Transform.Location;

	Rigidbody* rb = playerRef->FindComponentOfType<Rigidbody>();
	if (rb == nullptr) { 
		Debug::Log(this, Error, "No Rigidbody found on player"); 
		assert("The Player Must have a Rigid body", rb != nullptr);
		return;
	}
	Math::Vector2 Vel = rb->m_Velocity.Normalised();
	float isMovingRight = Vel.x > 0 ? 1 : -1;
	float isMovingUp = Vel.y > 0 ? 1 : -1;

	float xPos = Math::Random::Range(PlayerPos.x + WINDOW_WIDTH * isMovingRight, PlayerPos.x + WINDOW_WIDTH * isMovingRight + 150);
	float yPos = Math::Random::Range(PlayerPos.y + WINDOW_HEIGHT * isMovingUp, PlayerPos.y + WINDOW_HEIGHT * isMovingUp + 150);
	Asteroid->m_Transform.Location = { xPos,yPos };
	Asteroid->GetCollider()->Update();
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