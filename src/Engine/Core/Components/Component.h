#pragma once
#include "Engine/Core/Transform.h"
#include "Engine/Core/GameObject.h"

class Component : public Object
{


protected:
	SinStr::Transform LocalTransform = {};

public:

	void Init(Object* Owner) override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void BeginPlay() override;
	virtual void Update() override;
	virtual void Render(sf::RenderWindow& Renderer) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void OnDestroy() override;

	virtual GameObject* GetOwner() { return dynamic_cast<GameObject*>(m_Owner); }
	void SetLocalTransform(SinStr::Transform NewTransform) { LocalTransform = NewTransform; };
	SinStr::Transform& GetLocalTransform() { return LocalTransform; };
};