#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer(std::string SpriteSheetFilepath)
{
	const sf::Image SpriteSheet(SpriteSheetFilepath);
	bool Result = m_Texture.loadFromImage(SpriteSheet, true, sf::IntRect({ 0,0 }, { 32,32 }));
	if (Result) 
	{
		m_Sprite = new sf::Sprite(m_Texture);
	}
}

void SpriteRenderer::BeginPlay()
{
}

void SpriteRenderer::OnActivate()
{

}

void SpriteRenderer::OnDeactivate()
{
}

void SpriteRenderer::Render(sf::RenderWindow& Renderer)
{
 	GameObject* Owner = GetOwner();
	if (!Owner || !isActive) { return; }

	//Exit out of render loop if no sprite is found (This will cause Assertion Error if left unchecked
	if (m_Sprite == nullptr) 
	{
		Debug::Log(this, E_LogType::Error, "No Sprite Found");
		return;
	}

	Renderer.draw(*m_Sprite);

	return;
}

void SpriteRenderer::OnDestroy()
{
}

sf::Texture SpriteRenderer::LoadTextureFromFile(std::string Filename)
{
	sf::Texture texture;
	if (!texture.loadFromFile(Filename, false, sf::IntRect({10, 10}, {32, 32})))
	{
		//Error Here
	}
	return texture;
}


