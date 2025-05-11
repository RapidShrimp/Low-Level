#pragma once
#include "main.h"
#include <iostream>
#include "Engine/Core/GameInstance.h"
#include "Engine/TestClass.h"

GameInstance* GameInstance::m_GameInstance = nullptr;


class TestClass {
	int A = 1;
};

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

