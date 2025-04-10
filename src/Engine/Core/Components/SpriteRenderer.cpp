#pragma once
#include "Engine/Core/Libs/GameFunctionLib.h"
#include "Engine/Core/GameInstance.h"
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
	}
}
void SpriteRenderer::StartAnimation()
{
	bShouldAnimate = true;
}

void SpriteRenderer::NextAnimationFrame()
{
	m_Column++;
	if (m_Column+1 * m_CellSize.x > m_Texture.getSize().x) 
	{
		m_Column = 0;
		m_Row++;
	}
	if (m_Row * m_CellSize.y > m_Texture.getSize().y) {
		m_Row = 0;
	}

}

void SpriteRenderer::SetSprite(int Column, int Row)
{
	m_Column = Column;
	m_Row = Row;
}

void SpriteRenderer::SetSpriteScale(float Width, float Height)
{
	m_Sprite->setScale({ Width,Height });
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

void SpriteRenderer::FixedUpdate(float deltaTime)
{
	if(!bShouldAnimate) {return;}
	LastAnimationFrameTime += deltaTime;
	if (LastAnimationFrameTime > 1000 / FramesPerSecond) {return;}

	LastAnimationFrameTime = 0;
 	NextAnimationFrame();
	
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

	UpdateSpriteBounds();
	m_Sprite->setOrigin({ m_CellSize.x / 2,m_CellSize.y / 2 });
	m_Sprite->setScale((GetOwner()->m_Transform.Scale + m_LocalTransform.Scale).ToSF());
	
	//Rotation
	if (GetOwner() != nullptr) {
		m_Sprite->setRotation(sf::Angle(sf::radians(GetOwner()->m_Transform.Rotation + m_LocalTransform.Rotation)));
	}
	else {
		m_Sprite->setRotation(sf::Angle(sf::radians(m_LocalTransform.Rotation)));
	}
	m_Sprite->setPosition({ 
		GetOwner()->m_Transform.Location.x/* + (m_CellSize.x / 2 * m_Sprite->getScale().x)*/ ,
		GetOwner()->m_Transform.Location.y /*+ (m_CellSize.y / 2 * m_Sprite->getScale().y)*/});

	//m_Sprite->setRotation();
	Renderer.draw(*m_Sprite);


	//Debugging
	if (!GameInstance::GetGameInstance()->ShouldDrawDebug()) { return; }
	sf::RectangleShape Rect;
	Rect.setSize(m_CellSize.ToSF());
	Rect.setScale(m_Sprite->getScale());
	Rect.setFillColor(sf::Color::Transparent);
	Rect.setOutlineColor(sf::Color::Cyan);
	Rect.setOutlineThickness(1.0f/m_Sprite->getScale().x);
	Rect.setOrigin({ m_CellSize.x / 2,m_CellSize.y / 2 });
	Rect.setRotation(sf::Angle(sf::radians(GetOwner()->m_Transform.Rotation + m_LocalTransform.Rotation)));
	Rect.setPosition({
		GetOwner()->m_Transform.Location.x /*- (m_CellSize.x / 2) * m_Sprite->getScale().x*/ ,
		GetOwner()->m_Transform.Location.y /*- (m_CellSize.y / 2) * m_Sprite->getScale().y*/ });
	Renderer.draw(Rect);

}

void SpriteRenderer::OnDestroy()
{

}

void SpriteRenderer::UpdateSpriteBounds()
{
	std::string positon = std::to_string(m_Sprite->getTextureRect().position.x) + std::to_string(m_Sprite->getTextureRect().position.y);
	std::string size = std::to_string(m_Sprite->getTextureRect().size.x) + std::to_string(m_Sprite->getTextureRect().size.y);

	int XLocation = ((int)m_CellSize.x) * m_Column;
	int YLocation = ((int)m_CellSize.y) * m_Row;

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


