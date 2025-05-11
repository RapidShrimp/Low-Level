#pragma once

#include "Engine/Core/GameObject.h"
#include "Engine/Core/Components/SpriteRenderer.h"
#include "Engine/Core/Components/Rigidbody.h"
#include "Engine/Core/Components/Collider.h"

class Crystal : public GameObject {


public:
	SinStr::Event<GameObject*> OnCrystalAvaliable;
	SinStr::Event<GameObject*> OnCrystalCollided; //The Game Object Collided With

	Crystal();
	~Crystal() {};

	SpriteRenderer* m_SpriteRenderer = nullptr;
	Rigidbody* m_RigidBody = nullptr;
	Collider* m_Collider = nullptr;

	Math::Vector2 m_CrystalSpeedRange = Math::Vector2(2, 10);
	
	void OnCollisionEvent(Collider* InCollider, E_CollisionEvent Event);

	virtual void Init(Object* OwningObject) override;
	virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	//virtual void BeginPlay() override;
	//virtual void Update() override;
	virtual void FixedUpdate(float deltaTime) override;
	//virtual void Render(sf::RenderWindow& Renderer) override;
	virtual void OnDestroy() override;
};