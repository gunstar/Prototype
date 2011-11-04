/*
	enF4 represents a 4D float vector.
*/

#ifndef _enF4
#define	_enF4

#include "enF3.h"

class enF4
{
public:
			enF4		() : X(0), Y(0), Z(0), W(0)						{}
			enF4		(float x, float y, float z, float w)			{ X = x; Y = y; Z = z; W = w; }

	void	addSet		(enF4& l, enF4& r)								{ X = l.X + r.X; Y = l.Y + r.Y; Z = l.Z + r.Z; W = l.W + r.W; }
	void	clamp		(float min, float max);
	void	scale		(float s)										{ X *= s; Y *= s; Z *= s; W *= s; }
	void	set			(const enF3& v)									{ X = v.X; Y = v.Y; Z = v.Z; }
	void	set			(const enF3& v, float w)						{ X = v.X; Y = v.Y; Z = v.Z; W = w; }
	void	set			(float x, float y, float z, float w)			{ X = x; Y = y; Z = z; W = w; }
	void	set0		()												{ X = Y = Z = W = 0; }
	void	setDelta	(const enF4& from, const enF4& to, float delta) { X = from.X + delta * (to.X - from.X); Y = from.Y + delta * (to.Y - from.Y); Z = from.Z + delta * (to.Z - from.Z); W = from.W + delta * (to.W - from.W); }

public:
	float	X, Y, Z, W;
};

#endif
