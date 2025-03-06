#pragma once
#include "Transform.h"

SinStr::Transform::Transform(Math::Vector2 SetLocation,
	Math::Vector2 SetScale, float SetRotation)
{
	Location = SetLocation;
	Scale = SetScale;
	Rotation = SetRotation;
}



