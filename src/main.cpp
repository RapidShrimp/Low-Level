#pragma once
#include <iostream>
#include "Engine/Core/GameInstance.h"
#include "main.h"


int main()
{
	InitialiseEngine();
	UpdateLoop();
	Shutdown();
	return 0;
}

void InitialiseEngine() 
{
	cout << "Initialise Sinistar" << endl;
	m_Instance = new GameInstance();
	m_Instance->Init();
}

void UpdateLoop()
{
	m_Instance->Update();
}

void Shutdown()
{
	delete m_Instance;
	m_Instance = nullptr;
	cout << "Sinistar Shut Down..." << endl;

}


