#pragma once
#include "Engine/Core/Events/Event.h"
#include "Engine/Core/Components/Component.h"
#include "Engine/Core/Libs/Maths.h"

enum E_CollisionEvent
{
	None,
	TriggerEnter,
	TriggerColliding,
	TriggerExit,
	CollisionEnter,
	CollisionColliding,
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

	Collider(bool IsTrigger,float Radius);
	Collider(bool IsTrigger,Math::Vector2(BoxBounds));
	~Collider() {};



	void Init(Object* Owner) override;
	virtual void Update() override;
	virtual void Render(sf::RenderWindow& Renderer) override;

	const float GetRadius() { return m_Radius; }
	const Math::Vector2 GetBoxBounds() { return m_BoxBounds; }
protected:
	
	E_ColliderType m_CollisionType = Circle;
	bool m_IsTrigger = true;
	bool CircleCollision(Collider* OtherCircle);
	bool BoxCollision(Collider* OtherBox);
	bool BoxCircleCollision(Collider* OtherCollider);

	std::vector<Collider*> Overlapping;

private:
	float m_Radius = 0;
	Math::Vector2 m_BoxBounds = Math::Vector2::Zero();

};