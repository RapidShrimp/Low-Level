#pragma once
#include "HealthComponent.h"
#include <iostream>
#include "Engine/Core/Libs/GameFunctionLib.h"

HealthComponent::HealthComponent()
{
	m_MaxHealth = 100.0f;
	m_CurrentHealth = m_MaxHealth;
}

HealthComponent::HealthComponent(float Health)
{
	m_MaxHealth = Health;
	m_CurrentHealth = m_MaxHealth;
}

void HealthComponent::Handle_OnHeathChanged(float Damage, GameObject* Instigator)
{
	if (!isActive) { return; }

	bool isPositive = Damage >= 0;
	m_CurrentHealth = std::clamp(m_CurrentHealth - Damage,0.0f,m_MaxHealth);
	if (!isPositive) 
	{
		OnHealthRecieve(-Damage);
	}
	else 
	{
		OnDamageTaken(Damage);
	}

	if (m_CurrentHealth == 0) 
	{
		OnDeath();
	}
}
