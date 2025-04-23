#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Rigidbody.h"

Rigidbody::Rigidbody(float MaxSpeed, bool PhaseCollisions)
{
	m_MaxSpeed = MaxSpeed;
	m_PhaseCollisions = PhaseCollisions;
}

void Rigidbody::Init(Object* Owner)
{
	Object::Init(Owner);
	if(m_Owner == nullptr) 
	{
		Debug::Log(this, Error, "No Owner for Rigid Body");
		return;
	}
	if (!GetOwner()->GetCollider()) {
		Debug::Log(this, Warning, "No Collider found");
		return;
	}
	else {
		GetOwner()->GetCollider()->OnCollisionEvent += std::bind(&Rigidbody::OnCollisionEventCallback, this, std::placeholders::_1, std::placeholders::_2);
	}
}

void Rigidbody::FixedUpdate(float deltaTime)
{	
	//Linear Damped
	if (!isActive) { return; }
	if (m_Velocity.Length() > m_MaxSpeed) {
		m_Velocity = m_Velocity.Normalised() * m_MaxSpeed;
	}

	if (m_Velocity.Length() <= m_LinearDamp)
	{
		m_Velocity = { 0,0 };
		return;
	}
	m_Velocity -= m_Velocity.Normalised() * m_LinearDamp;
	GetOwner()->m_Transform.Location += m_Velocity * deltaTime;
	GetOwner()->m_Transform.Rotation  += m_AngluarVelocity * deltaTime;
	//Angular Dampen
	m_AngluarVelocity = (m_AngluarVelocity * -1) - m_AngularDamp;

}

void Rigidbody::SetVelocity(Math::Vector2(NewVelocity))
{
	m_Velocity = NewVelocity;
}

void Rigidbody::AddVelocity(Math::Vector2(Velocity))
{
	if (Velocity == Math::Vector2::Zero()) { return; }

	m_Velocity += Velocity;
	if (m_Velocity.Length() > m_MaxSpeed)
	{
		Math::Vector2::Normalise(m_Velocity);
		m_Velocity = m_Velocity * m_MaxSpeed ;
	}
}

void Rigidbody::OnCollisionEventCallback(Collider* OtherCollider, E_CollisionEvent Response)
{

	if (m_PhaseCollisions) { return; }
	if (Response != E_CollisionEvent::CollisionEnter) {
		return;
	}

	Debug::Log(this, DebugNone, "Colliding");
	m_Velocity *= -0.8;
	
}
