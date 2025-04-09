#pragma
#include "Particle.h"

VFX_Particle::VFX_Particle()
{

}

VFX_Particle::VFX_Particle(bool DestroyOnCompletion)
{
	m_DestroyOnEnd = DestroyOnCompletion;
}

void VFX_Particle::Init(Object* Owner)
{
	Object::Init(Owner);
	//Override Child Functionality Here
	//- Construct SpriteRenderer
	//- Register Components
}

void VFX_Particle::StartParticleSystem(float Lifetime, Math::Vector2(Velocity))
{
	if(Velocity != Math::Vector2::Zero())
	{
		m_RigidBody = new Rigidbody(10.0f);
		m_RigidBody->Activate();
		m_RigidBody->AddVelocity(Velocity);
	}
	m_Lifetime = Lifetime;
	m_SpriteRender->Activate();
}

void VFX_Particle::Update()
{
	Object::Update();
	if (m_RigidBody != nullptr) { m_RigidBody->Update(); }
	if (m_SpriteRender!= nullptr) { m_SpriteRender->Update(); }

}

void VFX_Particle::FixedUpdate(float deltaTime)
{
	if (!isActive) { return; }
	if (m_RigidBody != nullptr) 
	{ 
		m_RigidBody->FixedUpdate(deltaTime);
		return; 
	}
	m_SpriteRender->FixedUpdate(deltaTime);

	m_Lifetime -= deltaTime;
	if (m_Lifetime < 0) { OnParticleSystemEnd(); }
}

void VFX_Particle::Render(sf::RenderWindow& Renderer)
{
	if (!isActive) { return; }
	if (m_SpriteRender == nullptr) {return;}
	m_SpriteRender->Render(Renderer);
}

void VFX_Particle::OnDestroy()
{
	Object::OnDestroy();
	delete m_RigidBody;
	m_RigidBody = nullptr;

	delete m_SpriteRender;
	m_SpriteRender = nullptr;
}

void VFX_Particle::OnParticleSystemEnd()
{
	isActive = false;
	if (m_DestroyOnEnd) {OnDestroy();}

}
