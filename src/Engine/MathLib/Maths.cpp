#include "Engine/MathLib/Maths.h"

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

Vector2 Vector2::operator/(const Vector2& Vector)
{
	return Vector2(x/Vector.x,y/Vector.y);
}

Vector2 Vector2::operator/(const float fValue)
{
	return Vector2(x / fValue, y / fValue);
}

bool Vector2::operator==(const Vector2& Vector)
{
	if (Vector.x != x || Vector.y != y) { return false; }
	return true;
}


ostream& operator<<(ostream& os, const Vector2& Vector)
{
	os << "X:" << Vector.x << " Y:" << Vector.y;
	return os;
}

void Vector2::Abs()
{
	x = std::abs(x);
	y = std::abs(y);
}

float Vector2::Length()
{
	return std::sqrt(x * x + y * y);
}

void Vector2::Normalise(Vector2& InVector)
{
	InVector = InVector / InVector.Length();
}
