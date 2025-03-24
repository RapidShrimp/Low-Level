#pragma once
#include "UI_Text.h"

UI_Text::UI_Text(std::string DisplayText, std::string FontFilepath, int TextScale)
{
	RenderText = DisplayText;
	sf::Font font;
	if (!font.openFromFile(FontFilepath))
	{
		// error...
		
		return;
	}
	m_Text = new sf::Text(font,"Unknown", TextScale);
	/*m_Text->setString(L"What" );
	m_Text->setCharacterSize(TextScale);
	m_Text->setStyle(sf::Text::Regular);*/

}

void UI_Text::Render(sf::RenderWindow& Renderer)
{
	if (m_Text == nullptr) { return; }
	//TODO - SFML Tweaks out when trying to render this lmao;
	//Renderer.draw(*m_Text);
}

void UI_Text::UpdateText(std::string NewString, sf::Text::Style InStyle)
{
	m_Text->setString(NewString);
	m_Text->setStyle(InStyle);
}

void UI_Text::SetColour(sf::Color NewColour)
{
}
