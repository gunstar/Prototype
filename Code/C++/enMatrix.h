/*
	enMatrix represents a 4x3 float matrix.

	X = X axis   of coordinate system.
	Y = Y axis   of coordinate system.
	Z = Z axis   of coordinate system.
	P = Position of coordinate system.

	enMatrix() initialises the matrix to the identity matrix.

	IMPORTANT: All enMatrix methods assume that length(X/Y/Z) == 1.
*/

#ifndef _enMatrix
#define	_enMatrix

#include "enF3.h"

class enMatrix
{
public:
			enMatrix			();
			enMatrix			(const enMatrix& mat);
			enMatrix			(const enMatrix* mat);

	float	difference			(const enMatrix& other);							// = summary of how different the two matrices are (>= 0).
	float	differenceXYZ		(const enMatrix& other);							// = summary of how different the two matrices are (>= 0).

	void	flipXZ				()													{ X.negate(); Z.negate(); }
	void	flipXZSet			(const enMatrix& other)								{ X.negateSet(other.X); Y = other.Y; Z.negateSet(other.Z); P = other.P; }
	void	flipYZ				();
	void	flipYZScaleP		(float scale);

	void	getScale			(float& sx, float& sy, float& sz)					{ sx = X.length(); sy = Y.length(); sz = Z.length(); }
	float	getScaleMax			();

	void	invert				();													// mat * mat.invert() = mat.invert() * mat = identity
	void	invertSet			(const enMatrix& other);							// mat * mat.invert() = mat.invert() * mat = identity

	bool	isEqual				(const enMatrix& other)								{ return X.isEqual(other.X) && Y.isEqual(other.Y) && Z.isEqual(other.Z) && P.isEqual(other.P); }
	bool	isIdentity			();
	bool	isMirrored			() const;

	void	multiplySet			(const enMatrix& l, const enMatrix& r);				// l transform is applied to enF3 before r when enF3 is transformed (r "happens after" l).
	void	normalize			()													{ X.normalize(); Y.normalize(); Z.normalize(); }
	void	reset				()													{ setIdentity(); }
	void	rotate				(const enF3& axis, float angle);					// axis = unit vector, angle = radians.
	void	scaleXYZ			(float scale)										{ X.scale(scale); Y.scale(scale); Z.scale(scale); }

	void	set					(const enMatrix& mat);
	void	setDelta			(enMatrix* from, float delta);						// this = delta from -> this.
	void	setDelta			(enMatrix* from, enMatrix* to, float delta);		// Normalized X/Y/Z only!
	void	setDeltaXYZ			(enMatrix* from, enMatrix* to, float delta);		// Normalized X/Y/Z only!
	void	setDeltaTransform	(const enMatrix& from, const enMatrix& to);			// => this * from = to (i.e. LEFT multiplied)
	void	setDiagonal			(float x, float y, float z)							{ X.X = x; Y.Y = y; Z.Z = z; }
	void	setIdentity			();
	void	setIdentityXYZ		();
	void	setLookAt			(const enF3& from, const enF3& to);
	void	setLookAt			(const enF3& from, const enF3& to, const enF3& y);
	void	setOrientation		(const enF3& axis, float angle);					// => Matrix X/Y/Z = same effect as rotate around axis(angle)
	void	setScale			(float scale)										{ X.setLength(scale); Y.setLength(scale); Z.setLength(scale); }
	void	setScale			(float sx, float sy, float sz)						{ X.setLength(sx); Y.setLength(sy); Z.setLength(sz); }

	void	transform			(enF3& v) const;
	void	transform			(enF3& dst, const enF3& src) const;
	void	transform			(enMatrix& mat) const;
	void	transformInvert		(enF3& v) const;									// Normalized X/Y/Z only!
	void	transformInvert		(enF3& dst, const enF3& src) const;					// Normalized X/Y/Z only!
	void	transformInvert		(class enLineF3& dst, const enLineF3& src) const;
	void	transformInvert		(enMatrix& mat) const;
	void	transformInvertXYZ	(enF3& v) const;									// Normalized X/Y/Z only!
	void	transformInvertXYZ	(enF3& dst, const enF3& src) const;					// Normalized X/Y/Z only!
	void	transformXZ			(class enF2& dst, const enF2& src) const;			// Transforms src to dst as if src = enF3(src.X, 0, src.Y)
	void	transformXYZ		(enF3& v) const;

	bool	operator==			(const enMatrix& o)									{ return X == o.X && Y == o.Y && Z == o.Z && P == o.P; }
	bool	operator!=			(const enMatrix& o)									{ return X != o.X || Y != o.Y || Z != o.Z || P != o.P; }

	void	toFloat16			(float* f16);

private:
	float*	asFloat				() const											{ return (float*) &X; }

public:
	enF3	X, Y, Z, P;
};

inline void enMatrix::toFloat16(float* f16)
{
	f16[0]	= X.X;		f16[4]	= Y.X;		f16[8]	= Z.X;		f16[12]	= P.X;
	f16[1]	= X.Y;		f16[5]	= Y.Y;		f16[9]	= Z.Y;		f16[13]	= P.Y;
	f16[2]	= X.Z;		f16[6]	= Y.Z;		f16[10]	= Z.Z;		f16[14]	= P.Z;
	f16[3]	= 0.0f;		f16[7]	= 0.0f;		f16[11]	= 0.0f;		f16[15]	= 1.0f;
}

#endif
