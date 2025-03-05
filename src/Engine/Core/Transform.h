#pragma once
#include "Libs/Maths.h"
#include <Engine/Core/Component.h>

namespace SinStr {

struct Transform
{
	Transform(Math::Vector2 SetLocation = Math::Vector2(0,0), Math::Vector2 SetScale = Math::Vector2(1, 1), float SetRotation = 0);

	protected:
		Math::Vector2 Location = Math::Vector2(0,0);
		Math::Vector2 Scale = Math::Vector2(1,1);
		float Rotation = 0;

	public:
		Math::Vector2 GetLocation();
		Math::Vector2 GetScale();
		float GetRotation();
};

}