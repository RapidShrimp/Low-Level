#pragma once
#include "Engine/Core/GameInstance.h"
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Collider.h"



Collider::Collider(bool IsTrigger, float Radius, Math::Vector2(Offset))
{
	m_CollisionType = Circle;
	m_IsTrigger = IsTrigger;
	m_Radius = Radius;
	m_LocalTransform.Location = Offset;
}

Collider::Collider(bool IsTrigger, Math::Vector2(BoxBounds), Math::Vector2(Offset))
{
	m_CollisionType = Box;
	m_IsTrigger = IsTrigger;
	m_BoxBounds = BoxBounds;
	m_LocalTransform.Location = Offset;
}

void Collider::Update()
{
	std::vector<GameObject*> Objects = GameInstance::GetGameInstance()->GetWorld()->GetGameObjects();
	
	for (int i = 0; i < Objects.size(); i++) {
		
		//Ownership Distance Check && Collider Check 
		if (Objects[i] == m_Owner) { continue; }
		if (Objects[i]->GetCollider() == nullptr) { continue; }
		if ((Objects[i]->m_Transform.Location - GetOwner()->m_Transform.Location).Length() > 150.0f) { continue; }
		
		//if (CircleCollision(Objects[i]->GetCollider())) { return; }
	}
}

bool Collider::CircleCollision(Collider* CircleA, Collider* CircleB)
{
	if (CircleA == nullptr || CircleB == nullptr) { return false; }
	//Validation Checks to see if we need to continue with this function
	if (CircleA->m_CollisionType != Circle || CircleB->m_CollisionType != Circle) { return false; }
	
	//Get the distance between the 2 objects
	float Distance = Math::Vector2(
		(CircleA->GetOwner()->m_Transform.Location.x - CircleB->GetOwner()->m_Transform.Location.x),
		(CircleA->GetOwner()->m_Transform.Location.y - CircleB->GetOwner()->m_Transform.Location.y)).Length();
	
	float CollisionDistance = CircleA->GetRadius() + CircleB->GetRadius();
	return Distance < CollisionDistance;
}

bool Collider::BoxCollision(Collider* BoxA, Collider* BoxB)
{
	//Validation Checks to see if we need to continue with this function
	if (BoxA->m_CollisionType != Box || BoxB->m_CollisionType != Box) { return false; }


	return false;
}

bool Collider::BoxCircleCollision(Collider* ColliderA, Collider* ColliderB)
{
	//Validation Checks to see if we need to continue with this function
	if (ColliderA->m_CollisionType == ColliderB->m_CollisionType) { return false; }
	
	return false;
}
