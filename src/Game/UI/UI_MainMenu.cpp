#pragma once
#include "Engine/Core/UI/UI_Text.h"
#include "Engine/Core/GameInstance.h"
#include "Game/Scenes/GameLevel.h"
#include "UI_MainMenu.h"

void UI_MainMenu::Init(Object* OwningObject)
{
	Object::Init(OwningObject);

	//UI Button Play Game
	UI_Text* PlayGameText = new UI_Text("Play Game", "Assets/Fonts/sinistar.ttf", 24);
	PlayGameText->SetAlignment(Center);
	PlayGameText->m_Transform.SetPosition(720 / 2, 500);
	AddToNavigationPath(PlayGameText);

	//UI Button Exit Game
	UI_Text* ExitButton = new UI_Text("Exit Game", "Assets/Fonts/sinistar.ttf", 24);
	ExitButton->m_Transform.SetPosition(720 / 2, 600);
	ExitButton->SetAlignment(Center);
	AddToNavigationPath(ExitButton);

	SetNavigationFocus();

	BindableInput* UpNavigation = InputEventHandler::GetInstance()->CreateKeyInput(sf::Keyboard::Key::W);
	BindableInput* DownNavigation = InputEventHandler::GetInstance()->CreateKeyInput(sf::Keyboard::Key::S);
	BindableInput* SelectNav = InputEventHandler::GetInstance()->CreateKeyInput(sf::Keyboard::Key::Enter);

	if (UpNavigation) { UpNavigation->OnInputUpdate += std::bind(&UI_MainMenu::Handle_UpInput, this, std::placeholders::_1); }
	if (DownNavigation) { DownNavigation->OnInputUpdate += std::bind(&UI_MainMenu::Handle_DownInput, this, std::placeholders::_1); }
	if (SelectNav) { SelectNav->OnInputUpdate += std::bind(&UI_MainMenu::Handle_Select, this, std::placeholders::_1); }


}

void UI_MainMenu::Handle_UpInput(CallbackContext Context)
{
	if (!Context.Started) { return; }
	NavigatePrevious();
}

void UI_MainMenu::Handle_DownInput(CallbackContext Context)
{
	if (!Context.Started) { return; }
	NavigateNext();
}

void UI_MainMenu::Handle_Select(CallbackContext Context)
{
	if (!Context.Started) { return; }
	GameLevel* LoadLevel;;
	switch (m_NavigationIndex)
	{
	case 0:
		LoadLevel = new GameLevel();
		GameInstance::GetGameInstance()->LoadScene(LoadLevel);
		break;
	case 1: 
		GameInstance::GetGameInstance()->CloseGame();
		break;
	default:
		break;
	}
}
