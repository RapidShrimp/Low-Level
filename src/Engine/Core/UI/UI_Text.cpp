#pragma once
#include "UI_Text.h"
#include "Engine/Core/Libs/GameFunctionLib.h"

UI_Text::UI_Text(std::string DisplayText, std::string FontFilepath, int TextScale)
{
	RenderText = DisplayText;
	m_Font = new sf::Font();
	if (!m_Font->openFromFile(FontFilepath))
	{
		// error...
		Debug::Log(nullptr, Error, "No Font Found");
		return;
	}
	m_Text = new sf::Text(*m_Font);

	m_Text->setString("HelloWorld");

	m_Text->setCharacterSize(24);

	m_Text->setFillColor(sf::Color::Blue);

	m_Text->setStyle(sf::Text::Bold);
	//Debug::Log(this, Warning, "Font Found!");

}

void UI_Text::Render(sf::RenderWindow& Renderer)
{
	if (m_Text == nullptr || !isActive) { return; }
	m_Text->setPosition(m_Transform.Location.ToSF());
	Renderer.draw(*m_Text);
}

void UI_Text::UpdateText(std::string NewString, sf::Text::Style InStyle)
{
	m_Text->setString(NewString);
	m_Text->setStyle(InStyle);
}

void UI_Text::SetColour(sf::Color NewColour)
{
}
