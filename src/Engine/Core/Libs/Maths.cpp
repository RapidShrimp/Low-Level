#include "Maths.h"
#include <string>
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

Math::Vector2 Math::Vector2::operator+=(const Vector2& Vector)
{
	return Vector2(x+= Vector.x,y+=Vector.y);
}

Math::Vector2 Math::Vector2::operator-=(const Vector2& Vector)
{
	return Vector2(x-=Vector.x,y-=Vector.y);
}

void Math::Vector2::operator=(const Vector2& Vector)
{
	x = Vector.x;
	y = Vector.y;
}

Math::Vector2 Math::Vector2::operator*(const float InFloat)
{
	return Vector2(x*InFloat,y*InFloat);
}

Math::Vector2 Math::Vector2::operator/(const float InFloat)
{
	return Vector2(x / InFloat , y / InFloat);
}

bool Math::Vector2::operator==(const Math::Vector2& Vector)
{
	if (Vector.x != x || Vector.y != y) { return false; }
	return true;
}

bool Math::Vector2::operator!=(const Vector2& Vector)
{
	if (Vector.x != x || Vector.y != y) { return true; }
	return false;

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

std::string Math::Vector2::ToString()
{
	std::string ReturnString = "X: " + std::to_string(x) + " Y: " + std::to_string(y);
	return ReturnString;

}

void Math::Vector2::Normalise(Math::Vector2& InVector)
{
	InVector = InVector / InVector.Length();
}
