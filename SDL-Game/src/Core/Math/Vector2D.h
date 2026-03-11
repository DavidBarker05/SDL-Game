#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "DataTypes.h"

struct Vec2D
{
	FLOAT32 x, y;

	Vec2D() : x(0.0f), y(0.0f) { }
	Vec2D(FLOAT32 _x, FLOAT32 _y) : x(_x), y(_y) { }
	Vec2D(const Vec2D& other) : x(other.x), y(other.y) { }
	Vec2D(Vec2D&& other) noexcept : x(other.x), y(other.y) { other.x = 0.0f, other.y = 0.0f; }

	inline Vec2D& operator=(const Vec2D& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	inline Vec2D operator+(const Vec2D& other) const { return Vec2D(x + other.x, y + other.y); }
	inline Vec2D operator-(const Vec2D& other) const { return Vec2D(x - other.x, y + other.y); }

	inline Vec2D operator*(FLOAT32 scale) const { return Vec2D(x * scale, y * scale); }
	inline Vec2D operator/(FLOAT32 scale) const { return Vec2D(x / scale, y / scale); }

	inline Vec2D operator+=(const Vec2D& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	inline Vec2D operator-=(const Vec2D& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	inline Vec2D operator*=(FLOAT32 scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}
	inline Vec2D operator/=(FLOAT32 scale)
	{
		x /= scale;
		y /= scale;
		return *this;
	}
};
#endif // !VECTOR2D_H
