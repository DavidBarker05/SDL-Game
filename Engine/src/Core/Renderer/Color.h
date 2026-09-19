#pragma once

#include "Types.h"

typedef struct Color
{
    union
    {
        UINT8 r;
        UINT8 R;
        UINT8 red;
        UINT8 Red;
        UINT8 RED;
    };

    union
    {
        UINT8 g;
        UINT8 G;
        UINT8 green;
        UINT8 Green;
        UINT8 GREEN;
    };

    union
    {
        UINT8 b;
        UINT8 B;
        UINT8 blue;
        UINT8 Blue;
        UINT8 BLUE;
    };

    union
    {
        UINT8 a;
        UINT8 A;
        UINT8 alpha;
        UINT8 Alpha;
        UINT8 ALPHA;
    };

    Color() : r(0), g(0), b(0), a(255) { }
    Color(const Color&) = default;
    Color(Color&&) noexcept = default;

    Color(UINT8 red, UINT8 green, UINT8 blue) : r(red), g(green), b(blue), a(255) { }
    Color(UINT8 red, UINT8 green, UINT8 blue, UINT8 alpha) : r(red), g(green), b(blue), a(alpha) { }
    Color(UINT8 value) : r(value), g(value), b(value), a(255) { }

    inline Color& operator=(const Color&) = default;
    inline Color& operator=(Color&&) noexcept = default;

    inline Color& operator=(const UINT8 value)
    {
        r = value;
        g = value;
        b = value;
        a = 255;
        return *this;
    }

    inline bool operator==(Color other) const { return r == other.r && g == other.g && b == other.b && a == other.a; }
    inline bool operator!=(Color other) const
    {
        return !(r == other.r && g == other.g && b == other.b && a == other.a);
    }

    inline Color operator+(Color other)
    {
        UINT8 _r = other.r > 255 - r ? 255 : r + other.r;
        UINT8 _g = other.g > 255 - g ? 255 : g + other.g;
        UINT8 _b = other.b > 255 - b ? 255 : b + other.b;
        UINT8 _a = other.a > 255 - a ? 255 : a + other.a;
        return Color(_r, _g, _b, _a);
    }
    inline Color operator-(Color other)
    {
        UINT8 _r = r < other.r ? 0 : r - other.r;
        UINT8 _g = g < other.g ? 0 : g - other.g;
        UINT8 _b = b < other.b ? 0 : b - other.b;
        UINT8 _a = a < other.a ? 0 : a - other.a;
        return Color(_r, _g, _b, _a);
    }

    inline Color& operator+=(Color other)
    {
        r = other.r > 255 - r ? 255 : r + other.r;
        g = other.g > 255 - g ? 255 : g + other.g;
        b = other.b > 255 - b ? 255 : b + other.b;
        a = other.a > 255 - a ? 255 : a + other.a;
        return *this;
    }
    inline Color& operator-=(Color other)
    {
        r = r < other.r ? 0 : r - other.r;
        g = g < other.g ? 0 : g - other.g;
        b = b < other.b ? 0 : b - other.b;
        a = a < other.a ? 0 : a - other.a;
        return *this;
    }
} Colour;
