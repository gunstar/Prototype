/*
	enColorC4 manages a RGBA color stored as 4 uchars.
*/

#ifndef _enColorC4
#define _enColorC4

typedef unsigned char	uchar;
typedef unsigned int	uint;

class enColorC4
{
public:
			enColorC4		()																{ *((uint*) this) = 0xFFFFFFFF; }
			enColorC4		(int r, int g, int b)											{ R = r; G = g; B = b; A = 255; }
			enColorC4		(int r, int g, int b, int a)									{ R = r; G = g; B = b; A = a; }
			enColorC4		(const class enF3& rgb);
			enColorC4		(const class enF4& rgba);

	void	clampRGBASum	(int max);

	void	getFloat		(float* f4) const;

	bool	isEqual			(const enColorC4& other)										{ return *((uint*) this) == *((uint*) &other); }

	void	reset			()																{ R = G = B = A = 255; }

	void	scale			(float scale);

	void	set				(const enColorC4& color)										{ *((uint*) this) = *((uint*) &color); }
	void	set				(enF4& rgba);
	void	set0			()																{ R = G = B = A = 0; }
	void	setDelta		(const enColorC4& from, const enColorC4& to, float delta);
	void	setDeltaA		(const enColorC4& from, const enColorC4& to, float delta)		{ setDelta(from, to, (delta <= 0.5f) ? (delta * 2) : (1 - 2 * (delta - 0.5f))); }
	void	setC			(uchar r, uchar g, uchar b, uchar a)							{ R = r; G = g; B = b; A = a; }
	void	setF			(float r, float g, float b);									// 0 <= r/g/b <= 1
	void	setF			(float r, float g, float b, float a);							// 0 <= r/g/b/a <= 1
	void	setI			(int r, int g, int b)											{ R = r; G = g; B = b; A = 255; }
	void	setI			(int r, int g, int b, int a)									{ R = r; G = g; B = b; A = a; }
	void	setUVN			(float u, float v, float n);									// -1 <= u/v/n <= 1

	bool	operator==		(const enColorC4& o)											{ return R == o.R && G == o.G && B == o.B && A == o.A; }
	bool	operator!=		(const enColorC4& o)											{ return R != o.R || G != o.G || B != o.B || A != o.A; }

public:
	uchar	B, G, R, A;		// Stored like this to be DirectX (PC) compatible.
};

#endif
