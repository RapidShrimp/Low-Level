#pragma once
#include "Engine/Core/GameObject.h"

class GameFucntionLib {
public:

	static void ApplyDamage(GameObject* DamageObject, float Damage, GameObject* Instigator = nullptr);

};

static enum E_LogType {
	Display = 0,
	Warning = 1,
	Error = 2
};

class Debug{

public:

	static void Log(Object* CallingObject, E_LogType LogType, std::string LogMessage);


};



