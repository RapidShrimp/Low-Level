#pragma once
#include "Engine/Core/GameObject.h"
#include "Engine/Core/Input/InputSystem.h"

class PlayerCharacter : public GameObject 
{
	float m_MoveSpeed = 10.0f;

public:
	PlayerCharacter();
	~PlayerCharacter();
	virtual void Init(Object* OwningObject) override;
	//virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	virtual void BeginPlay() override;
	//virtual void Update() override;
	//virtual void FixedUpdate() override;
	//virtual void OnDestroy() override;

};