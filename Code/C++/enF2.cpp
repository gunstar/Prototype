#include "enF2.h"

float enF2::distance(const enF2& v) const
{
	float dx = v.X - X;
	float dy = v.Y - Y;

	return sqrtf(dx * dx + dy * dy);
}

float enF2::distance(const enF2* v) const
{
	float dx = v->X - X;
	float dy = v->Y - Y;

	return sqrtf(dx * dx + dy * dy);
}

float enF2::distanceSqr(const enF2& v) const
{
	float dx = v.X - X;
	float dy = v.Y - Y;

	return dx * dx + dy * dy;
}

float enF2::normalize()
{
	float len2 = X * X + Y * Y;

	if(len2 != 0)
	{
		float div = sqrtf(len2);

		X /= div;
		Y /= div;
	}

	return len2;
}

void enF2::setLength(float length)
{
	float len2 = X * X + Y * Y;

	if(len2 != 0)
	{
		float mul = length / sqrtf(len2);

		X *= mul;
		Y *= mul;
	}
}
