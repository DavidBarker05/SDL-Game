#pragma once

#include "Types.h"

typedef struct Vector2
{
	FLOAT32 x, y;

	Vector2() : x(0.0f), y(0.0f) { }
	Vector2(FLOAT32 _x, FLOAT32 _y) : x(_x), y(_y) { }
	Vector2(const Vector2& other) : x(other.x), y(other.y) { }
	Vector2(Vector2&& other) noexcept : x(other.x), y(other.y) { other.x = 0.0f, other.y = 0.0f; }

	inline Vector2& operator=(const Vector2& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	inline bool operator==(const Vector2& other) const { return x == other.x && y == other.y; }
	inline bool operator!=(const Vector2& other) const { return x != other.x && y != other.y; }

	inline bool operator>(const Vector2& other) const { return x > other.x && y > other.y; }
	inline bool operator<(const Vector2& other) const { return x < other.x && y < other.y; }

	inline bool operator>=(const Vector2& other) const { return x >= other.x && y >= other.y; }
	inline bool operator<=(const Vector2& other) const { return x <= other.x && y <= other.y; }

	inline Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
	inline Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y + other.y); }

	inline Vector2 operator*(FLOAT32 scale) const { return Vector2(x * scale, y * scale); }
	inline Vector2 operator/(FLOAT32 scale) const { return Vector2(x / scale, y / scale); }

	inline Vector2 operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	inline Vector2 operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	inline Vector2 operator*=(FLOAT32 scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}
	inline Vector2 operator/=(FLOAT32 scale)
	{
		x /= scale;
		y /= scale;
		return *this;
	}
} Vector2D, Vec2D, Vec2;

