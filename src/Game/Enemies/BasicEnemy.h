#pragma once
#include "Engine/Core/GameObject.h"
#include "Engine/Core/Components/SpriteRenderer.h"
#include "Game/Components/HealthComponent.h"

class Enemy : public GameObject 
{
protected:
	HealthComponent* m_Health;
	SpriteRenderer* m_SpriteRenderer;
	Collider* m_Collider;
	float m_MoveSpeed = 1.0f;

public:
	Enemy();
	~Enemy() {};
	virtual void Init(Object* OwningObject) override;
	//virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	virtual void BeginPlay() override;
	virtual void Update() override;
	virtual void FixedUpdate(float DeltaTime) override;
	//virtual void OnDestroy() override;

};