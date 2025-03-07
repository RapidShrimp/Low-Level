#pragma once
#include "Engine/Core/Component.h"
#include "Engine/Core/Events/Event.h"

class HealthComponent : public Component {

public:
	SinStr::Event<> OnDeath;
	SinStr::Event<float> OnDamageTaken; //New Health
	SinStr::Event<float> OnHealthRecieve; //New Health

public:
	HealthComponent();
	HealthComponent(float Health);
	
	virtual void Update() override;
	virtual void FixedUpdate() override;

	void OnActivate() override;
	void OnDeactivate() override;
	void Handle_OnHeathChanged(float Damage, GameObject* Instigator);
protected:
	float m_CurrentHealth;
	float m_MaxHealth;

};