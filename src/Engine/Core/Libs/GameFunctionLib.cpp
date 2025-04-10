#pragma once
#include <iostream>
#include <windows.h>
#include "Engine/Core/Object.h"
#include "Engine/Core/GameInstance.h"
#include "GameFunctionLib.h"

void GameFucntionLib::ApplyDamage(GameObject* DamageObject, float Damage, GameObject* Instigator)
{
	if (DamageObject == nullptr) { return; }
	DamageObject->OnTakeDamage.Invoke(Damage, Instigator);
}

void GameFucntionLib::SpawnParticleSystem(Math::Vector2(Location), VFX_Particle* ParticleSystem, float Lifetime)
{
	if (ParticleSystem == nullptr) { return; }

}

void Debug::Log(Object* CallingObject, E_LogType LogType, std::string LogMessage) 
{
	if (!GameInstance::GetGameInstance()->ShouldLogDisplay() && LogType == Display) { return; }
	std::string ObjectName = "";
	if (CallingObject != nullptr) 
	{
		std::string ParentName = "";
		Object* Owner = CallingObject->GetOwner();
		if (Owner != nullptr) 
		{
			ParentName = Owner->GetName() + ':';
		}
		ObjectName = '[' + ParentName + CallingObject->GetName() + "] ";
	}

	std::string LogTypeStr;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (LogType)
	{
	case Display:
		LogTypeStr = "Display: ";
		SetConsoleTextAttribute(hConsole,15);
		break;
	case Warning:
		LogTypeStr = "Warning: ";
		SetConsoleTextAttribute(hConsole, 14);
		break;
	case Error:
		LogTypeStr = "ERROR: ";
		SetConsoleTextAttribute(hConsole, 4);
		break;
	}
	cout << ObjectName << LogTypeStr << LogMessage << endl;
	SetConsoleTextAttribute(hConsole, 15);

}