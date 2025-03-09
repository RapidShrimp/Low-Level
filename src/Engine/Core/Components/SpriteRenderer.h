#pragma once
#include "Engine/Core/Components/Component.h"

struct Sprite 
{
protected:
	std::shared_ptr<sf::Texture> m_Texture;
};

class SpriteRenderer : public Component
{
	
protected:



public:
	SpriteRenderer();
	virtual void BeginPlay() override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void Render(sf::RenderWindow& Renderer) override;
	virtual void OnDestroy() override;

	
	sf::Texture LoadTextureFromFile(std::string Filename);
};