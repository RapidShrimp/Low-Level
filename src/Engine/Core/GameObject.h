#pragma once
#include "Object.h"

#include "Engine/MathLib/Maths.h"

class Component;
class Transform;

class GameObject : Object
{
protected:
	Component* Component;
	Transform ObjectTransform;
	
	//Texture2D* Sprite
	//SpriteRenderer

public:

	virtual void Init() override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void BeginPlay() override;
	virtual void OnDestroy();
	

	Vector2 GetLocation();
	Vector2 GetScale();
	float GetRotation();

};