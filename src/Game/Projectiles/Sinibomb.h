#pragma once
#include "Engine/Core/GameObject.h"
#include "Engine/Core/Components/Rigidbody.h"
#include "Engine/Core/Components/SpriteRenderer.h"
#include "Engine/Core/Components/Collider.h"
#include "Projectile.h"

class Sinibomb : public Projectile {

public:
	Sinibomb();
	
	//virtual void Init(Object* OwningObject) override;
	//virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	//virtual void BeginPlay() override;
	//virtual void Update() override;
	//virtual void FixedUpdate(float deltaTime) override;
	//virtual void Render(sf::RenderWindow& Renderer) override;
	//virtual void OnDestroy() override;

	virtual void OnCollisionHit(Collider* OtherCollider, E_CollisionEvent ColliderEvent) override;

};