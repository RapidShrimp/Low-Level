#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Engine/Core/GameInstance.h"
#include "Engine/Core/AudioManager.h"
#include "Game/Enemies/Boss.h"
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
	AudioManger::PlaySound("laserShoot.wav");
	m_RigidBody->m_Velocity = FireDirection;
	m_Owner = Owner;
}

void Projectile::Init(Object* OwningObject)
{
	RegisterComponent(m_SpriteRender, true, "Projectile Sprite");
	RegisterComponent(m_Collider, true, "Projectile Collider");
	RegisterComponent(m_RigidBody, true, "Projectile RB");
	m_SpriteRender->GetLocalTransform().SetRotation(1.5708);
	m_Collider->OnCollisionEvent.AddListener(this,std::bind(&Projectile::OnCollisionHit, this, std::placeholders::_1,std::placeholders::_2));
}

void Projectile::OnDeactivate()
{
	m_RigidBody->SetVelocity({ 0,0 });
	m_Transform.SetPosition(0, 0);
}

void Projectile::FixedUpdate(float deltaTime)
{
	m_Transform.Location += m_RigidBody->m_Velocity * deltaTime;

	if (GameObject* GameOwner = dynamic_cast<GameObject*>(GetOwner()))
	{
		bool CanDeactivate = (m_Transform.Location - GameOwner->m_Transform.Location).Length() > MINIMAP_SIZE/2;
		if (!CanDeactivate) { return; }
		Deactivate();
	}
	else 
	{
		Deactivate();
		
	}
}

void Projectile::OnDestroy()
{
	m_SpriteRender = nullptr;
	m_Collider = nullptr;
	m_RigidBody = nullptr;
	GameObject::OnDestroy();
}

void Projectile::OnCollisionHit(Collider* OtherCollider, E_CollisionEvent ColliderEvent)
{
	if (ColliderEvent != TriggerEnter) { return; }
	
	GameObject* OtherObject = OtherCollider->GetOwner();
	
	if (OtherObject == GetOwner()) {return;}
	if (dynamic_cast<Boss*>(OtherObject)) 
	{
		Deactivate();
		return; 
	}

  	GameFucntionLib::ApplyDamage(OtherObject, 10, dynamic_cast<GameObject*>(GetOwner()));
	Deactivate();
	//if(OtherCollider == GetOwner()->)
}
