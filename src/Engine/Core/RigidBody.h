#include "Component.h"


enum E_CollisionEvent
{
	TriggerEnter,
	TriggerExit,
	CollisionEnter,
	CollisionExit
};

class RigidBody : Component
{

public:
	RigidBody();
	RigidBody(bool IsTrigger, Vector2 DefaultScale, Vector2 Offset);
	~RigidBody();

protected:
	bool IsTrigger = true;
	Vector2 Scale = Vector2(1, 1);
	Vector2 Offset = Vector2(0, 0);

	void OnCollisionEnter(Collider CollisionGameObject, E_EventType Event);
	void OnColliderEvent(Collider CollisionGameObjecct, E_EventType Event);
};
