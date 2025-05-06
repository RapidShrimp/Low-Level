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

	m_Text->setString(DisplayText);

	m_Text->setCharacterSize(TextScale);

	m_Text->setFillColor(sf::Color::Blue);
	
	m_Text->setStyle(sf::Text::Bold);
	m_Text->setLineSpacing(10);
	
	//Debug::Log(this, Warning, "Font Found!");

}

void UI_Text::Render(sf::RenderWindow& Renderer)
{
	if (m_Text == nullptr || !isActive) { return; }

	Math::Vector2 RenderLoc;
	if (GetOwner() != nullptr) 
	{
		RenderLoc = static_cast<GameObject*>(GetOwner())->m_Transform.Location + m_Transform.Location;
	}
	else {
		RenderLoc = m_Transform.Location;
	}
	m_Text->setPosition(RenderLoc.ToSF());
	Renderer.draw(*m_Text);
}

void UI_Text::UpdateText(std::string NewString, sf::Text::Style InStyle)
{
	m_Text->setString(NewString);
	m_Text->setStyle(InStyle);
}

void UI_Text::SetColour(sf::Color NewColour)
{
	if (m_Text == nullptr) { return; }

	m_Text->setFillColor(NewColour);
}

void UI_Text::SetAlignment(E_TextAlignment AlignText)
{

	switch (AlignText)
	{
	case Left:
		m_Text->setOrigin({ 0,0 });
		break;
	case Center:
		m_Text->setOrigin(m_Text->getGlobalBounds().getCenter());
		break;
	case Right:
		m_Text->setOrigin({ m_Text->getGlobalBounds().size.x,0 });
		break;
	default:
		break;
	}
}

void UI_Text::OnSetFocus()
{
	SetColour(sf::Color::White);
}

void UI_Text::OnRemoveFocus()
{
	SetColour(sf::Color::Blue);
}
