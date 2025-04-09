#pragma once
#include "Engine/Core/Components/Component.h"

class SpriteRenderer : public Component
{
	
protected:

	sf::Texture m_Texture;
	sf::Sprite* m_Sprite = nullptr;

	//Sprite sheet specifics
	unsigned int m_Row = 0;
	unsigned int m_Column = 0;

	Math::Vector2 m_CellSize = { 0,0 };
	Math::Vector2 m_SpriteSheetStart = { 0,0 };

	bool bShouldAnimate = false;

public:
	//Spritesheet Constructor
	SpriteRenderer(std::string ImageFilepath, Math::Vector2(ImageSize)); //Single Image Constructor
	SpriteRenderer(std::string SpriteSheetFilepath, Math::Vector2(SheetSize),Math::Vector2(SheetStart),int Columns = 1,int Rows = 1);
	void StartAnimation();

	//Sprite Specifics
	void SetSprite(int Row, int Column);
	void SetSpriteScale(float Width, float Height);

	//Get the current row and column the sprite is on
	const Math::Vector2 GetSpriteIndexes() { return Math::Vector2(m_Row, m_Column); }
	virtual void BeginPlay() override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;

	//Animation Handling
	float LastAnimationFrameTime = 0.0f;
	//Frame animation time in Miliseconds
	float FramesPerSecond = 5;
	virtual void FixedUpdate(float deltaTime) override;

	//Render the sprite to the screen
	virtual void Render(sf::RenderWindow& Renderer) override;
	virtual void OnDestroy() override;

	void UpdateSpriteBounds();
protected:
	void NextAnimationFrame();
	sf::Texture LoadTextureFromFile(std::string Filename);
};