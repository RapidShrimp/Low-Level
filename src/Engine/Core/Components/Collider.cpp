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

		Collider* OtherCollider = Objects[i]->GetCollider();
		if (OtherCollider == nullptr) { continue; }

		if ((Objects[i]->m_Transform.Location - GetOwner()->m_Transform.Location).Length() > 150.0f) { continue; }
		bool Collided;
		if (OtherCollider->m_CollisionType == Box && m_CollisionType == Box){
			 Collided = BoxCollision(OtherCollider);
		}
		else if (OtherCollider->m_CollisionType == Circle && m_CollisionType == Circle){
			Collided = CircleCollision(OtherCollider);
		}
		else {
			Collided = BoxCircleCollision(OtherCollider);
		}
		//TODO-Broadcast Collision Event
		//OnCollisionEvent(this, E_CollisionEvent);
	}
}

bool Collider::CircleCollision(Collider* OtherCircle)
{
	if (OtherCircle == nullptr) { return false; }
	//Get the distance between the 2 objects
	float Distance = Math::Vector2(
		(GetOwner()->m_Transform.Location.x - OtherCircle->GetOwner()->m_Transform.Location.x),
		(GetOwner()->m_Transform.Location.y - OtherCircle->GetOwner()->m_Transform.Location.y)).Length();

	float CollisionDistance = GetRadius() + OtherCircle->GetRadius();

	return Distance < CollisionDistance;
}

bool Collider::BoxCollision(Collider* OtherBox)
{
	Math::Vector2 AMin = GetOwner()->m_Transform.Location - m_BoxBounds / 2;
	Math::Vector2 AMax = GetOwner()->m_Transform.Location + m_BoxBounds / 2;

	Math::Vector2 BMin = OtherBox->GetOwner()->m_Transform.Location - OtherBox->m_BoxBounds / 2;
	Math::Vector2 BMax = OtherBox->GetOwner()->m_Transform.Location + OtherBox->m_BoxBounds / 2;

	return (AMin.x < BMax.x && AMax.x > BMin.x && AMin.y < BMax.y && AMax.y > BMin.y);
}

bool Collider::BoxCircleCollision(Collider* OtherCollider)
{
	Collider* ACircle = m_CollisionType == Circle ? this : OtherCollider;
	Collider* BBox = m_CollisionType != Circle ? this : OtherCollider;
	Math::Vector2 AMin = BBox->GetOwner()->m_Transform.Location - BBox->m_BoxBounds / 2;
	Math::Vector2 AMax = BBox->GetOwner()->m_Transform.Location + BBox->m_BoxBounds / 2;

	Math::Vector2 ClosestPoint = {
		std::clamp(ACircle->GetOwner()->m_Transform.Location.x, AMin.x, AMax.x),
		std::clamp(ACircle->GetOwner()->m_Transform.Location.y, AMin.y, AMax.y)
	};

	return  (ACircle->GetOwner()->m_Transform.Location - ClosestPoint).Length() <= ACircle->m_Radius;
}

