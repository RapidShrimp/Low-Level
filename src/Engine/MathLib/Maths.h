#include <ostream>
using namespace std;

//Vector Maths

class Vector2 {

public:
	float x = 0.0f;
	float y = 0.0f;

	//Default Constructors
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

	bool operator==(const Vector2& Vector);
	void Abs();
	float Normalise();
	Vector2 GetForwardVector();
	Vector2 GetRightVector();
	friend ostream& operator<<(ostream&, const Vector2& Vector);
	float DotProduct(Vector2& VectorB);
	static float DotProduct(Vector2& VecA,Vector2& VecB);

};
