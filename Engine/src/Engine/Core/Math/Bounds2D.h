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

    Bounds2D() : Centre(), HalfExtents() { }
    Bounds2D(const Vector2& center, const Vector2& halfExtents) :
        Centre(center), HalfExtents(halfExtents)
    {
    }
    Bounds2D(const Bounds2D& other) : Centre(other.Centre), HalfExtents(other.HalfExtents) { }
    Bounds2D(Bounds2D&& other) noexcept : Centre(other.Centre), HalfExtents(other.HalfExtents)
    {
        other.Centre = Vector2();
        other.HalfExtents = Vector2();
    }

    inline Vector2 LowerBound() const { return Centre - HalfExtents; }
    inline Vector2 UpperBound() const { return Centre + HalfExtents; }

    inline Bounds2D& operator=(const Bounds2D& other)
    {
        Centre = other.Centre;
        HalfExtents = other.HalfExtents;
        return *this;
    }

    inline bool IsPointWithinBounds(const Vector2& point) const
    {
        return LowerBound() <= point && UpperBound() >= point;
    }

    inline bool IsIntersecting(const Bounds2D& other) const
    {
        return IsPointWithinBounds(other.LowerBound()) || IsPointWithinBounds(other.UpperBound());
    }
} BOUNDS2D, B2D;
