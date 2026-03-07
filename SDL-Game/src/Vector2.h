#ifndef VECTOR2_H
#define VECTOR2_H

#include "DataTypes.h"
#include <stdexcept>

struct Vector2
{
	FLOAT32 x, y;

	Vector2();
	explicit Vector2(FLOAT32 x1, FLOAT32 y1);
	Vector2(const Vector2& other);
	Vector2(Vector2&& other) noexcept;

	FLOAT32 SqrMagnitude() const;
	FLOAT32 Magnitude() const;

	Vector2 Normalised() const;
	Vector2& Normalise();

	Vector2 Rotated(FLOAT32 degrees) const;
	Vector2& Rotate(FLOAT32 degrees);


	FLOAT32 Get(SIZE_T index) const;
	FLOAT32& Get(SIZE_T index);

	Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
	Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }

	Vector2 operator*(float scale) const { return Vector2(x * scale, y * scale); }
	Vector2 operator/(float scale) const { return Vector2(x / scale, y / scale); }

	FLOAT32 operator[](SIZE_T index) const
	{
		if (index == 0) return x;
		else if (index == 1) return y;
		else throw new std::out_of_range("Index out of range. Index needs to be 0 for x or 1 for y");
	}
	FLOAT32& operator[](SIZE_T index)
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

	Vector2& operator*=(FLOAT32 scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}
	Vector2& operator/=(FLOAT32 scale)
	{
		x /= scale;
		y /= scale;
		return *this;
	}

	static FLOAT32 Dot(const Vector2& a, const Vector2& b);
	static FLOAT32 Cross(const Vector2& a, const Vector2& b);

	static FLOAT32 SqrDistance(const Vector2& a, const Vector2& b);
	static FLOAT32 Distance(const Vector2& a, const Vector2& b);
};
#endif // !VECTOR2_H
