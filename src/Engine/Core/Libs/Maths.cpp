#include "Maths.h"
Math::Vector2 Math::Vector2::operator+(const Math::Vector2& Vector)
{
	return Math::Vector2(x + Vector.x,y + Vector.y);
}

Math::Vector2 Math::Vector2::operator-(const Math::Vector2& Vector)
{
	return Math::Vector2(x-Vector.x,y-Vector.y);
}

Math::Vector2 Math::Vector2::operator*(const Math::Vector2& Vector)
{
	return Math::Vector2(x* Vector.x,y*Vector.y);
}

Math::Vector2 Math::Vector2::operator/(const Math::Vector2& Vector)
{
	return Math::Vector2(x/Vector.x,y/Vector.y);
}

Math::Vector2 Math::Vector2::operator/(const float fValue)
{
	return Math::Vector2(x / fValue, y / fValue);
}

bool Math::Vector2::operator==(const Math::Vector2& Vector)
{
	if (Vector.x != x || Vector.y != y) { return false; }
	return true;
}


ostream& operator<<(ostream& os, const Math::Vector2& Vector)
{
	os << "X:" << Vector.x << " Y:" << Vector.y;
	return os;
}

void Math::Vector2::Abs()
{
	x = std::abs(x);
	y = std::abs(y);
}

float Math::Vector2::Length()
{
	return std::sqrt(x * x + y * y);
}

void Math::Vector2::Normalise(Math::Vector2& InVector)
{
	InVector = InVector / InVector.Length();
}
