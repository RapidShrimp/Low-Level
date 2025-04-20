#pragma once
#include "Engine/Core/GameObject.h"
#include "Engine/Core/ObjectPooler.h"
#include "Game/Pickups/Crystal.h"
#include "Game/Misc/Asteroid.h"

class PlayerCharacter;

class AsteroidManager : public GameObject {


protected:
	ObjectPooler<Asteroid>* m_PooledAsteroids;
	ObjectPooler<Crystal>* m_PooledCrystals;

public:
	AsteroidManager();
	virtual void Init(Object* OwningObject) override;
	//virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	//virtual void BeginPlay() override;
	//virtual void Update() override;
	virtual void FixedUpdate(float deltaTime) override;
	//virtual void Render(sf::RenderWindow& Renderer) override;
	//virtual void OnDestroy() override;

	PlayerCharacter* playerRef;
protected:
	//Spawn an asteroid in a place not colliding
	void InitialPlaceAsteroid(GameObject* Asteroid);
	void PlaceAsteroid(GameObject* Asteroid);

	void OnAsteroidDestroyed();
	void OnSpawnCrystal(Math::Vector2(Location));
};