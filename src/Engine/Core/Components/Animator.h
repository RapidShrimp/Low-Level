#pragma once
#include "Engine/Core/Components/Component.h"
#include <map>

class Animator : Component {
protected:

	//The Animation Sprites
	std::unordered_map<std::string, sf::Sprite> m_SpriteMap;

	SpriteRenderer* _SpriteRenderer;


public:

	Animator(SpriteRenderer& SpriteRenderer);


	//void AddSprite();
	//void 

	//void Init(Object* Owner) override;
	//virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	//virtual void BeginPlay() override;
	//virtual void Update() override;
	//virtual void Render(sf::RenderWindow& Renderer) override;
	//virtual void FixedUpdate(float deltaTime) override;
	//virtual void OnDestroy() override;

};