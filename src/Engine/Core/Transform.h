#pragma once
#include "Libs/Maths.h"

namespace SinStr {
	/**
	* ---Transform Data Struct---
	* Holds Values for;
	* Location - Vector 2
	* Scale - Vector 2
	* Rotation - Float
	**/
struct Transform
{
public:
	Transform(Math::Vector2 SetLocation = Math::Vector2(0,0), Math::Vector2 SetScale = Math::Vector2(1, 1), float SetRotation = 0);

	Math::Vector2 Location = Math::Vector2(0,0);
	Math::Vector2 Scale = Math::Vector2(1,1);
	float Rotation = 0;
	void SetScale(float SizeX, float SizeY) { Scale.x = SizeX; Scale.y = SizeY; };
	void SetPosition(float PosX, float PosY) { Location.x = PosX; Location.y = PosY; };
	void SetRotation(float InRotation) { Rotation = InRotation; };


	SinStr::Transform operator+(const SinStr::Transform& rhs_Tranform);
	SinStr::Transform operator-(const SinStr::Transform& rhs_Tranform);
	SinStr::Transform operator*(const SinStr::Transform& rhs_Tranform);
	SinStr::Transform operator/(const SinStr::Transform& rhs_Tranform);
	SinStr::Transform operator+=(const SinStr::Transform& rhs_Tranform);
	SinStr::Transform operator-=(const SinStr::Transform& rhs_Tranform);
};

}