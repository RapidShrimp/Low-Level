#pragma once
#include "Engine/Core/Components/Component.h"

class SpriteRenderer : public Component
{
	
protected:

	sf::Texture m_Texture;
	sf::Sprite* m_Sprite;

	//Sprite sheet specifics
	unsigned int m_Row = 0;
	unsigned int m_Column = 0;

	Math::Vector2 m_CellSize = { 0,0 };
	Math::Vector2 m_SpriteSheetStart = { 0,0 };


public:
	SpriteRenderer(std::string ImageFilepath, Math::Vector2(ImageSize)); //Single Image Constructor
	SpriteRenderer(std::string SpriteSheetFilepath, Math::Vector2(SheetSize),Math::Vector2(SheetStart),int Columns = 1,int Rows = 1); //Spritesheet Constructor
	void SetSprite(int Row, int Column);
	const Math::Vector2 GetSpriteIndexes() { return Math::Vector2(m_Row, m_Column); }
	virtual void BeginPlay() override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void Render(sf::RenderWindow& Renderer) override;
	virtual void OnDestroy() override;


	void UpdateSpriteBounds();

	sf::Texture LoadTextureFromFile(std::string Filename);
};