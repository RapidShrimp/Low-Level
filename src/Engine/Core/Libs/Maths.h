#pragma once
#include <ostream>
#include <SFML/System/Vector2.hpp>
using namespace std;

namespace Math {
	//Vector Maths

	static class Random 
	{
	public:
		static int Range(int Min, int Max);
		static float Range(float Min, float Max);

	};

	class Vector2
	{

	public:
		float x = 0.0f;
		float y = 0.0f;

		//Default Constructors
		Vector2() {
			x = 0;
			y = 0;
		};

		Vector2(float XValue, float YValue)
		{
			x = XValue;
			y = YValue;
		};
		~Vector2() {};

		//Operator Functions Functions
		Vector2 operator+(const Vector2& Vector);
		Vector2 operator-(const Vector2& Vector);
		Vector2 operator*(const Vector2& Vector);
		Vector2 operator/(const Vector2& Vector);
		Vector2 operator+=(const Vector2& Vector);
		Vector2 operator-=(const Vector2& Vector);

		void operator=(const Vector2& Vector);
		Vector2 operator*(const float Vector);
		Vector2 operator/(const float Vector);
		Vector2 operator*=(const float rhsFloat);
		Vector2 operator/=(const float rhsFloat);




		bool operator==(const Vector2& Vector);
		bool operator!=(const Vector2& Vector);


		//Vector Functions 
		void Abs();
		static void Normalise(Vector2& InVector);
		Vector2 Normalised();

		float GetRadians();
		float Rad2Deg(float Radians);
		float Length();

		//Screen Log Statement
		friend ostream& operator<<(ostream&, const Vector2& Vector);
		
		static Vector2 Zero() { return Vector2(0, 0); }
		static Vector2 One() { return Vector2(1, 1); }
		static Vector2 Up() { return Vector2(0, 1); }
		static Vector2 Right() { return Vector2(1, 0); }
		static Vector2 Left() { return Vector2(-1, 0); }
		static Vector2 Down() { return Vector2(0, -1); }
		std::string ToString();
		sf::Vector2f ToSF() { return sf::Vector2f(x, y); }

	};

}
