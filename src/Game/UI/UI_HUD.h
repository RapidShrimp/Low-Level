#pragma once

#include "Engine/Core/UI/UI_Base.h"
#include "Engine/Core/UI/UI_Text.h"
#include "Game/Player/PlayerCharacter.h"
#include "SFML/Graphics.hpp"

enum E_SinistarAction {
	Building,
	EnteringPlanetoids,
	ChargingPlayer
};

class UI_HUD : public UI_Base {

public:
	UI_HUD(PlayerCharacter& Player);
protected:
	int m_Sinibombs = 0;
	int m_Score = 0;
	E_SinistarAction m_CurrentAction;

	UI_Text* m_ScoreRenderer;
	UI_Text* m_ActionRenderer;
	UI_Text* m_BombCountRenderer;


	sf::RectangleShape UI_Backing;
	//Minimap Tracker
	sf::View m_Minimap;
public:
	virtual void Init(Object* OwningObject) override;
	//virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	//virtual void BeginPlay() override;
	//virtual void Update() override;
	//virtual void FixedUpdate(float deltaTime) override;
	virtual void Render(sf::RenderWindow& Renderer) override;
	//virtual void OnDestroy() override;

private:
	void Handle_OnUpdateSinibombs(int NewBombCount);
	void Handle_OnUpdateScore(int NewScore);

};