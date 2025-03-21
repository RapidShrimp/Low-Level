#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(std::string ImageFilepath, Math::Vector2(ImageSize))
{
	m_CellSize = ImageSize;
	const sf::Image SingleImage(ImageFilepath);
	bool Result = m_Texture.loadFromImage(SingleImage, true, sf::IntRect({ 0,0 }, { (int)ImageSize.x,(int)ImageSize.y }));
	if (Result)
	{
		m_Sprite = new sf::Sprite(m_Texture);
	}
}

SpriteRenderer::SpriteRenderer(std::string SpriteSheetFilepath, Math::Vector2(SheetSize), Math::Vector2(SheetStart), int Columns, int Rows)
{
	const sf::Image SpriteSheet(SpriteSheetFilepath);
	m_CellSize = { SheetSize.x / Columns , SheetSize.y / Rows };

	m_SpriteSheetStart = SheetStart;
	bool Result = m_Texture.loadFromImage(SpriteSheet, true, sf::IntRect({ (int)m_SpriteSheetStart.x,(int)m_SpriteSheetStart.y }, { (int)SheetSize.x,(int)SheetSize.y }));
	if (Result) 
	{
		m_Sprite = new sf::Sprite(m_Texture);
		m_Sprite->setScale({5,5});
	}
}
void SpriteRenderer::SetSprite(int Row, int Column)
{
	m_Column = Column;
	m_Row = Row;
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

	//Exit out of render loop if no sprite is found (This will cause Assertion Error if left unchecked)
	if (m_Sprite == nullptr) 
	{
		Debug::Log(this, E_LogType::Error, "No Sprite Found");
		return;
	}
	//m_Sprite->setTextureRect(sf::IntRect({m_SpriteSheetStart.x+(m_CellSize.x * m_Columns),m_SpriteSheetStart.y + (m_CellSize.y * m_Rows)}, {m_CellSize.x,m_CellSize.y}));
	//Replace 0,0 with half the texture size ( Center Sprite to character transform)
	UpdateSpriteBounds();
	m_Sprite->setScale(m_LocalTransform.Scale.ToSF());
	m_Sprite->setPosition({ GetOwner()->m_Transform.Location.x - (m_Texture.getSize().x/2), GetOwner()->m_Transform.Location.y - (m_Texture.getSize().y/2) });
	Renderer.draw(*m_Sprite);

	return;
}

void SpriteRenderer::OnDestroy()
{
}

void SpriteRenderer::UpdateSpriteBounds()
{
	int XLocation = ((int)m_CellSize.x) * m_Row;
	int YLocation = ((int)m_CellSize.y) * m_Column;

	sf::IntRect NewRect = sf::IntRect({XLocation,YLocation}, { (int)m_CellSize.x,(int)m_CellSize.y });
	m_Sprite->setTextureRect(NewRect);

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


