#pragma once
#include <iostream>
#include "Engine/Core/Object.h"
#include "GameFunctionLib.h"

void GameFucntionLib::ApplyDamage(GameObject* DamageObject, float Damage, GameObject* Instigator)
{
	if (DamageObject == nullptr) { return; }
	DamageObject->OnTakeDamage.Invoke(Damage, Instigator);
}

void Debug::Log(Object* CallingObject, E_LogType LogType, std::string LogMessage) 
{

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
	switch (LogType)
	{
	case Display:
		LogTypeStr = "Display: ";
		break;
	case Warning:
		LogTypeStr = "Warning: ";
		break;
	case Error:
		LogTypeStr = "ERROR: ";
		break;
	}
	cout << ObjectName << LogTypeStr << LogMessage << endl;
}