#pragma once
#include "Engine/Core/GameObject.h"
#include "Game/UI/UI_Text.h"


class UI_Text : public GameObject {

public:
	UI_Text(std::string DisplayText, std::string FontFilepath = "", int TextScale = 24);
	
	//virtual void Init(Object* OwningObject) override;
	//virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	//virtual void BeginPlay() override;
	//virtual void Update() override;
	//virtual void FixedUpdate(float deltaTime) override;
	virtual void Render(sf::RenderWindow& Renderer) override;
	//virtual void OnDestroy() override;
	
	
	void UpdateText(std::string NewString, sf::Text::Style InStyle = sf::Text::Regular);
	void SetColour(sf::Color NewColour);


protected:
	std::string RenderText;
	sf::Text* m_Text;


};