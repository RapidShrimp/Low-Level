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

void HealthComponent::Update()
{

}

void HealthComponent::FixedUpdate()
{
}

void HealthComponent::OnActivate()
{
	Debug::Log(this, E_LogType::Display, "Health Comp Debug");
	GameObject* Owner = static_cast<GameObject*>(m_Owner);
	if (Owner) 
	{
		//Owner->OnHealthChange += std::bind(&HealthComponent::Handle_OnHeathChanged, this, std::placeholders::_1);
	}
}

void HealthComponent::OnDeactivate()
{
	GameObject* Owner = static_cast<GameObject*>(m_Owner);
	if(Owner)
	{
		//Owner->OnHealthChange -= std::bind(&HealthComponent::Handle_OnHeathChanged, this, std::placeholders::_1);
	}

}

void HealthComponent::Handle_OnHeathChanged(float Damage, GameObject* Instigator)
{

}
