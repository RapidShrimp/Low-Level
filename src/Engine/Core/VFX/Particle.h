#pragma once
#include "Engine/Core/Object.h"
#include "Engine/Core/Components/SpriteRenderer.h"
#include "Engine/Core/Components/Rigidbody.h"

class VFX_Particle : public Object {

protected:
	SpriteRenderer* m_SpriteRender = nullptr;
	float m_Lifetime = 1.0f;
	bool m_DestroyOnEnd = false;

public:
	VFX_Particle();
	VFX_Particle(bool DestroyOnCompletion);

	virtual void Init(Object* Owner) override;
	virtual void StartParticleSystem(float Lifetime, Math::Vector2(Velocity) = Math::Vector2::Zero());
	virtual void Update();
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Render(sf::RenderWindow& Renderer) override;
	virtual void OnDestroy() override;
protected:

	void OnParticleSystemEnd();

private:
	Rigidbody* m_RigidBody = nullptr;

};