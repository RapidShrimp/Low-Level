#pragma once
#include "Engine/Core/Components/Component.h"
#include "Engine/Core/Events/Event.h"

class HealthComponent : public Component {

public:
	SinStr::Event<> OnDeath;
	SinStr::Event<float> OnDamageTaken; //New Health
	SinStr::Event<float> OnHealthRecieve; //New Health

public:
	HealthComponent();
	HealthComponent(float Health);
	virtual void BeginPlay() override;
	void SetHealth(float InHealth) { m_CurrentHealth = InHealth; }
	float GetHealthPercent() { return m_CurrentHealth / m_MaxHealth; }
	float GetCurrentHealth() { return m_CurrentHealth; }
	float GetMaxHealth() { return m_MaxHealth; }

	void Handle_OnHeathChanged(float Damage, GameObject* Instigator);
protected:
	float m_CurrentHealth;
	float m_MaxHealth;

};