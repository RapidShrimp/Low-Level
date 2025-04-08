#include "Projectile.h"
#pragma once
#include "Projectile.h"

Projectile::Projectile()
{
	m_SpriteRender = new SpriteRenderer("Assets/SinistarSpriteSheet.png", { 3,8 }, {6,58});
	m_Collider = new Collider(true,5.0f);
	m_RigidBody = new Rigidbody(10.0f);
	m_RigidBody->m_LinearDamp = 0;
}

void Projectile::OnFired(GameObject* Owner, Math::Vector2 FireDirection)
{
	m_RigidBody->m_Velocity = FireDirection;

	m_Owner = Owner;
}

void Projectile::Init(Object* OwningObject)
{
	RegisterComponent(m_SpriteRender, true, "Projectile Sprite");
	RegisterComponent(m_Collider, true, "Projectile Collider");
	RegisterComponent(m_RigidBody, true, "Projectile RB");
}

void Projectile::FixedUpdate(float deltaTime)
{
	m_Transform.Location += m_RigidBody->m_Velocity * deltaTime;

	if (GameObject* GameOwner = dynamic_cast<GameObject*>(GetOwner()))
	{
		bool CanDeactivate = (m_Transform.Location - GameOwner->m_Transform.Location).Length() > 1000;
		if (!CanDeactivate) { return; }
		Deactivate();
	}
	else 
	{
		Deactivate();
		
	}
}
