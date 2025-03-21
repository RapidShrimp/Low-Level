#pragma once
#include "Component.h"

class Rigidbody : public Component {

public:
	Rigidbody(float MaxSpeed);
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
protected:

	void CalculateLateralVelocity();
	void CalculateAngularVelocity();

	
	float m_MaxSpeed = 10.0f;
	float m_LinearDamp = 0.001f; // 0.01 - 1 || 1 = No Dampen
	float m_AngularDamp = 0.1f;
};