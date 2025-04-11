#pragma once
#include "Engine/Core/UI/UI_Element.h"
#include "Engine/Core/UI/UI_Text.h"


enum E_TextAlignment {
	Left,
	Center,
	Right
};

class UI_Text : public UI_Element {

public:
	UI_Text(std::string DisplayText, std::string FontFilepath = "", int TextScale = 24);
	
	virtual void Render(sf::RenderWindow& Renderer) override;
	
	
	void UpdateText(std::string NewString, sf::Text::Style InStyle = sf::Text::Regular);
	void SetColour(sf::Color NewColour);
	void SetAlignment(E_TextAlignment AlignText);
	virtual void OnSetFocus() override;
	virtual void OnRemoveFocus() override;

protected:
	std::string RenderText;
	sf::Font* m_Font;
	sf::Text* m_Text;


};