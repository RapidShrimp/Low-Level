#include "Rigidbody.h"
#include "Rigidbody.h"
#include "Rigidbody.h"
#include "Rigidbody.h"
#include "Rigidbody.h"
#include "Rigidbody.h"
#include "Rigidbody.h"
#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Rigidbody.h"

Rigidbody::Rigidbody(float MaxSpeed)
{
	m_MaxSpeed = MaxSpeed;
}

void Rigidbody::Init(Object* Owner)
{
	Object::Init(Owner);
	if(m_Owner == nullptr) 
	{
		Debug::Log(this, Error, "No Owner for Rigid Body");
	}
}

void Rigidbody::FixedUpdate(float deltaTime)
{	
	CalculateLateralVelocity();
	CalculateAngularVelocity();

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

void Rigidbody::CalculateLateralVelocity()
{
	if (m_Velocity.Length() <= m_LinearDamp)
	{
		m_Velocity = { 0,0 };
		return;
	}
	//Decelerate
	m_Velocity -= m_Velocity.Normalised() * m_LinearDamp;
}

void Rigidbody::CalculateAngularVelocity()
{
	m_AngluarVelocity = (m_AngluarVelocity * -1) - m_AngularDamp;

}
