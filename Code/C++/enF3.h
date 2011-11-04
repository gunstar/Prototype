/*
	enF3 represents a 3D float vector.
*/

#ifndef _enF3
#define	_enF3

#include <math.h>

class enF3
{
public:
			enF3			()												: X(0), Y(0), Z(0) {}
			enF3			(float x, float y, float z)						: X(x), Y(y), Z(z) {}
			enF3			(float* v)										: X(v[0]), Y(v[1]), Z(v[2]) {}
			enF3			(const enF3& v)									: X(v.X), Y(v.Y), Z(v.Z) {}
			enF3			(const enF3* v)									: X(v->X), Y(v->Y), Z(v->Z) {}
			enF3			(const enF3& from, const enF3& to)				{ X = to.X - from.X; Y = to.Y - from.Y; Z = to.Z - from.Z; }

	void	accelerate		(float secs, enF3& v, const enF3& a);

	void	add				(float x, float y, float z)						{ X += x; Y += y; Z += z; }
	void	add				(const enF3& v)									{ X += v.X; Y += v.Y; Z += v.Z; }
	void	addSet			(const enF3& l, const enF3& r)					{ X = l.X + r.X; Y = l.Y + r.Y; Z = l.Z + r.Z; }
	void	addSet			(const enF3& a, const enF3& b, const enF3& c)	{ X = a.X + b.X + c.X; Y = a.Y + b.Y + c.Y; Z = a.Z + b.Z + c.Z; }

	void	clamp			(float min, float max);
	void	clampInt		()												{ X = (float) (int) X; Y = (float) (int) Y; Z = (float) (int) Z; }
	float	clampLength		(float max);									// == new length.
	void	clampMax		(float max)										{ X = X > max ? max : X; Y = Y > max ? max : Y; Z = Z > max ? max : Z; }

	void	cross			(const enF3& v);								// == cross(this, v)
	void	cross			(const enF3& vx, const enF3& vz);				// cross(xAxis, zAxis) == yAxis

	float	distance		(const enF3& v) const;
	float	distanceSqr		(const enF3& v) const;
	float	distanceSqrXZ	(const enF3& v) const;
	float	distanceXZ		(const enF3& v) const;

	void	div				(float x, float y, float z)						{ X /= x; Y /= y; Z /= z; }
	void	div				(const enF3& v)									{ X /= v.X; Y /= v.Y; Z /= v.Z; }
	void	div				(float v)										{ X /= v; Y /= v; Z /= v; }

	float	dot				(float x, float y, float z) const				{ return X * x + Y * y + Z * z; }
	float	dot				(const enF3& v) const							{ return X * v.X + Y * v.Y + Z * v.Z; }
	float	dotXZ			(const enF3& v) const							{ return X * v.X + Z * v.Z; }

	void	flipYZ			()												{ float tmp = Y; Y = Z; Z = tmp; }
	void	flipYZSet		(const enF3& v)									{ X = v.X; Y = v.Z; Z = v.Y; }

	void	get				(float* dst)									{ dst[0] = X; dst[1] = Y; dst[2] = Z; }
	int		getMaxIndex		()												{ return X >= Y ? (X >= Z ? 0 : 2) : (Y >= Z ? 1 : 2); }
	float	getMin			()												{ return X <= Y ? (X <= Z ? X : Z ) : (Y <= Z ? Y : Z); }

	bool	is0				() const										{ return X == 0 && Y == 0 && Z == 0; }
	bool	isEqual			(const enF3& v) const							{ return X == v.X && Y == v.Y && Z == v.Z; }

	float	length			() const										{ return sqrtf((X * X) + (Y * Y) + (Z * Z)); }
	float	lengthSqr		() const										{ return (X * X) + (Y * Y) + (Z * Z); }
	float	lengthSqr		(const enF3& v)									{ return (X - v.X) * (X - v.X) + (Y - v.Y) * (Y - v.Y) + (Z - v.Z) * (Z - v.Z); }
	float	lengthXZ		() const										{ return sqrtf((X * X) + (Z * Z)); }

	float	maxXYZ			()												{ return X >= Y ? (X >= Z ? X : Z) : (Y >= Z ? Y : Z); }
	float	minXYZ			()												{ return X <= Y ? (X <= Z ? X : Z) : (Y <= Z ? Y : Z); }

	void	negate			()												{ X = - X; Y = - Y; Z = - Z; }
	void	negateSet		(const enF3& v)									{ X = - v.X; Y = - v.Y; Z = - v.Z; }

	float	normalize		();
	float	normalizeSet	(const enF3& v);
	float	normalizeXZ		();
	float	normalizeXZSet	(const enF3& v);

	void	reset			()												{ X = Y = Z = 0; }

	void	rotate			(const enF3& axis, float angle);				// axis = unit vector to rotate about, angle = angle in radians.
	void	rotateSet		(const enF3& v, const enF3& axis, float angle);	// axis = unit vector to rotate about, angle = angle in radians.

	void	scale			(float s)										{ X *= s; Y *= s; Z *= s; }
	void	scale			(float x, float y, float z)						{ X *= x; Y *= y; Z *= z; }
	void	scale			(const enF3& v)									{ X *= v.X; Y *= v.Y; Z *= v.Z; }
	void	scaleAdd		(const enF3& v, float s)						{ X += s * v.X; Y += s * v.Y; Z += s * v.Z; }
	void	scaleAddSet		(const enF3& v, const enF3& w, float s)			{ X = v.X + s * w.X; Y = v.Y + s * w.Y; Z = v.Z + s * w.Z; }
	void	scaleSet		(const enF3& v, float s)						{ X = s * v.X; Y = s * v.Y; Z = s * v.Z; }

	void	set				(float x, float y, float z)						{ X = x; Y = y; Z = z; }
	void	set				(float* p)										{ X = p[0]; Y = p[1]; Z = p[2]; }
	void	set				(const enF3& v)									{ X = v.X; Y = v.Y; Z = v.Z; }
	void	set0			()												{ X = Y = Z = 0; }
	void	setDelta		(const enF3& from, float delta)					{ X = from.X + delta * (X - from.X); Y = from.Y + delta * (Y - from.Y); Z = from.Z + delta * (Z - from.Z); }
	void	setDelta		(const enF3& from, const enF3& to, float delta) { X = from.X + delta * (to.X - from.X); Y = from.Y + delta * (to.Y - from.Y); Z = from.Z + delta * (to.Z - from.Z); }
	void	setDir			(const enF3& from, const enF3& to);
	void	setGrid			(float grid);
	void	setI			(int x, int y, int z)							{ X = (float) x; Y = (float) y; Z = (float) z; }
	void	setLength		(float length);
	void	setLengthXZ		(float length);

	void	sub				(float x, float y, float z)						{ X -= x; Y -= y; Z -= z; }
	void	sub				(const enF3& v)									{ X -= v.X; Y -= v.Y; Z -= v.Z; }
	void	subSet			(const enF3& l, const enF3& r)					{ X = l.X - r.X; Y = l.Y - r.Y; Z = l.Z - r.Z; }

	enF3&	operator=		(const enF3& v)									{ X = v.X; Y = v.Y; Z = v.Z; return *this; }
	bool	operator==		(const enF3& v)									{ return X == v.X && Y == v.Y && Z == v.Z; }
	bool	operator!=		(const enF3& v)									{ return X != v.X || Y != v.Y || Z != v.Z; }

public:
	float	X, Y, Z;
};

#endif
