#include "enRnd.h"

#include "enF2.h"
#include <math.h>

/*******************************************************************/

enRnd::enRnd()
{
	reset();
}

float enRnd::getF(int x)
{
	x = (x << 13) ^ x;

	return (1.0f - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

float enRnd::getIntegerNoise(int n)
{
	n = (n >> 13) ^ n;

	int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;

	return 1.0f - ((float) nn / 1073741824.0f);
}

float enRnd::getPerlinNoise2D(float fx, float fy)
{
// Table:

	static float vs[8][2] =
	{
		{ 1         ,  0		 },
		{ 0.7071067f,  0.7071067f},
		{ 0         ,  1		 },
		{-0.7071067f,  0.7071067f},
		{-1         ,  0		 },
		{-0.7071067f, -0.7071067f},
		{ 0         , -1		 },
		{ 0.7071067f, -0.7071067f}
	};

// Get integer coordinates:

	int		ix = (int) fx + (fx >= 0 ? 0 : -1);
	int		iy = (int) fy + (fy >= 0 ? 0 : -1);
	float	rx = fx - ix;
	float	ry = fy - iy;

// Get corner values:

	enF2	c2p;
	float	ci[2][2];

	for(int cx = 0; cx < 2; cx++)
	{
		int	sx = ix + cx;

		for(int cy = 0; cy < 2; cy++)
		{
			int sy = iy + cy;

		// Select random corner vector:

			int vi = (int) (4 + enRnd::getF(sx * 239 + sy * 1549) * 3.999f);

		// Get vector from corner to point:

			c2p.set(fx - sx, fy - sy);

		// Set corner influence:

			ci[cx][cy] = c2p.dot(enF2(vs[vi][0], vs[vi][1]));
		}
	}

// Average X direction:

	float	wx = 6 * (rx * rx * rx * rx * rx) - 15 * (rx * rx * rx * rx) + 10 * (rx * rx * rx);
	float	wy = 6 * (ry * ry * ry * ry * ry) - 15 * (ry * ry * ry * ry) + 10 * (ry * ry * ry);

	float	vx0 = ci[0][0] * (1 - wx) + ci[1][0] * wx;
	float	vx1 = ci[0][1] * (1 - wx) + ci[1][1] * wx;
	float	vy  = vx0 * (1 - wy) + vx1 * wy;

	return vy;
}

/*******************************************************************/

static int perlinHashTable[2 * 256] =
{
	151,160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,

	151,160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
};

// 0..1 -> 0..1

inline float fade(float t)
{
//	6 * t^5 - 15 * t^4 + 10 * t^3:

	return t * t * t * (t * (t * 6 - 15) + 10);
}

// This method is faster than using (int) floor(x):

inline int fastfloor(float x)
{
	return x > 0 ? (int) x : (int) x - 1;
}

inline float lerp(float t, float a, float b)
{
	return a + t * (b - a);
}

inline float grad(int hash, float x, float y, float z)
{
// Convert low 4 bits of hash code into 12 gradient directions:

	int		h = hash & 15;
	float	u = h < 8 ? x : y;
	float	v = h < 4 ? y : (h == 12 || h == 14) ? x : z;

	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float enRnd::getPerlinNoise3D(const enF3& samplePos)
{
	float x = samplePos.X;
	float y = samplePos.Y;
	float z = samplePos.Z;

	int X = fastfloor(x);
	int Y = fastfloor(y);
	int Z = fastfloor(z);

	x -= X;											// FIND RELATIVE X,Y,Z
	y -= Y;											// OF POINT IN CUBE.
	z -= Z;

	X = X & 255;									// FIND UNIT CUBE THAT
	Y = Y & 255;									// CONTAINS POINT.
	Z = Z & 255;

	float u = fade(x);								// COMPUTE FADE CURVES
	float v = fade(y);								// FOR EACH OF X,Y,Z.
	float w = fade(z);

	int A	= perlinHashTable[X    ] + Y;			// HASH COORDINATES OF
	int	AA	= perlinHashTable[A    ] + Z;			// THE 8 CUBE CORNERS
	int AB	= perlinHashTable[A + 1] + Z;
	int B	= perlinHashTable[X + 1] + Y;
	int	BA	= perlinHashTable[B] + Z;
	int	BB	= perlinHashTable[B + 1] + Z;

// Add blended results from 8 corners of cube:

	return lerp
	(
		w,
		lerp
		(
			v,
			lerp
			(
				u,
				grad(perlinHashTable[AA], x  , y, z),
				grad(perlinHashTable[BA], x-1, y, z)
			),
			lerp
			(
				u,
				grad(perlinHashTable[AB], x  , y-1, z),
				grad(perlinHashTable[BB], x-1, y-1, z)
			)
		),
		lerp
		(
			v,
			lerp
			(
				u,
				grad(perlinHashTable[AA + 1], x  , y, z-1),
				grad(perlinHashTable[BA + 1], x-1, y, z-1)
			),
			lerp
			(
				u,
				grad(perlinHashTable[AB + 1], x  , y-1, z-1),
				grad(perlinHashTable[BB + 1], x-1, y-1, z-1)
			)
		)
	);
}

/*******************************************************************/

void enRnd::reset()
{
// This uses a Park/Miller generator - very good and fast:
// http://www.math.utah.edu/~alfeld/Random/Random.html

	A = 16807;
	N = 2147483647;
	X = 1;
}
