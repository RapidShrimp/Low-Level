#include "<Engine/Public/Transform.h"

class GameObject 
{
	//Some basic functionality that all game objects should hav
	GameObject(){}
	~GameObject(){};
	void Init();
	void OnActivate();
	void OnDeactivate();
	void BeginPlay();
	void Update();
	void FixedUpdate();
	void OnCollisionEnter(Collider CollisionGameObject,E_EventType Event);
	void OnColliderEvent(Collider CollisionGameObjecct,E_EventType Event);
};
