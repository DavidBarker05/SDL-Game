#pragma once

#include "Types.h"
#include "Vector2D.h"

typedef struct Bounds2D
{
    union
    {
        Vector2 Center;
        Vector2 Centre;
    };

    Vector2 HalfExtents;

    Bounds2D() : Centre(), HalfExtents() { };
    Bounds2D(const Bounds2D&) = default;
    Bounds2D(Bounds2D&&) noexcept = default;

    explicit Bounds2D(Vector2 center, Vector2 halfExtents) : Centre(center), HalfExtents(halfExtents) { }

    inline Bounds2D& operator=(const Bounds2D&) = default;
    inline Bounds2D& operator=(Bounds2D&&) noexcept = default;

    inline Vector2 LowerBound() const { return Centre - HalfExtents; }
    inline Vector2 UpperBound() const { return Centre + HalfExtents; }

    inline bool IsPointWithinBounds(Vector2 point) const { return LowerBound() <= point && UpperBound() >= point; }

    inline bool IsIntersecting(Bounds2D other) const
    {
        return IsPointWithinBounds(other.LowerBound()) || IsPointWithinBounds(other.UpperBound());
    }
} BOUNDS2D, B2D;
