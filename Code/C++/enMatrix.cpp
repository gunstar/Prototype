#include "enMatrix.h"

#include "enF2.h"
#include "enLineF3.h"

/*******************************************************************/

enMatrix::enMatrix()
{
	X.X = 1;
	Y.Y = 1;
	Z.Z = 1;
}

enMatrix::enMatrix(const enMatrix& mat)
{
	float*		 d = asFloat();
	const float* s = ((enMatrix&) mat).asFloat();

	for(int i = 0; i < 12; i++)
		*d++ = *s++;
}

enMatrix::enMatrix(const enMatrix* mat)
{
	float*		 d = asFloat();
	const float* s = mat->asFloat();

	for(int i = 0; i < 12; i++)
		*d++ = *s++;
}

float enMatrix::difference(const enMatrix& other)
{
	return X.distance(other.X) + Y.distance(other.Y) + Z.distance(other.Z) + P.distance(other.P);
}

float enMatrix::differenceXYZ(const enMatrix& other)
{
	return X.distance(other.X) + Y.distance(other.Y) + Z.distance(other.Z);
}

void enMatrix::flipYZ()
{
	enF3 t(Y);

	X.set(X.X, X.Z, X.Y);
	Y.set(Z.X, Z.Z, Z.Y);
	Z.set(t.X, t.Z, t.Y);
	P.set(P.X, P.Z, P.Y);
}

void enMatrix::flipYZScaleP(float scale)
{
	enF3 t(Y);

	X.set(X.X, X.Z, X.Y);
	Y.set(Z.X, Z.Z, Z.Y);
	Z.set(t.X, t.Z, t.Y);
	P.set(scale * P.X, scale * P.Z, scale * P.Y);
}

float enMatrix::getScaleMax()
{
	float	scale;
	float	sx = X.length();
	float	sy = Y.length();
	float	sz = Z.length();

	scale = sx;
	scale = (sy > scale ? sy : scale);
	scale = (sz > scale ? sz : scale);

	return scale;
}

void enMatrix::invert()
{
// This ensures that inverting matrices with non-unit X/Y/Z works correctly (verified with enMatrixTester):

	X.scaleSet(X, 1.0f / X.lengthSqr());
	Y.scaleSet(Y, 1.0f / Y.lengthSqr());
	Z.scaleSet(Z, 1.0f / Z.lengthSqr());

// P is inverted first:

	P.negate();
	P.set(X.dot(P), Y.dot(P), Z.dot(P));

// XYZ can be inverted by simply transposing the 3x3 XYZ matrix (verified with enMatrixTester):

	float xy = X.Y;	float xz = X.Z;
	float yx = Y.X;	float yz = Y.Z;
	float zx = Z.X;	float zy = Z.Y;

	X.Y = yx; X.Z = zx;
	Y.X = xy; Y.Z = zy;
	Z.X = xz; Z.Y = yz;
}

void enMatrix::invertSet(const enMatrix& other)
{
// This ensures that inverting matrices with non-unit X/Y/Z works correctly (Verified with enMatrixTester):

	X.scaleSet(other.X, 1.0f / other.X.lengthSqr());
	Y.scaleSet(other.Y, 1.0f / other.Y.lengthSqr());
	Z.scaleSet(other.Z, 1.0f / other.Z.lengthSqr());

// P is inverted first:

	P.negateSet(other.P);
	P.set(X.dot(P), Y.dot(P), Z.dot(P));

// XYZ can be inverted by simply transposing the 3x3 XYZ matrix (verified with enMatrixTester):

	float xy = X.Y;	float xz = X.Z;
	float yx = Y.X;	float yz = Y.Z;
	float zx = Z.X;	float zy = Z.Y;

	X.Y = yx; X.Z = zx;
	Y.X = xy; Y.Z = zy;
	Z.X = xz; Z.Y = yz;
}

bool enMatrix::isIdentity()
{
	return
		X.X == 1 && X.Y == 0 && X.Z == 0 &&
		Y.X == 0 && Y.Y == 1 && Y.Z == 0 &&
		Z.X == 0 && Z.Y == 0 && Z.Z == 1 &&
		P.X == 0 && P.Y == 0 && P.Z == 0;
}

bool enMatrix::isMirrored() const
{
	enF3 y;

	y.cross(X, Z);

	return y.dot(Y) < 0;
}

void enMatrix::multiplySet(const enMatrix& l, const enMatrix& r)
{
	/*
						X.X, X.Y, X.Z,
						Y.X, Y.Y, Y.Z,
						Z.X, Z.Y, Z.Z,
						P.X, P.Y, P.Z

		X.X, X.Y, X.Z,
		Y.X, Y.Y, Y.Z,
		Z.X, Z.Y, Z.Z,
		P.X, P.Y, P.Z
	*/

	X.X = l.X.X * r.X.X + l.X.Y * r.Y.X + l.X.Z * r.Z.X;
	X.Y = l.X.X * r.X.Y + l.X.Y * r.Y.Y + l.X.Z * r.Z.Y;
	X.Z = l.X.X * r.X.Z + l.X.Y * r.Y.Z + l.X.Z * r.Z.Z;

	Y.X = l.Y.X * r.X.X + l.Y.Y * r.Y.X + l.Y.Z * r.Z.X;
	Y.Y = l.Y.X * r.X.Y + l.Y.Y * r.Y.Y + l.Y.Z * r.Z.Y;
	Y.Z = l.Y.X * r.X.Z + l.Y.Y * r.Y.Z + l.Y.Z * r.Z.Z;

	Z.X = l.Z.X * r.X.X + l.Z.Y * r.Y.X + l.Z.Z * r.Z.X;
	Z.Y = l.Z.X * r.X.Y + l.Z.Y * r.Y.Y + l.Z.Z * r.Z.Y;
	Z.Z = l.Z.X * r.X.Z + l.Z.Y * r.Y.Z + l.Z.Z * r.Z.Z;

	P.X = l.P.X * r.X.X + l.P.Y * r.Y.X + l.P.Z * r.Z.X + r.P.X;
	P.Y = l.P.X * r.X.Y + l.P.Y * r.Y.Y + l.P.Z * r.Z.Y + r.P.Y;
	P.Z = l.P.X * r.X.Z + l.P.Y * r.Y.Z + l.P.Z * r.Z.Z + r.P.Z;
}

void enMatrix::rotate(const enF3& axisI, float angle)
{
	enF3 axis(axisI);

	X.rotate(axis, angle);
	X.normalize();

	Y.rotate(axis, angle);
	Y.normalize();

	Z.rotate(axis, angle);
	Z.normalize();
}

void enMatrix::set(const enMatrix& mat)
{
	float*		 d = asFloat();
	const float* s = ((enMatrix&) mat).asFloat();

	for(int i = 0; i < 12; i++)
		*d++ = *s++;
}

void enMatrix::setDelta(enMatrix* from, float delta)
{
	X.setDelta(from->X, delta);
	X.normalize();

	Y.setDelta(from->Y, delta);
	Y.normalize();

	Z.setDelta(from->Z, delta);
	Z.normalize();

	P.setDelta(from->P, delta);
}

void enMatrix::setDelta(enMatrix* from, enMatrix* to, float delta)
{
	X.setDelta(from->X, to->X, delta);
	X.normalize();

	Y.setDelta(from->Y, to->Y, delta);
	Y.normalize();

	Z.setDelta(from->Z, to->Z, delta);
	Z.normalize();

	P.setDelta(from->P, to->P, delta);
}

void enMatrix::setDeltaXYZ(enMatrix* from, enMatrix* to, float delta)
{
	X.setDelta(from->X, to->X, delta);
	X.normalize();

	Y.setDelta(from->Y, to->Y, delta);
	Y.normalize();

	Z.setDelta(from->Z, to->Z, delta);
	Z.normalize();
}

void enMatrix::setDeltaTransform(const enMatrix& from, const enMatrix& to)
{
// This ensures that matrices with non-unit X/Y/Z works correctly.
// Verified with enMatrixTester:

	enMatrix mat;

	mat.X.scaleSet	(from.X, 1.0f / from.X.lengthSqr());
	mat.Y.scaleSet	(from.Y, 1.0f / from.Y.lengthSqr());
	mat.Z.scaleSet	(from.Z, 1.0f / from.Z.lengthSqr());
	mat.P.subSet	(to.P, from.P);

// Transform:

	X.set(mat.X.dot(to.X),	mat.Y.dot(to.X),  mat.Z.dot(to.X));
	Y.set(mat.X.dot(to.Y),	mat.Y.dot(to.Y),  mat.Z.dot(to.Y));
	Z.set(mat.X.dot(to.Z),	mat.Y.dot(to.Z),  mat.Z.dot(to.Z));
	P.set(mat.X.dot(mat.P),	mat.Y.dot(mat.P), mat.Z.dot(mat.P));
}

void enMatrix::setIdentity()
{
	X.set(1, 0, 0);
	Y.set(0, 1, 0);
	Z.set(0, 0, 1);
	P.set0();
}

void enMatrix::setIdentityXYZ()
{
	X.set(1, 0, 0);
	Y.set(0, 1, 0);
	Z.set(0, 0, 1);
}

void enMatrix::setLookAt(const enF3& from, const enF3& to)
{
	Z.subSet(to, from);
	Z.normalize();

	X.set(Z.Z, 0, - Z.X);

	if(X.length() < 0.00001f)
		X.set(1, 0, 0);
	else
		X.normalize();

	Y.cross(X, Z);

	P.set(from);
}

void enMatrix::setLookAt(const enF3& from, const enF3& to, const enF3& y)
{
	Z.subSet(to, from);
	Z.normalize();

	X.cross(Z, y);
	X.normalize();

	Y.cross(X, Z);
	Y.normalize();

	P.set(from);
}

void enMatrix::setOrientation(const enF3& axisI, float angle)
{
	enF3 axis(axisI);

	X.rotateSet(enF3(1, 0, 0), axis, angle);
	Y.rotateSet(enF3(0, 1, 0), axis, angle);
	Z.rotateSet(enF3(0, 0, 1), axis, angle);
}

void enMatrix::transform(enF3& v) const
{
	float x = v.X;
	float y = v.Y;
	float z = v.Z;

	v.X = P.X + x * X.X + y * Y.X + z * Z.X;
	v.Y = P.Y + x * X.Y + y * Y.Y + z * Z.Y;
	v.Z = P.Z + x * X.Z + y * Y.Z + z * Z.Z;
}

void enMatrix::transform(enF3& dst, const enF3& src) const
{
	/*
				X.X, X.Y, X.Z,
				Y.X, Y.Y, Y.Z,
				Z.X, Z.Y, Z.Z,
				P.X, P.Y, P.Z

		[X Y Z]
	*/

	dst.X = P.X + src.X * X.X + src.Y * Y.X + src.Z * Z.X;
	dst.Y = P.Y + src.X * X.Y + src.Y * Y.Y + src.Z * Z.Y;
	dst.Z = P.Z + src.X * X.Z + src.Y * Y.Z + src.Z * Z.Z;
}

void enMatrix::transform(enMatrix& mat) const
{
	enF3 x, y, z;

	x.addSet(mat.P, mat.X);
	y.addSet(mat.P, mat.Y);
	z.addSet(mat.P, mat.Z);

	transform(x);
	transform(y);
	transform(z);

	transform(mat.P);

	mat.X.subSet(x, mat.P);
	mat.Y.subSet(y, mat.P);
	mat.Z.subSet(z, mat.P);
}

void enMatrix::transformInvert(enF3& v) const
{
	v.sub(P);
	v.set(X.dot(v), Y.dot(v), Z.dot(v));
}

void enMatrix::transformInvert(enF3& dst, const enF3& src) const
{
	enF3 delta(P, src);

	dst.set(X.dot(delta), Y.dot(delta), Z.dot(delta));
}

void enMatrix::transformInvert(enLineF3& dst, const enLineF3& src) const
{
	enF3 df(src.From);
	enF3 dt(src.To);

	transformInvert(df);
	transformInvert(dt);

	dst.set(df, dt);
}

void enMatrix::transformInvert(enMatrix& mat) const
{
	enF3 x, y, z, p;

	x.addSet(mat.P, mat.X);
	y.addSet(mat.P, mat.Y);
	z.addSet(mat.P, mat.Z);

	transformInvert(x);
	transformInvert(y);
	transformInvert(z);
	transformInvert(mat.P);

	mat.X.subSet(x, mat.P);
	mat.Y.subSet(y, mat.P);
	mat.Z.subSet(z, mat.P);
}

void enMatrix::transformInvertXYZ(enF3& v) const
{
	v.set(X.dot(v), Y.dot(v), Z.dot(v));
}

void enMatrix::transformInvertXYZ(enF3& dst, const enF3& src) const
{
	dst.set(X.dot(src), Y.dot(src), Z.dot(src));
}

void enMatrix::transformXZ(enF2& dst, const enF2& src) const
{
	dst.X = P.X + src.X * X.X + src.Y * Y.X + src.Y * Z.X;
	dst.Y = P.Z + src.X * X.Z + src.Y * Y.Z + src.Y * Z.Z;
}

void enMatrix::transformXYZ(enF3& v) const
{
	float x = v.X;
	float y = v.Y;
	float z = v.Z;

	v.X = x * X.X + y * Y.X + z * Z.X;
	v.Y = x * X.Y + y * Y.Y + z * Z.Y;
	v.Z = x * X.Z + y * Y.Z + z * Z.Z;
}
