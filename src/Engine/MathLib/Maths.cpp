
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

Vector2 Vector2::operator/(const Vector2& Vector)
{
	return Vector2(x/Vector.x,y/Vector.y);
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
	// TODO: insert return statement here
}
