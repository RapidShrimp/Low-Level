#pragma once
#include "Component.h"
#include "Collider.h"

class Rigidbody : public Component {

public:
	Rigidbody(float MaxSpeed,bool PhaseCollisions = false);
	~Rigidbody() {};

	Math::Vector2 m_Velocity;
	float m_AngluarVelocity = 0;
	
	void Init(Object* Owner) override;
	//virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	//virtual void BeginPlay() override;
	//virtual void Update() override;
	virtual void FixedUpdate(float deltaTime) override;
	//virtual void OnDestroy() override;

	//Overrides Current Velocity and Sets direct Velocity
	void SetVelocity(Math::Vector2(NewVelocity));
	void AddVelocity(Math::Vector2(Velocity));

	void OnCollisionEventCallback(Collider* OtherCollider, E_CollisionEvent Response);
	//All these values may want to be updated at runtime, leave them public (sinistar pieces gain weight, crystal weights ect)
	//Also for AI steering
	float m_MaxSpeed = 1.0f;
	float m_LinearDamp = 0.001f; // 0.01 - 1 || 1 = No Dampen  Default Value = 0.001f;
	float m_AngularDamp = 0.1f;
	float m_mass = 20; 

protected:
	bool m_PhaseCollisions = false;
};