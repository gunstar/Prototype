/*
	enF2 represents a 2D float vector.
*/

#ifndef _enF2
#define	_enF2

#include <math.h>

class enF2
{
public:
			enF2		()												: X(0), Y(0) {}
			enF2		(float x, float y)								: X(x), Y(y) {}
			enF2		(const enF2& v)									: X(v.X), Y(v.Y) {}
			enF2		(const enF2& from, const enF2& to)				{ X = to.X - from.X; Y = to.Y - from.Y; }

	void	add			(float x, float y)								{ X += x; Y += y; }
	void	add			(const enF2& v)									{ X += v.X; Y += v.Y; }
	void	addSet		(const enF2& l, const enF2& r)					{ X = l.X + r.X; Y = l.Y + r.Y; }

	float	distance	(const enF2& v) const;
	float	distance	(const enF2* v) const;
	float	distanceSqr	(const enF2& v) const;

	void	div			(float x, float y)								{ X /= x; Y /= y; }
	void	div			(const enF2& v)									{ X /= v.X; Y /= v.Y; }

	float	dot			(float x, float y)								{ return X * x + Y * y; }
	float	dot			(const enF2& v)									{ return X * v.X + Y * v.Y; }

	bool	is0			()												{ return X == 0 && Y == 0; }
	bool	isEqual		(const enF2& v)									{ return X == v.X && Y == v.Y; }
	float	length		()												{ return sqrtf((X * X) + (Y * Y)); }
	float	lengthSqr	()												{ return (X * X) + (Y * Y); }
	float	lengthSqr	(const enF2& v)									{ return (X - v.X) * (X - v.X) + (Y - v.Y) * (Y - v.Y); }

	void	mul			(float x, float y)								{ X *= x; Y *= y; }
	void	mul			(const enF2& v)									{ X *= v.X; Y *= v.Y; }
	void	mulAdd		(const enF2& v, float s)						{ X += s * v.X; Y += s * v.Y; }

	void	negate		()												{ X = - X; Y = - Y; }

	float	normalize	();

	void	reset		()												{ X = Y = 0; }

	void	scale		(float s)										{ X *= s; Y *= s; }
	void	scaleSet	(const enF2& v, float s)						{ X = s * v.X; Y = s * v.Y; }
	void	scaleSet	(const enF2& v, const enF2& w, float s)			{ X = v.X + s * w.X; Y = v.Y + s * w.Y; }

	void	set			(float x, float y)								{ X = x; Y = y; }
	void	set			(const enF2& v)									{ X = v.X; Y = v.Y; }
	void	set0		()												{ X = Y = 0; }
	void	setDelta	(const enF2& from, const enF2& to, float delta) { X = from.X + delta * (to.X - from.X); Y = from.Y + delta * (to.Y - from.Y); }
	void	setLength	(float length);

	void	sub			(float x, float y)								{ X -= x; Y -= y; }
	void	sub			(const enF2& v)									{ X -= v.X; Y -= v.Y; }
	void	subSet		(const enF2& l, const enF2& r)					{ X = l.X - r.X; Y = l.Y - r.Y; }

	enF2&	operator=	(const enF2& v)									{ X = v.X; Y = v.Y; return *this; }
	bool	operator==	(const enF2& v) const							{ return X == v.X && Y == v.Y; }

public:
	float	X, Y;
};

#endif
