#pragma once
#include "SFML/Graphics.hpp"
#include "Engine/Core/GameInstance.h"
#include "UI_HUD.h"

UI_HUD::UI_HUD(PlayerCharacter& Player)
{
	Player.OnSinibombUpdated += std::bind(&UI_HUD::Handle_OnUpdateSinibombs, this, std::placeholders::_1);
	Player.OnScoreUpdated += std::bind(&UI_HUD::Handle_OnUpdateScore, this, std::placeholders::_1);

	
	m_ScoreRenderer = new UI_Text("00000", "Assets/Fonts/sinistar.ttf",12);
	m_ScoreRenderer->m_Transform.Location = { 10,10 };

	


	m_ActionRenderer = new UI_Text("Action Here", "Assets/Fonts/sinistar.ttf", 12);
	m_ActionRenderer->m_Transform.Location = {10, 100};
	//m_Sinibombs = new SpriteRenderer()

}

void UI_HUD::Init(Object* OwningObject)
{
	Object::Init(OwningObject);
	AddElement(m_ScoreRenderer);
	AddElement(m_ActionRenderer);
}

void UI_HUD::Render(sf::RenderWindow& Renderer)
{

	UI_Base::Render(Renderer);
}

void UI_HUD::Handle_OnUpdateSinibombs(int NewBombCount)
{
	
}

void UI_HUD::Handle_OnUpdateScore(int NewScore)
{
	m_ScoreRenderer->UpdateText(std::to_string(NewScore));
}
