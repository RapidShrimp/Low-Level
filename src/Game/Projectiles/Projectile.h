#pragma once
#include "Engine/Core/GameObject.h"
#include "Engine/Core/Components/Rigidbody.h"
#include "Engine/Core/Components/SpriteRenderer.h"
#include "Engine/Core/Components/Collider.h"

class Projectile : public GameObject {

public:
	Projectile();
	
	void OnFired(GameObject* Owner, Math::Vector2 FireDirection);


	virtual void Init(Object* OwningObject) override;
	//virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	//virtual void BeginPlay() override;
	//virtual void Update() override;
	virtual void FixedUpdate(float deltaTime) override;
	//virtual void Render(sf::RenderWindow& Renderer) override;
	virtual void OnDestroy() override;

	virtual void OnCollisionHit(Collider* OtherCollider, E_CollisionEvent ColliderEvent);


protected:
	Collider* m_Collider = nullptr;
	Rigidbody* m_RigidBody = nullptr;
	SpriteRenderer* m_SpriteRender = nullptr;

	
};