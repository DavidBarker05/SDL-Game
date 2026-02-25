#pragma once

#include <stdexcept>

struct Vector2
{
	float x, y;

	Vector2();
	explicit Vector2(float x1, float y1);
	Vector2(const Vector2& other);
	Vector2(Vector2&& other) noexcept;

	float SqrMagnitude() const;
	float Magnitude() const;

	Vector2 Normalised() const;
	Vector2& Normalise();

	Vector2 Rotated(float degrees) const;
	Vector2& Rotate(float degrees);

	static float Dot(const Vector2& a, const Vector2& b);
	static float Cross(const Vector2& a, const Vector2& b);

	float Get(int index) const;
	float& Get(int index);

	Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
	Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }

	Vector2 operator*(float scale) const { return Vector2(x * scale, y * scale); }
	Vector2 operator/(float scale) const { return Vector2(x / scale, y / scale); }

	float operator[](int index) const
	{
		if (index == 0) return x;
		else if (index == 1) return y;
		else throw new std::out_of_range("Index out of range. Index needs to be 0 for x or 1 for y");
	}
	float& operator[](int index)
	{
		if (index == 0) return x;
		else if (index == 1) return y;
		else throw new std::out_of_range("Index out of range. Index needs to be 0 for x or 1 for y");
	}

	Vector2& operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector2& operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2& operator*=(float scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}
	Vector2& operator/=(float scale)
	{
		x /= scale;
		y /= scale;
		return *this;
	}
};

