#include "BoxCollider2D.h"

BoxCollider2D::BoxCollider2D() : centerPos(0.0f, 0.0f), halfExtents(0.0f, 0.0f)
{
}

BoxCollider2D::BoxCollider2D(FLOAT32 centerX, FLOAT32 centerY, FLOAT32 halfWidth, FLOAT32 halfHeight) : centerPos(centerX, centerY), halfExtents(halfWidth, halfHeight)
{
}

BoxCollider2D::BoxCollider2D(Vec2D _centerPos, Vec2D _halfExtents) : centerPos(_centerPos), halfExtents(_halfExtents)
{
}

BoxCollider2D::BoxCollider2D(const BoxCollider2D& other) : centerPos(other.centerPos), halfExtents(other.halfExtents)
{
}

BoxCollider2D::BoxCollider2D(BoxCollider2D&& other) noexcept : centerPos(other.centerPos), halfExtents(other.halfExtents)
{
	other.centerPos = Vec2D();
	other.halfExtents = Vec2D();
}

Vec2D BoxCollider2D::LowerBounds() const
{
	return centerPos - halfExtents;
}

Vec2D BoxCollider2D::UpperBounds() const
{
	return centerPos + halfExtents;
}


bool BoxCollider2D::IsPointWithinBounds(Vec2D point) const
{
	return point >= LowerBounds() && point <= UpperBounds();
}

bool BoxCollider2D::IsCollidingWith(const BoxCollider2D& other) const
{
	return LowerBounds() >= other.LowerBounds() && UpperBounds() <= other.UpperBounds();
}
