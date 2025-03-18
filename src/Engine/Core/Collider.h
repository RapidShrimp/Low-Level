#pragma once
#include "Engine/Core/Events/Event.h"
#include "Engine/Core/Components/Component.h"
#include "Engine/Core/Libs/Maths.h"

enum E_CollisionEvent
{
	TriggerEnter,
	TriggerExit,
	CollisionEnter,
	CollisionExit
};

enum E_ColliderType
{
	Circle,
	Box,
	Convex
};

class Collider : public Component
{
public:
	//Events And Constructors
	SinStr::Event<Collider*, E_CollisionEvent> OnCollisionEvent;

	Collider(bool IsTrigger,float Radius,Math::Vector2(Offset) = Math::Vector2::Zero());
	Collider(bool IsTrigger,Math::Vector2(BoxBounds), Math::Vector2(Offset) = Math::Vector2::Zero());
	~Collider() {};

	virtual void Update() override;
	const float GetRadius() { return m_Radius; }
	const Math::Vector2 GetBoxBounds() { return m_BoxBounds; }
protected:
	
	E_ColliderType m_CollisionType = Circle;
	bool m_IsTrigger = true;
	static bool CircleCollision(Collider* CircleA, Collider* CircleB);
	static bool BoxCollision(Collider* BoxA, Collider* BoxB);
	static bool BoxCircleCollision(Collider* Box, Collider* Circle);

private:
	float m_Radius = 0;
	Math::Vector2 m_BoxBounds = Math::Vector2::Zero();

};