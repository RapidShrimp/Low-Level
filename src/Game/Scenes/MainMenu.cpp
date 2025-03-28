#pragma once
#include "MainMenu.h"
#include "Engine/Core/Components/SpriteRenderer.h"
#include "Game/UI/UI_MainMenu.h"
#include <iostream>

void MainMenu::OnLoadScene()
{
	GameScene::OnLoadScene();


	//The UI Logo
	GameObject* MainMenu = new GameObject();
	SpawnObject(MainMenu,Math::Vector2(720/2,18*4.5));
	SpriteRenderer* MenuLogoSprite = new SpriteRenderer("Assets/SinistarSpriteSheet.png", { 170,37 }, { 1,1 }, 1, 1);
	MenuLogoSprite->SetSpriteScale(4.23, 4.23);
	MainMenu->RegisterComponent(MenuLogoSprite,true,"MenuSprite");


	//Spawn UI
	UI_Base* MainMenuUI = new UI_MainMenu();
	SpawnObject(MainMenuUI, { 0,0 });




}
