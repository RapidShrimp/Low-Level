#pragma once
#include "Transform.h"

SinStr::Transform::Transform(Math::Vector2 SetLocation,
	Math::Vector2 SetScale, float SetRotation)
{
	Location = SetLocation;
	Scale = SetScale;
	Rotation = SetRotation;
}

Math::Vector2 SinStr::Transform::GetLocation()
{
	return Location;
}

Math::Vector2 SinStr::Transform::GetScale()
{
	return Scale;
}

float SinStr::Transform::GetRotation()
{
	return Rotation;
}


