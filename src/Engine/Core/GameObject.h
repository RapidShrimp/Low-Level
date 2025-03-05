#pragma once
#include "Object.h"
#include "Transform.h"
#include "Libs/Maths.h"


class GameObject : public Object
{
	class Component;


protected:
	
	vector<Component*> Components;
	SinStr::Transform m_Transform;
	//Texture2D* Sprite
	//SpriteRenderer
public:

	virtual void Init();
	virtual void OnActivate();
	virtual void OnDeactivate();
	virtual void BeginPlay();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void Render(sf::RenderWindow& Renderer);
	virtual void OnDestroy();


};