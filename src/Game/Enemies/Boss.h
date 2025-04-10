#pragma once
#include "Game/Enemies/BasicEnemy.h"


class Boss : public Enemy {

public:
	Boss();

	virtual void Init(Object* OwningObject) override;
	//virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	virtual void BeginPlay() override;
	virtual void Update() override;
	virtual void FixedUpdate(float DeltaTime) override;
	//virtual void OnDestroy() override;
};