#pragma once
#include "main.h"
#include <iostream>
#include "Engine/Core/GameInstance.h"

GameInstance* GameInstance::m_GameInstance = nullptr;

int main()
{
	InitialiseEngine();
	Shutdown();
	return 0;
}

void InitialiseEngine() 
{
	cout << "Initialise Sinistar" << endl;
	GameInstance::GetGameInstance()->Init();
	GameInstance::GetGameInstance()->Update();
}


void Shutdown()
{
	cout << "Sinistar Shut Down..." << endl;
}


