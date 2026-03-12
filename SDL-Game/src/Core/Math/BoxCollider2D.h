#ifndef BOXCOLLIDER2D_H
#define BOXCOLLIDER2D_H

#include "DataTypes.h"
#include "Vector2D.h"

struct BoxCollider2D
{
	Vec2D centerPos, halfExtents;

	BoxCollider2D();
	BoxCollider2D(FLOAT32 centerX, FLOAT32 centerY, FLOAT32 halfWidth, FLOAT32 halfHeight);
	BoxCollider2D(Vec2D _centerPos, Vec2D _halfExtents);
	BoxCollider2D(const BoxCollider2D& other);
	BoxCollider2D(BoxCollider2D&& other) noexcept;

	// Top left point
	Vec2D LowerBounds() const;
	// Bottom right point
	Vec2D UpperBounds() const;

	bool IsPointWithinBounds(Vec2D point) const;
	bool IsCollidingWith(const BoxCollider2D& other) const;
};
#endif // !BOXCOLLIDER_H
