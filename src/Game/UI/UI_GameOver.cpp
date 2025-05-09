#pragma once
#include "UI_GameOver.h"
#include "Game/Scenes/MainMenu.h"

void UI_EndGameScreen::Init(Object* OwningObject)
{
	//UI Button Play Game
	UI_Text* PlayGameText = new UI_Text("Return to Main Menu", "Assets/Fonts/sinistar.ttf", 24);
	PlayGameText->SetAlignment(Center);
	PlayGameText->m_Transform.SetPosition(720 / 2, 500);
	AddToNavigationPath(PlayGameText);

	SetNavigationFocus();
	BindableInput* SelectNav = InputEventHandler::GetInstance()->CreateKeyInput(sf::Keyboard::Key::Enter,true);
	if (SelectNav) { SelectNav->OnInputUpdate.AddListener(this, std::bind(&UI_EndGameScreen::Handle_Select, this, std::placeholders::_1)); }

}

void UI_EndGameScreen::SetScore(float Score)
{
}

void UI_EndGameScreen::Handle_Select(CallbackContext Context)
{
	if (Context.Started) {
		GameInstance::GetGameInstance()->QueueGameScene(new MainMenu());
	}
}
