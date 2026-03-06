#define _USE_MATH_DEFINES

#include "Vector2.h"
#include <utility>
#include <cmath>

Vector2::Vector2() : x(0.0f), y(0.0f) { }

Vector2::Vector2(float x1, float y1) : x(x1), y(y1) { }

Vector2::Vector2(const Vector2& other) : x(other.x), y(other.y) { }

Vector2::Vector2(Vector2&& other) noexcept : x(std::exchange(other.x, 0.0f)), y(std::exchange(other.y, 0.0f)) { }

float Vector2::SqrMagnitude() const { return x * x + y * y; }

float Vector2::Magnitude() const { return sqrt(x * x + y * y); }

Vector2 Vector2::Normalised() const { return Vector2(x / Magnitude(), y / Magnitude()); }

Vector2& Vector2::Normalise()
{
	float x2 = x / Magnitude();
	float y2 = y / Magnitude();
	x = x2;
	y = y2;
	return *this;
}

Vector2 Vector2::Rotated(float degrees) const
{
	float radians = degrees * M_PI / 180.0f;
	float x2 = cos(radians) * x - sin(radians) * y;
	float y2 = sin(radians) * x + cos(radians) * y;
	return Vector2(x2, y2);
}

Vector2& Vector2::Rotate(float degrees)
{
	float radians = degrees * M_PI / 180.0f;
	float x2 = cos(radians) * x - sin(radians) * y;
	float y2 = sin(radians) * x + cos(radians) * y;
	x = x2;
	y = y2;
	return *this;
}

float Vector2::Dot(const Vector2& a, const Vector2& b) { return a.x * b.x + a.y * b.y; }

float Vector2::Cross(const Vector2& a, const Vector2& b) { return (a.x * b.y) - (a.y * b.x); }

float Vector2::Get(int index) const
{
	if (index == 0) return x;
	else if (index == 1) return y;
	else throw new std::out_of_range("Index out of range. Index needs to be 0 for x or 1 for y");
}

float& Vector2::Get(int index)
{
	if (index == 0) return x;
	else if (index == 1) return y;
	else throw new std::out_of_range("Index out of range. Index needs to be 0 for x or 1 for y");
}
