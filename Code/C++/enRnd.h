/*
	enRnd is a random number generator.

	It uses a Park/Miller generator so it is very
	fast, very random and has a long cycle time (2^31 - 1).

	Use setSeed(1..N) to create a "family" of different random number generators.
	Use setSeed(x, y) to create a "family" of different random number generators based on position.

	http://www.math.utah.edu/~alfeld/Random/Random.html
*/

#ifndef _enRnd
#define	_enRnd

#include "enF3.h"

typedef unsigned int uint;

class enRnd
{
public:
					enRnd				();

	float			getF				()								{ X = (A * X + Y) % N; return (float) X / N; }	// [0;1[
	float			getF				(float min, float max)			{ return min + getF() * (max - min); }			// [min;max[
	static float	getF				(int x);						// [-1;1] Same x always returns same float.
	int				getI				(int min, int max)				{ return (int) (min + getF() * (max - min)); }	// [min;max[

	static float	getIntegerNoise		(int n);						// == [-1,1] same n always returns same float.
	static float	getPerlinNoise2D	(float x, float y);				// == [-1,1] same xy always returns same float.
	static float	getPerlinNoise3D	(const enF3& samplePos);		// == [-1,1] same xyz always returns same float.

	void			reset				();

	void			setSeed				(uint x)						{ X = x; Y = 0; }
	void			setSeed				(uint x, uint y)				{ X = x; Y = y; }

private:
	uint			A;		// Multiplier (0 <= A < N)
	uint			N;		// Modulus (0 < N)
	uint			X;		// Value
	uint			Y;		// Offset
};

#endif
