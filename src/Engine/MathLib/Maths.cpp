
#include "Maths.h"


Vector2 Vector2::operator+(const Vector2& Vector)
{
	return Vector2(x + Vector.x,y + Vector.y);
}

Vector2 Vector2::operator-(const Vector2& Vector)
{
	return Vector2(x-Vector.x,y-Vector.y);
}

Vector2 Vector2::operator*(const Vector2& Vector)
{
	return Vector2(x* Vector.x,y*Vector.y);
}

bool Vector2::operator==(const Vector2& Vector)
{
	if (Vector.x != x || Vector.y != y) { return false; }
	return true;
}

