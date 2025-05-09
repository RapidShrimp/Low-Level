#pragma once
#include "SFML/Graphics.hpp"
#include "Engine/Core/GameInstance.h"
#include "UI_HUD.h"




UI_HUD::UI_HUD(PlayerCharacter& Player)
{
	Player.OnSinibombUpdated.AddListener(this,std::bind(&UI_HUD::Handle_OnUpdateSinibombs, this, std::placeholders::_1));
	Player.OnScoreUpdated.AddListener(this,std::bind(&UI_HUD::Handle_OnUpdateScore, this, std::placeholders::_1));

	
	GameInstance::GetGameInstance()->GetWorld()->OnPausedChanged.AddListener(this,std::bind(&UI_HUD::Handle_GamePaused, this, std::placeholders::_1));

	m_ScoreRenderer = new UI_Text("00000", "Assets/Fonts/sinistar.ttf",24);
	m_ScoreRenderer->m_Transform.Location = { 10,10 };

	UI_Backing = sf::RectangleShape({ WINDOW_WIDTH,140 });
	UI_Backing.setFillColor(sf::Color(0,47,52));
	UI_Backing.setOutlineColor(sf::Color::Blue);
	UI_Backing.setOutlineThickness(1);
	

	m_ActionRenderer = new UI_Text("Action Here", "Assets/Fonts/sinistar.ttf", 24);
	m_ActionRenderer->m_Transform.Location = {10, 100};
	//m_Sinibombs = new SpriteRenderer()
	m_BombCountRenderer = new UI_Text("Sinibombs: 00", "Assets/Fonts/sinistar.ttf", 24);
	m_BombCountRenderer->m_Transform.Location = { 10, 55 };

	m_PauseMenu = new UI_PauseMenu();
	m_LifeScreen = new UI_LostLife();



}

void UI_HUD::Init(Object* OwningObject)
{
	Object::Init(OwningObject);


	float MinimapWidth = (float)MINIMAP_SCREENSIZE / WINDOW_WIDTH;
	float MinimapHeight = (float)MINIMAP_SCREENSIZE / WINDOW_HEIGHT;


	m_Minimap = sf::View(sf::FloatRect{ {0,0},{MINIMAP_SIZE,MINIMAP_SIZE} });
	m_Minimap.setViewport(sf::FloatRect({ 0.5f - MinimapWidth/2, 0.0f}, { MinimapWidth, MinimapHeight }));
	AddElement(m_ScoreRenderer);
	AddElement(m_BombCountRenderer);
	AddElement(m_ActionRenderer);
	Handle_OnUpdateScore(0);
	Handle_OnUpdateSinibombs(0);

	//Spawn Pause Menu
	//GameInstance::GetGameInstance()->GetWorld()->SpawnUILayer(m_PauseMenu, { 0,0 }, false);
	m_PauseMenu->Init(this);
	m_PauseMenu->Deactivate();

	m_LifeScreen->Init(this);
	m_LifeScreen->Deactivate();
}

void UI_HUD::Render(sf::RenderWindow& Renderer)
{
	m_PauseMenu->Render(Renderer);
	m_LifeScreen->Render(Renderer);
	Renderer.draw(UI_Backing);
	UI_Base::Render(Renderer);
	


	/*Minimap Draw Functionality*/
	//Outline
	sf::RectangleShape MinimapOutline({ 140,140 });
	MinimapOutline.setPosition({ (WINDOW_WIDTH/2)-70,0 });
	MinimapOutline.setFillColor(sf::Color::Black);
	MinimapOutline.setOutlineColor(sf::Color::Blue);
	MinimapOutline.setOutlineThickness(2);
	Renderer.draw(MinimapOutline);

	Renderer.setView(m_Minimap);
	
	Math::Vector2 MinimapLocation = GameInstance::GetGameInstance()->GetPlayer()->m_Transform.Location;
	m_Minimap.setCenter(MinimapLocation.ToSF());

	//Border
	sf::RectangleShape MinimapBorder({ WINDOW_WIDTH,WINDOW_HEIGHT-140});
	MinimapBorder.setOrigin({ WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2 });
	MinimapBorder.setFillColor(sf::Color::Transparent);
	MinimapBorder.setOutlineColor(sf::Color::Blue);
	MinimapBorder.setOutlineThickness(16);
	MinimapBorder.setPosition(MinimapLocation.ToSF());
	Renderer.draw(MinimapBorder);

	std::vector<GameObject*> MinimapItems = GameInstance::GetGameInstance()->GetWorld()->GetGameObjects();
	sf::Color DrawColour;
	for (GameObject * Item : MinimapItems) {
		if (!Item->GetIsActive()) { continue; }
		sf::CircleShape Dot(24);
		Dot.setOrigin({ 12,12 });
		if (Item->m_MinimapDraw == E_DontDraw) { continue; }
		Dot.setPosition(Item->m_Transform.Location.ToSF());

		switch (Item->m_MinimapDraw) 
		{
		case E_Player:
			DrawColour = sf::Color::Blue;
			break;
		case E_Special:
			DrawColour = sf::Color::Yellow;
			break;
		case E_Planetoid:
			DrawColour = sf::Color(144,144,160);
			break;
		case E_SINISTAR:
			Dot.setRadius(100);
			Dot.setOrigin({ 50,50 });
			DrawColour = sf::Color::Red;
			break;
		case E_Enemy:
			Dot.setRadius(20);
			Dot.setOrigin({ 10,10 });
			DrawColour = sf::Color::Red;
			break;
		}
		Dot.setFillColor(DrawColour);
		Renderer.draw(Dot);

	}
	Renderer.setView(Renderer.getDefaultView());
}



void UI_HUD::Handle_OnUpdateSinibombs(int NewBombCount)
{
	m_BombCountRenderer->UpdateText("Sinibombs: " + std::to_string(NewBombCount));

}

void UI_HUD::Handle_OnUpdateScore(int NewScore)
{
	std::ostringstream oss;
	oss << std::setfill('0') << std::setw(7) << NewScore;
	std::string formatted = oss.str();
	m_ScoreRenderer->UpdateText(formatted);
}

void UI_HUD::Handle_GamePaused(bool NewPaused)
{
	if (NewPaused) {
		m_PauseMenu->Activate();
	}
	else {
		m_PauseMenu->Deactivate();
	}
}

