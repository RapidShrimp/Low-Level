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


	if (m_Sprite == nullptr) 
	{
		Debug::Log(this, E_LogType::Error, "No Sprite Found");
		return;
	}

	Renderer.draw(*m_Sprite);

	return;
	//TODO - Move the texture loading out of Render()
	const sf::Image PackagedSheetCharacter("Assets/SinistarSprites.jpg");
	bool Result = m_Texture.loadFromImage(PackagedSheetCharacter, true, sf::IntRect({0,0}, {32,32}));
	
	if (Result) 
	{
		sf::Sprite ShowSprite(m_Texture);
		ShowSprite.setPosition(LocalTransform.Location.ToSF());
	}
	//Intexture.setSmooth(true);
	//SinStr::Transform RenderTransform = SinStr::Transform(GetOwner()->m_Transform + LocalTransform);
	//Intexture.setPosition(sf::Vector2f(RenderTransform.Location.x, RenderTransform.Location.y));
	//sf::Sprite TestSprite(Intexture);
	
	//Renderer.draw(m_Sprite);
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


