#include "MinimalMath.h"
#include <cmath>
#include <stdexcept>

FLOAT32 Math::Sqrt(FLOAT32 num)
{
	return std::sqrt(num);
}

FLOAT32 Math::InvSqrt(FLOAT32 num)
{
	return 1.0 / std::sqrt(num);
}

FLOAT32 Math::Pow(FLOAT32 base, FLOAT32 exponent)
{
	return std::pow(base, exponent);
}

INT32 Math::Pow(INT32 base, INT32 exponent)
{
	return std::pow(base, exponent);
}

FLOAT32 Math::Abs(FLOAT32 num)
{
	return std::abs(num);
}

INT32 Math::Abs(INT32 num)
{
	return std::abs(num);
}

FLOAT32 Math::Floor(FLOAT32 num)
{
	return std::floor(num);
}

FLOAT32 Math::Round(FLOAT32 num)
{
	return std::round(num);
}

FLOAT32 Math::Round(FLOAT32 num, INT32 decimalPlaces)
{
	INT32 decimalShift = Pow(10, decimalPlaces);
	return std::round(num * decimalShift) / (FLOAT32) decimalShift;
}

FLOAT32 Math::Ceil(FLOAT32 num)
{
	return std::ceil(num);
}

FLOAT32 Math::Min(FLOAT32 num1, FLOAT32 num2)
{
	return std::fmin(num1, num2);
}

INT32 Math::Min(INT32 num1, INT32 num2)
{
	return std::fmin(num1, num2);
}

FLOAT32 Math::Max(FLOAT32 num1, FLOAT32 num2)
{
	return std::fmax(num1, num2);
}

INT32 Math::Max(INT32 num1, INT32 num2)
{
	return std::fmax(num1, num2);
}

FLOAT32 Math::Clamp(FLOAT32 num, FLOAT32 _min, FLOAT32 _max)
{
	if (_min > _max) throw new std::invalid_argument("The minimum value should be less than the maximum value");
	if (num < _min) return _min;
	else if (num > _max) return _max;
	else return num;
}

INT32 Math::Clamp(INT32 num, INT32 _min, INT32 _max)
{
	if (_min > _max) throw new std::invalid_argument("The minimum value should be less than the maximum value");
	if (num < _min) return _min;
	else if (num > _max) return _max;
	else return num;
}

FLOAT32 Math::Clamp01(FLOAT32 num)
{
	if (num < 0.0f) return 0.0f;
	else if (num > 1.0f) return 1.0f;
	else return num;
}

FLOAT32 Math::Lerp(FLOAT32 num1, FLOAT32 num2, FLOAT32 alpha)
{
	return num1 * (1 - alpha) + num2 * alpha;
}

FLOAT32 Math::SinDeg(FLOAT32 angleDeg)
{
	return std::sin(angleDeg * DegToRad);
}

FLOAT32 Math::SinRad(FLOAT32 angleRad)
{
	return std::sin(angleRad);
}

FLOAT32 Math::ASinDeg(FLOAT32 _sin)
{
	return std::asin(_sin) * RadToDeg;
}

FLOAT32 Math::ASinRad(FLOAT32 _sin)
{
	return std::asin(_sin);
}

FLOAT32 Math::CosDeg(FLOAT32 angleDeg)
{
	return std::cos(angleDeg * DegToRad);
}

FLOAT32 Math::CosRad(FLOAT32 angleRad)
{
	return std::cos(angleRad);
}

FLOAT32 Math::ACosDeg(FLOAT32 _cos)
{
	return std::acos(_cos) * Math::RadToDeg;
}

FLOAT32 Math::ACosRad(FLOAT32 _cos)
{
	return std::acos(_cos);
}

FLOAT32 Math::TanDeg(FLOAT32 angleDeg)
{
	return std::tan(angleDeg * DegToRad);
}

FLOAT32 Math::TanRad(FLOAT32 angleRad)
{
	return std::tan(angleRad);
}

FLOAT32 Math::ATanDeg(FLOAT32 _tan)
{
	return std::atan(_tan) * RadToDeg;
}

FLOAT32 Math::ATanRad(FLOAT32 _tan)
{
	return std::atan(_tan);
}

FLOAT32 Math::ATan2Deg(FLOAT32 x, FLOAT32 y)
{
	return std::atan2(y, x) * RadToDeg;
}

FLOAT32 Math::ATan2Rad(FLOAT32 x, FLOAT32 y)
{
	return std::atan2(y, x);
}
