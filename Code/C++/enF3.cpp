#include "enF3.h"

/*******************************************************************/

void enF3::accelerate(float secs, enF3& v, const enF3& a)
{
// Second order Euler-Cauchy integrator.
// Important: v needs to be updated AFTER X because X uses current v and a.

	X   += v.X * secs + 0.5f * a.X * (secs * secs);
	Y   += v.Y * secs + 0.5f * a.Y * (secs * secs);
	Z   += v.Z * secs + 0.5f * a.Z * (secs * secs);

	v.X += a.X * secs;
	v.Y += a.Y * secs;
	v.Z += a.Z * secs;
}

void enF3::clamp(float min, float max)
{
	X = (X < min) ? min : X;
	Y = (Y < min) ? min : Y;
	Z = (Z < min) ? min : Z;

	X = (X > max) ? max : X;
	Y = (Y > max) ? max : Y;
	Z = (Z > max) ? max : Z;
}

float enF3::clampLength(float max)
{
	float l = length();

	if(l <= max)
		return l;

	setLength(max);

	return max;
}

void enF3::cross(const enF3& v)
{
	float tx = X;
	float ty = Y;
	float tz = Z;

	X = v.Y * tz - v.Z * ty;
	Y = v.Z * tx - v.X * tz;
	Z = v.X * ty - v.Y * tx;
}

void enF3::cross(const enF3& va, const enF3& vb)
{
	X = vb.Y * va.Z - vb.Z * va.Y;
	Y = vb.Z * va.X - vb.X * va.Z;
	Z = vb.X * va.Y - vb.Y * va.X;
}

float enF3::distance(const enF3& v) const
{
	float dx = v.X - X;
	float dy = v.Y - Y;
	float dz = v.Z - Z;

	return sqrtf(dx * dx + dy * dy + dz * dz);
}

float enF3::distanceSqr(const enF3& v) const
{
	float dx = v.X - X;
	float dy = v.Y - Y;
	float dz = v.Z - Z;

	return dx * dx + dy * dy + dz * dz;
}

float enF3::distanceSqrXZ(const enF3& v) const
{
	float dx = v.X - X;
	float dz = v.Z - Z;

	return dx * dx + dz * dz;
}

float enF3::distanceXZ(const enF3& v) const
{
	float dx = v.X - X;
	float dz = v.Z - Z;

	return sqrtf(dx * dx + dz * dz);
}

float enF3::normalize()
{
	float len2 = X * X + Y * Y + Z * Z;

	if(len2 == 0)
		return 0;

	float len = sqrtf(len2);

	X /= len;
	Y /= len;
	Z /= len;

	return len;
}

float enF3::normalizeSet(const enF3& v)
{
	float len2 = v.X * v.X + v.Y * v.Y + v.Z * v.Z;

	if(len2 == 0)
		return 0;

	float len = sqrtf(len2);

	X = v.X / len;
	Y = v.Y / len;
	Z = v.Z / len;

	return len;
}

float enF3::normalizeXZ()
{
	float len2 = X * X + Z * Z;

	if(len2 == 0)
		return 0;

	float len = sqrtf(len2);

	X /= len;
	Y  = 0;
	Z /= len;

	return len;
}

float enF3::normalizeXZSet(const enF3& v)
{
	float len2 = v.X * v.X + v.Z * v.Z;

	if(len2 == 0)
		return 0;

	float len = sqrtf(len2);

	X = v.X / len;
	Y = 0;
	Z = v.Z / len;

	return len;
}

void enF3::rotate(const enF3& axis, float a)
{
	float q1 = cosf(a);
	float q2 = (1 - q1) * (X * axis.X + Y * axis.Y + Z * axis.Z);
	float q3 = sinf(a);

	enF3 q4(axis);

	q4.cross(*this);

	scale(q1);
	scaleAdd(axis, q2);
	scaleAdd(q4, q3);
}

void enF3::rotateSet(const enF3& v, const enF3& axis, float a)
{
	float q1 = cosf(a);
	float q2 = (1 - q1) * (v.X * axis.X + v.Y * axis.Y + v.Z * axis.Z);
	float q3 = sinf(a);

	enF3 q4(axis);

	q4.cross(v);

	scaleSet(v, q1);
	scaleAdd(axis, q2);
	scaleAdd(q4, q3);
}

void enF3::setDir(const enF3& from, const enF3& to)
{
// Sub:

	X = to.X - from.X;
	Y = to.Y - from.Y;
	Z = to.Z - from.Z;

// Normalize:

	float len2 = X * X + Y * Y + Z * Z;

	if(len2 == 0)
		return;

	float len = sqrtf(len2);

	X /= len;
	Y /= len;
	Z /= len;
}

void enF3::setGrid(float grid)
{
// Check grid:

	if(grid <= 0)
		return;

	float grid2	= grid / 2;

// X:

	int		n = (int) (X / grid);
	float	e = X - n * grid;

	if(X >= 0)
		X = (e <=   grid2) ? n * grid : (n + 1) * grid;
	else
		X = (e <= - grid2) ? (n - 1) * grid : n * grid;

// Y:

	n = (int) (Y / grid);
	e = Y - n * grid;

	if(Y >= 0)
		Y = (e <=   grid2) ? n * grid : (n + 1) * grid;
	else
		Y = (e <= - grid2) ? (n - 1) * grid : n * grid;

// Z:

	n = (int) (Z / grid);
	e = Z - n * grid;

	if(Z >= 0)
		Z = (e <=   grid2) ? n * grid : (n + 1) * grid;
	else
		Z = (e <= - grid2) ? (n - 1) * grid : n * grid;
}

void enF3::setLength(float length)
{
	float len2 = X * X + Y * Y + Z * Z;

	if(len2 != 0)
	{
		float mul = length / sqrtf(len2);

		X *= mul;
		Y *= mul;
		Z *= mul;
	}
}

void enF3::setLengthXZ(float length)
{
	float len2 = X * X + Z * Z;

	if(len2 != 0)
	{
		float mul = length / sqrtf(len2);

		X *= mul;
		Y = 0;
		Z *= mul;
	}
}
