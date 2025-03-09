#pragma once
#include "Transform.h"

SinStr::Transform::Transform(Math::Vector2 SetLocation,
	Math::Vector2 SetScale, float SetRotation)
{
	Location = SetLocation;
	Scale = SetScale;
	Rotation = SetRotation;
}

SinStr::Transform SinStr::Transform::operator+(const SinStr::Transform& rhs_Tranform)
{
	Location += rhs_Tranform.Location;
	Scale += rhs_Tranform.Scale;
	Rotation += rhs_Tranform.Rotation;
	return SinStr::Transform();
}



