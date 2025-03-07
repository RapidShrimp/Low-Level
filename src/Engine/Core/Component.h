#pragma once
#include "Transform.h"
#include "GameObject.h"

class Component : public Object
{
public:
	virtual void Init(Object* Owner) override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void BeginPlay() override;
	virtual void Update() override;
	virtual void FixedUpdate() override;
	virtual void Render(sf::RenderWindow& Renderer) override;
	virtual void OnDestroy() override;

};