#pragma once
#include "MainMenu.h"
#include "Engine/Core/AudioManager.h"
#include "Engine/Core/Components/SpriteRenderer.h"
#include "Game/UI/UI_MainMenu.h"
#include <iostream>

MainMenu::MainMenu()
{
	m_SceneName = "Main Menu";
	SetName("Main Menu");
}

void MainMenu::OnLoadScene()
{
	GameScene::OnLoadScene();


	AudioManger::PlayMusic("sinistarHomeMusic.mp3", true);
	
	//The UI Logo
	GameObject* MainMenu = new GameObject();
	SpawnObject(MainMenu,Math::Vector2(720/2,18*4.5));
	
	//Renderer Component
	SpriteRenderer* MenuLogoSprite = new SpriteRenderer("Assets/SinistarSpriteSheet.png", { 170,37 }, { 1,1 }, 1, 1);
	MainMenu->RegisterComponent(MenuLogoSprite,true,"MenuSprite");
	MenuLogoSprite->GetLocalTransform().SetScale(3.23f, 3.23f);

	//Spawn UI
	UI_Base* MainMenuUI = new UI_MainMenu();
	SpawnObject(MainMenuUI, { 0,0 });

}
