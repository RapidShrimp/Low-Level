#pragma once
#include "Engine/Core/GameObject.h"
#include "Engine/Core/Input/InputSystem.h"
#include "Engine/Core/Components/SpriteRenderer.h"
#include "Game/Components/HealthComponent.h"
#include "Engine/Core/Components/Rigidbody.h"
#include "Engine/Core/Components/Collider.h"

class PlayerCharacter : public GameObject 
{
protected:
	HealthComponent* m_Health; 
	SpriteRenderer* m_SpriteRenderer;
	Collider* m_Collider;
	Rigidbody* m_RigidBody;
	float m_MoveSpeed = 0.002f;

	int m_SinibombsHeld = 0;

	Math::Vector2 MoveDirection;

public:
	PlayerCharacter();
	~PlayerCharacter();
	void MovePlayer(CallbackContext Context, Math::Vector2 MoveVector);
	void FireWeapon(CallbackContext Context);

	void CollectSinibomb(); 
	
	void OnCollisionEventCallback(Collider* OtherCollider, E_CollisionEvent Response);

	virtual void Init(Object* OwningObject) override;
	//virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	virtual void BeginPlay() override;
	virtual void Update() override;
	virtual void Render(sf::RenderWindow& Renderer) override;
	virtual void FixedUpdate(float DeltaTime) override;
	//virtual void OnDestroy() override;

};