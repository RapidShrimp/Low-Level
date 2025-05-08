#pragma once
#include "Engine/Core/GameObject.h"
#include "Engine/Core/VFX/Particle.h"

class GameFucntionLib {
public:

	static void ApplyDamage(GameObject* DamageObject, float Damage, GameObject* Instigator = nullptr);
	static void SpawnParticleSystem(Math::Vector2(Location), VFX_Particle* ParticleSystem, float Lifetime);
};

enum E_LogType {
	Display = 0,
	Warning = 1,
	Error = 2,
	DebugNone = 3,
	Confirm = 4
};

class Debug{

public:

	static void Log(Object* CallingObject, E_LogType LogType, std::string LogMessage);

	const static bool LogAll = true;
};



