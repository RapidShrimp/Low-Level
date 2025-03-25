#pragma once
#include "MainMenu.h"
#include "Engine/Core/UI/UI_Text.h"
#include "Engine/Core/Components/SpriteRenderer.h"
#include "Engine/Core/UI/UI_Base.h"
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


	//TODO - Move this into its Own Hud/Widget class so single spawn is easier
	//Play Game Menu Base
	UI_Base* MainMenuUI = new UI_Base();
	SpawnObject(MainMenuUI, { 0,0 });
	UI_Text* PlayGameText = new UI_Text("Play Game", "Assets/Fonts/sinistar.ttf", 24);
	PlayGameText->m_Transform.SetPosition(400, 100);
	UI_Text* ExitButton = new UI_Text("Play Game", "Assets/Fonts/sinistar.ttf", 24);
	MainMenuUI->AddToNavigationPath(PlayGameText);
	MainMenuUI->AddToNavigationPath(ExitButton);

	/*UI_Text* Text = new UI_Text("SINISTAR TEST", "Assets/Fonts/sinistar.ttf");
	SpawnObject(Text, Math::Vector2::Zero(), true, "Text");*/
}
