#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Sinibomb.h"

Sinibomb::Sinibomb()
{
	m_SpriteRender = new SpriteRenderer("Assets/SinistarSpriteSheet.png", { 3,8 }, {6,58});
	m_Collider = new Collider(true,5.0f);
	m_RigidBody = new Rigidbody(10.0f);
	m_RigidBody->m_LinearDamp = 0;
}


void Sinibomb::OnCollisionHit(Collider* OtherCollider, E_CollisionEvent ColliderEvent)
{
	if (ColliderEvent != TriggerEnter) { return; }
	
	GameObject* OtherObject = OtherCollider->GetOwner();
	
	if (OtherObject == GetOwner()) {return;}


  	GameFucntionLib::ApplyDamage(OtherObject, 10, dynamic_cast<GameObject*>(GetOwner()));
	Deactivate();
	//if(OtherCollider == GetOwner()->)
}
