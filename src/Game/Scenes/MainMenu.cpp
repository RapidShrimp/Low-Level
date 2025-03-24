#pragma once
#include "MainMenu.h"
#include "Game/UI/UI_Text.h"
#include <iostream>

void MainMenu::OnLoadScene()
{
	GameScene::OnLoadScene();
	UI_Text* Text = new UI_Text("SINISTAR TEST", "Assets/Fonts/sinistar.ttf");
	SpawnObject(Text, Math::Vector2::Zero(), true, "Text");
}
