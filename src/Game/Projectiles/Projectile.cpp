#include "Projectile.h"
#pragma once
#include "Projectile.h"

Projectile::Projectile()
{
	m_SpriteRender = new SpriteRenderer("Assets/SinistarSpriteSheet.png", { 3,8 }, {6,58});
	m_Collider = new Collider(true,5.0f);
	m_RigidBody = new Rigidbody(10.0f);
}

void Projectile::OnFired(GameObject* Owner, Math::Vector2 FireDirection)
{
	m_RigidBody->m_Velocity = FireDirection * 1000;
	m_Owner = Owner;
}

void Projectile::Init(Object* OwningObject)
{
	RegisterComponent(m_SpriteRender, true, "Projectile Sprite");
	RegisterComponent(m_Collider, true, "Projectile Collider");
	RegisterComponent(m_RigidBody, true, "Projectile RB");


}
