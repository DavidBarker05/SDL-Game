#define _USE_MATH_DEFINES

#include "Vector2.h"
#include <utility>
#include "MinimalMath.h"

Vector2::Vector2() : x(0.0f), y(0.0f) { }

Vector2::Vector2(FLOAT32 x1, FLOAT32 y1) : x(x1), y(y1) { }

Vector2::Vector2(const Vector2& other) : x(other.x), y(other.y) { }

Vector2::Vector2(Vector2&& other) noexcept : x(std::exchange(other.x, 0.0f)), y(std::exchange(other.y, 0.0f)) { }

FLOAT32 Vector2::SqrMagnitude() const { return x * x + y * y; }

FLOAT32 Vector2::Magnitude() const { return Math::Sqrt(x * x + y * y); }

Vector2 Vector2::Normalised() const { return Vector2(x / Magnitude(), y / Magnitude()); }

Vector2& Vector2::Normalise()
{
	FLOAT32 x2 = x / Magnitude();
	FLOAT32 y2 = y / Magnitude();
	x = x2;
	y = y2;
	return *this;
}

Vector2 Vector2::Rotated(FLOAT32 degrees) const
{
	FLOAT32 x2 = Math::CosDeg(degrees) * x - Math::SinDeg(degrees) * y;
	FLOAT32 y2 = Math::SinDeg(degrees) * x + Math::CosDeg(degrees) * y;
	return Vector2(x2, y2);
}

Vector2& Vector2::Rotate(FLOAT32 degrees)
{
	FLOAT32 x2 = Math::CosDeg(degrees) * x - Math::SinDeg(degrees) * y;
	FLOAT32 y2 = Math::SinDeg(degrees) * x + Math::CosDeg(degrees) * y;
	x = x2;
	y = y2;
	return *this;
}

FLOAT32 Vector2::Get(SIZE_T index) const
{
	if (index == 0) return x;
	else if (index == 1) return y;
	else throw new std::out_of_range("Index out of range. Index needs to be 0 for x or 1 for y");
}

FLOAT32& Vector2::Get(SIZE_T index)
{
	if (index == 0) return x;
	else if (index == 1) return y;
	else throw new std::out_of_range("Index out of range. Index needs to be 0 for x or 1 for y");
}

FLOAT32 Vector2::Dot(const Vector2& a, const Vector2& b) { return a.x * b.x + a.y * b.y; }

FLOAT32 Vector2::Cross(const Vector2& a, const Vector2& b) { return (a.x * b.y) - (a.y * b.x); }

FLOAT32 Vector2::SqrDistance(const Vector2& a, const Vector2& b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

FLOAT32 Vector2::Distance(const Vector2& a, const Vector2& b)
{
	return Math::Sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
