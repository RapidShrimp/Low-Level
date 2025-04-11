#pragma once
#include "SFML/Graphics.hpp"
#include "Engine/Core/GameInstance.h"
#include "UI_HUD.h"

UI_HUD::UI_HUD(PlayerCharacter& Player)
{
	Player.OnSinibombUpdated += std::bind(&UI_HUD::Handle_OnUpdateSinibombs, this, std::placeholders::_1);
	Player.OnScoreUpdated += std::bind(&UI_HUD::Handle_OnUpdateScore, this, std::placeholders::_1);

	m_ScoreRenderer = new UI_Text("00000", "Assets/Fonts/sinistar.ttf",12);
	m_ActionRenderer = new UI_Text("Action Here", "Assets/Fonts/sinistar.ttf", 12);
	//m_Sinibombs = new SpriteRenderer()

}

void UI_HUD::Init(Object* OwningObject)
{
	Object::Init(OwningObject);
	AddElement(m_ScoreRenderer);
}

void UI_HUD::Render(sf::RenderWindow& Renderer)
{
	//m_Transform = static_cast<GameObject*>(GetOwner())->m_Transform;
	//sf::Vector2i CamCenter = GameInstance::GetGameInstance()->GetCamera().getCenter();
	//Math::Vector2 TopL = { CamCenter.x,CamCenter.y };

	//m_Transform.SetPosition(CamCenter.x, CamCenter.y);
	UI_Base::Render(Renderer);
}

void UI_HUD::Handle_OnUpdateSinibombs(int NewBombCount)
{
	
}

void UI_HUD::Handle_OnUpdateScore(int NewScore)
{
	m_ScoreRenderer->UpdateText(std::to_string(NewScore));
}
