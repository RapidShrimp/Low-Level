#pragma once
#include "Engine/UI_Core.h"
#include "UI_PauseMenu.h"

UI_PauseMenu::UI_PauseMenu()
{
	/*Pause Init*/
	m_BlinkTimer = new Timer(0.5f, true, 0, true);

	m_PauseText = new UI_Text("GAME PAUSED", "Assets/Fonts/sinistar.ttf", 24);
	m_PauseText->m_Transform.Location = { WINDOW_WIDTH / 2,(WINDOW_HEIGHT / 2) };
	m_PauseText->SetAlignment(E_TextAlignment::Center);
	m_PauseText->Deactivate();

	m_PausePrompt = new UI_Text("PRESS 'Esc' TO CONTINUE", "Assets/Fonts/sinistar.ttf", 24);
	m_PausePrompt->m_Transform.Location = { WINDOW_WIDTH / 2,(WINDOW_HEIGHT / 2) + 32 };
	m_PausePrompt->SetAlignment(E_TextAlignment::Center);
	m_PausePrompt->Deactivate();
}


void UI_PauseMenu::Init(Object* OwningObject)
{
	UI_Base::Init(OwningObject);
	AddElement(m_PauseText, false);
	AddElement(m_PausePrompt, false);

	m_BlinkTimer->OnTimerCompleted += std::bind(&UI_PauseMenu::Handle_BlinkTimerTrigger, this);
}

void UI_PauseMenu::OnActivate()
{
	ShowPauseMenu();
}

void UI_PauseMenu::OnDeactivate()
{
	HidePauseMenu();
}

void UI_PauseMenu::Render(sf::RenderWindow& Renderer)
{
	if (!isActive) { return; }
	sf::RectangleShape ScreenBackground = sf::RectangleShape({ WINDOW_WIDTH,WINDOW_HEIGHT });
	ScreenBackground.setFillColor(sf::Color::Black);
	Renderer.draw(ScreenBackground);
	UI_Base::Render(Renderer);
}

void UI_PauseMenu::Handle_BlinkTimerTrigger()
{
	sf::Color CurrColour = m_PausePrompt->GetColour();
	sf::Color NextColour = CurrColour == sf::Color::Blue ? sf::Color::Yellow : sf::Color::Blue;
	m_PausePrompt->SetColour(NextColour);
	m_PauseText->SetColour(NextColour);
}


void UI_PauseMenu::ShowPauseMenu()
{
	m_BlinkTimer->StartTimer();
	m_PauseText->Activate();
	m_PausePrompt->Activate();
}

void UI_PauseMenu::HidePauseMenu()
{
	m_BlinkTimer->PauseTimer();
	m_PauseText->Deactivate();
	m_PausePrompt->Deactivate();

}