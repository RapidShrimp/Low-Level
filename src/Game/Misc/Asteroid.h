#pragma once
#include "Engine/Core/GameObject.h"
#include "Engine/Core/Components/SpriteRenderer.h"
#include "Game/Components/HealthComponent.h"
#include "Engine/Core/Components/Rigidbody.h"
#include "Engine/Core/Components/Collider.h"

class Asteroid : public GameObject {

protected:
	HealthComponent* m_Health;
	SpriteRenderer* m_SpriteRenderer;
	Collider* m_Collider;
	Rigidbody* m_RigidBody;

	int Hits = 0;
	int CrystalRequireHits = 3;

public:

	SinStr::Event<Math::Vector2> OnSpawnCrystal;
	SinStr::Event<>OnAsteroidDestroyed;

	Asteroid();
	~Asteroid();

	virtual void Init(Object* OwningObject) override;
	virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	virtual void BeginPlay() override;
	virtual void Update() override;
	virtual void FixedUpdate(float DeltaTime) override;
	//virtual void OnDestroy() override;


private:
	void Handle_OnAsteroidHit(float InDamage);
	void Handle_OnAsteroidDestroyed(float InDamage);
};