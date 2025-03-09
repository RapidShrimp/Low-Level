#pragma once
#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
{
}

void SpriteRenderer::BeginPlay()
{
}

void SpriteRenderer::OnActivate()
{
	LoadTextureFromFile("Assets/Test.jpg");
}

void SpriteRenderer::OnDeactivate()
{
}

void SpriteRenderer::Render(sf::RenderWindow& Renderer)
{
 	GameObject* Owner = GetOwner();
	if (!Owner || !isActive) { return; }


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

	}
	return sf::Texture();
}


