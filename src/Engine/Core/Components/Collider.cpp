#pragma once
#include "Engine/Core/GameInstance.h"
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Collider.h"



Collider::Collider(bool IsTrigger, float Radius)
{
	m_CollisionType = Circle;
	m_IsTrigger = IsTrigger;
	m_Radius = Radius;
}

Collider::Collider(bool IsTrigger, Math::Vector2(BoxBounds))
{
	m_CollisionType = Box;
	m_IsTrigger = IsTrigger;
	m_BoxBounds = BoxBounds;
}

void Collider::Init(Object* Owner)
{
	Object::Init(Owner);

	
	m_LocalTransform.Location += m_CollisionType == Box ? m_BoxBounds / 2 : Math::Vector2(m_Radius,m_Radius);
}

void Collider::Update()
{
	if (!isActive) { return; }

	std::vector<GameObject*> Objects = GameInstance::GetGameInstance()->GetWorld()->GetGameObjects();
	E_CollisionEvent ColliderEvent;
	for (int i = 0; i < Objects.size(); i++) {

		ColliderEvent = None;
	
		//Ownership Check && Collider Owner Null Check 
		if (Objects[i] == m_Owner || Objects[i] == nullptr) { continue; }
		Collider* OtherCollider = Objects[i]->GetCollider();

		//Is In collision check range?
		if ((Objects[i]->m_Transform.Location - GetOwner()->m_Transform.Location).Length() > 150.0f) { continue; }
		bool Collided;

		//If the collider does not exist
		if (OtherCollider == nullptr) { continue; }

		//If the other Collider is Active
		if (!OtherCollider->isActive) { continue; }

		//Are Both Triggers?
		if (m_IsTrigger && OtherCollider->m_IsTrigger) { continue; }

		//Collision Checks
		if (OtherCollider->m_CollisionType == Box && m_CollisionType == Box){ //Box
			 Collided = BoxCollision(OtherCollider);
		}
		else if (OtherCollider->m_CollisionType == Circle && m_CollisionType == Circle){ //Circle
			Collided = CircleCollision(OtherCollider);
		}
		else { //Circle && Box
			Collided = BoxCircleCollision(OtherCollider);
		}


		int Index = -1;
		for (int i = 0; i < Overlapping.size(); i++) {

			// When the element is found
			if (Overlapping[i] == OtherCollider) {
				Index = i;
			}
		}

		//if the Overlapping evnts contains it already?
		if (Index != -1){

			if (!Collided) 
			{ 
				//Exit Event
				Debug::Log(this, Display, "Collision Exit");
				ColliderEvent = m_IsTrigger ? TriggerExit : CollisionExit;
				OnCollisionEvent(OtherCollider, ColliderEvent);
				Overlapping.erase(Overlapping.begin()+Index);
				continue; 
			}

			//Continuous Event
			ColliderEvent = m_IsTrigger ? TriggerColliding : CollisionColliding;
			OnCollisionEvent(OtherCollider,ColliderEvent);

		}
		else if (Collided) {
			ColliderEvent = m_IsTrigger ? TriggerEnter : CollisionEnter;
			Overlapping.push_back(OtherCollider);
			OnCollisionEvent(OtherCollider, ColliderEvent);
			Debug::Log(this, Display, "Collision Added");
		}
	}
}

void Collider::Render(sf::RenderWindow& Renderer)
{
	if (!isActive) { return; }

	if (!GameInstance::GetGameInstance()->ShouldDrawDebug()) { return; }
	//Debugging
	if (m_CollisionType == Circle) 
	{
		sf::CircleShape circle;
		circle.setRadius(m_Radius);
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineColor(sf::Color::Green);
		circle.setOutlineThickness(1.0f);
		circle.setPosition((GetOwner()->m_Transform.Location + Math::Vector2(-m_Radius,-m_Radius)).ToSF());
		Renderer.draw(circle);
	}
	else if (m_CollisionType == Box) {
		sf::RectangleShape Rect;
		Rect.setFillColor(sf::Color::Transparent);
		Rect.setOutlineColor(sf::Color::Green);
		Rect.setOutlineThickness(1.0f);
		Rect.setSize(m_BoxBounds.ToSF());
		Rect.setPosition((GetOwner()->m_Transform.Location - m_BoxBounds/2).ToSF());
		Renderer.draw(Rect);
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

