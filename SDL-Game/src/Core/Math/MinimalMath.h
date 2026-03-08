#ifndef MINIMALMATH_H
#define MINIMALMATH_H

#include "DataTypes.h"

namespace Math
{
	constexpr FLOAT32 Pi = 3.1415927f;
	constexpr FLOAT32 RadToDeg = (FLOAT32) 180.0f / Pi;
	constexpr FLOAT32 DegToRad = Pi / 180.0f;

	FLOAT32 Sqrt(FLOAT32 num);
	FLOAT32 InvSqrt(FLOAT32 num);

	FLOAT32 Pow(FLOAT32 base, FLOAT32 exponent);
	INT32 Pow(INT32 base, INT32 exponent);

	FLOAT32 Abs(FLOAT32 num);
	INT32 Abs(INT32 num);

	FLOAT32 Floor(FLOAT32 num);
	FLOAT32 Round(FLOAT32 num);
	FLOAT32 Round(FLOAT32 num, INT32 decimalPlaces);
	FLOAT32 Ceil(FLOAT32 num);

	FLOAT32 Min(FLOAT32 num1, FLOAT32 num2);
	INT32 Min(INT32 num1, INT32 num2);
	FLOAT32 Max(FLOAT32 num1, FLOAT32 num2);
	INT32 Max(INT32 num1, INT32 num2);

	FLOAT32 Clamp(FLOAT32 num, FLOAT32 _min, FLOAT32 _max);
	INT32 Clamp(INT32 num, INT32 _min, INT32 _max);
	FLOAT32 Clamp01(FLOAT32 num);

	FLOAT32 Lerp(FLOAT32 num1, FLOAT32 num2, FLOAT32 alpha);

	FLOAT32 SinDeg(FLOAT32 angleDeg);
	FLOAT32 SinRad(FLOAT32 angleRad);

	FLOAT32 ASinDeg(FLOAT32 _sin);
	FLOAT32 ASinRad(FLOAT32 _sin);

	FLOAT32 CosDeg(FLOAT32 angleDeg);
	FLOAT32 CosRad(FLOAT32 angleRad);

	FLOAT32 ACosDeg(FLOAT32 _cos);
	FLOAT32 ACosRad(FLOAT32 _cos);

	FLOAT32 TanDeg(FLOAT32 angleDeg);
	FLOAT32 TanRad(FLOAT32 angleRad);

	FLOAT32 ATanDeg(FLOAT32 _tan);
	FLOAT32 ATanRad(FLOAT32 _tan);

	FLOAT32 ATan2Deg(FLOAT32 x, FLOAT32 y);
	FLOAT32 ATan2Rad(FLOAT32 x, FLOAT32 y);
}


#endif // !MINIMALMATH_H
