#pragma once
#include "Engine/Core/GameObject.h"
#include "SFML/Graphics.hpp"

class UI_Element : public GameObject {

public:
	
	virtual void OnSetFocus() {};
	virtual void OnRemoveFocus() {};
	virtual void Render(sf::RenderWindow& Renderer) override;

};