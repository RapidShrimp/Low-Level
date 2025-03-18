#pragma once
#include "Engine/Core/Components/Component.h"

class SpriteRenderer : public Component
{
	
protected:

	sf::Texture m_Texture;
	sf::Sprite* m_Sprite;

public:
	SpriteRenderer(std::string SpriteSheetFilepath, Math::Vector2(ImageSize));
	virtual void BeginPlay() override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void Render(sf::RenderWindow& Renderer) override;
	virtual void OnDestroy() override;

	sf::Texture LoadTextureFromFile(std::string Filename);
};