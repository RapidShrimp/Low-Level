#pragma once
#include "UI_LostLife.h"

UI_LostLife::UI_LostLife()
{
 	m_ScreenTimer = GameInstance::GetWorld()->CreateTimer(5.0f, false,false, 0, true);

	m_LifePrompt = new UI_Text("GAME PAUSED", "Assets/Fonts/sinistar.ttf", 24);
	m_LifePrompt->m_Transform.Location = { WINDOW_WIDTH / 2,(WINDOW_HEIGHT / 2) };
	m_LifePrompt->SetAlignment(E_TextAlignment::Center);

	m_SinistarStateText = new UI_Text("SINISTAR LIVES!", "Assets/Fonts/sinistar.ttf", 24);
	m_SinistarStateText->m_Transform.Location = { WINDOW_WIDTH / 2,(WINDOW_HEIGHT / 2)  + 32};
	m_SinistarStateText->SetColour(sf::Color::Red);
	m_SinistarStateText->SetAlignment(E_TextAlignment::Center);

}

void UI_LostLife::Init(Object* OwningObject)
{
	m_ScreenTimer->OnTimerCompleted.AddListener(this,std::bind(&UI_LostLife::Handle_HideLostLifeMenu, this));
	AddElement(m_LifePrompt);
	AddElement(m_SinistarStateText);
}

void UI_LostLife::OnActivate()
{
	m_ScreenTimer->StartTimer();
	GameInstance::GetGameInstance()->GetWorld()->SetGamePaused(true);

}

void UI_LostLife::OnDeactivate()
{
	m_ScreenTimer->PauseTimer();
	GameInstance::GetGameInstance()->GetWorld()->SetGamePaused(false);

}

void UI_LostLife::Render(sf::RenderWindow& Renderer)
{
	if (!isActive) { return; }

	sf::RectangleShape Background({ WINDOW_WIDTH, WINDOW_HEIGHT });
	Background.setFillColor(sf::Color::Black);
	Renderer.draw(Background);
	UI_Base::Render(Renderer);
}

void UI_LostLife::Handle_HideLostLifeMenu()
{
	Debug::Log(this, Confirm, "Reset Scene Objects");
	Deactivate();
}
