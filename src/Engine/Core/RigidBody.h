#include "Component.h"
#include "Maths.h"

enum E_CollisionEvent
{
	TriggerEnter,
	TriggerExit,
	CollisionEnter,
	CollisionExit
};

class RigidBody : public Component
{
public:
	RigidBody(bool IsTrigger, Math::Vector2 DefaultScale, Math::Vector2 Offset = {0,0});
	~RigidBody();

protected:
	bool IsTrigger = true;
	Math::Vector2 Scale = {1,1};
	Math::Vector2 Offset = {0,0};

	void OnCollisionEnter(Collider CollisionGameObject, E_CollisionEvent Event);
	void OnColliderEvent(Collider CollisionGameObjecct, E_CollisionEvent Event);
};
