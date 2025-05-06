#pragma once
#include "main.h"
#include <iostream>
#include "Engine/Core/GameInstance.h"

#include "Engine/TestClass.h"

GameInstance* GameInstance::m_GameInstance = nullptr;

int main()
{
	InitialiseEngine();
	Shutdown();
	return 0;
}

void InitialiseEngine() 
{
	//Class created for event demo
	//BroadcasterClass* Broadcaster = new BroadcasterClass();
	//RecieverClass* Reciever1 = new RecieverClass(Broadcaster);
	//RecieverClass* Reciever2 = new RecieverClass(Broadcaster);
	//RecieverClass* Reciever3 = new RecieverClass(Broadcaster);
	//Broadcaster->BroadcastEvent();
	//system("pause");

	cout << "Initialise Sinistar" << endl;
	GameInstance::GetGameInstance()->Init();
	GameInstance::GetGameInstance()->Update();
 }

void Shutdown()
{
	cout << "Sinistar Shut Down..." << endl;
}