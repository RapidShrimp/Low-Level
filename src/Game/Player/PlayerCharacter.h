#pragma once
#include "Engine/Core/GameObject.h"
#include "Engine/Core/Input/InputSystem.h"
#include "Engine/Core/Components/SpriteRenderer.h"
#include "Game/Components/HealthComponent.h"

class PlayerCharacter : public GameObject 
{
protected:
	HealthComponent* m_Health; 
	SpriteRenderer* m_SpriteRenderer;
	float m_MoveSpeed = 10.0f;

public:
	PlayerCharacter();
	~PlayerCharacter();

	void MovePlayer(Math::Vector2 MoveDirection);
	void FireWeapon();
	
	virtual void Init(Object* OwningObject) override;
	//virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	virtual void BeginPlay() override;
	virtual void Update() override;
	//virtual void FixedUpdate() override;
	//virtual void OnDestroy() override;

};