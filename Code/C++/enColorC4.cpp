#include "enColorC4.h"

#include "enF4.h"

/*******************************************************************/

#define	Scale	255.99999f

/*******************************************************************/

enColorC4::enColorC4(const enF3& rgb)
{
	R = (uchar) (rgb.X * Scale);
	G = (uchar) (rgb.Y * Scale);
	B = (uchar) (rgb.Z * Scale);
	A = 255;
}

enColorC4::enColorC4(const enF4& rgba)
{
	R = (uchar) (rgba.X * Scale);
	G = (uchar) (rgba.Y * Scale);
	B = (uchar) (rgba.Z * Scale);
	A = (uchar) (rgba.W * Scale);
}

void enColorC4::clampRGBASum(int max)
{
	int sum = R + G + B + A;

	if(sum <= max)
		return;

	float mul = (float) max / sum;

	R = (int) (R * mul);
	G = (int) (G * mul);
	B = (int) (B * mul);
	A = (int) (A * mul);
}

void enColorC4::getFloat(float* f4) const
{
	f4[0] = (R == 255 ? 1 : R / 255.0f);
	f4[1] = (G == 255 ? 1 : G / 255.0f);
	f4[2] = (B == 255 ? 1 : B / 255.0f);
	f4[3] = (A == 255 ? 1 : A / 255.0f);
}

void enColorC4::scale(float scale)
{
	float f4[4];

	getFloat(f4);

	setF(f4[0] * scale, f4[1] * scale, f4[2] * scale, f4[3] * scale);
}

void enColorC4::set(enF4& rgba)
{
	R = (uchar) (rgba.X * Scale);
	G = (uchar) (rgba.Y * Scale);
	B = (uchar) (rgba.Z * Scale);
	A = (uchar) (rgba.W * Scale);
}

void enColorC4::setDelta(const enColorC4& from, const enColorC4& to, float delta)
{
	if(delta <= 0)
		*this = from;
	else if(delta >= 1)
		*this = to;
	else
	{
		R = (uchar) (from.R + delta * (to.R - from.R + 0.9999f));
		G = (uchar) (from.G + delta * (to.G - from.G + 0.9999f));
		B = (uchar) (from.B + delta * (to.B - from.B + 0.9999f));
		A = (uchar) (from.A + delta * (to.A - from.A + 0.9999f));
	}
}

void enColorC4::setF(float r, float g, float b)
{
	R = (uchar) (r >= 1 ? 255 : (r <= 0 ? 0 : r * Scale));
	G = (uchar) (g >= 1 ? 255 : (g <= 0 ? 0 : g * Scale));
	B = (uchar) (b >= 1 ? 255 : (b <= 0 ? 0 : b * Scale));
	A = 255;
}

void enColorC4::setF(float r, float g, float b, float a)
{
	R = (uchar) (r >= 1 ? 255 : r * Scale);
	G = (uchar) (g >= 1 ? 255 : g * Scale);
	B = (uchar) (b >= 1 ? 255 : b * Scale);
	A = (uchar) (a >= 1 ? 255 : a * Scale);
}

void enColorC4::setUVN(float u, float v, float n)
{
	int iu = (int) (127 + u * 127); iu = (iu < 0 ? 0 : iu); iu = (iu > 255 ? 255 : iu);
	int iv = (int) (127 + v * 127); iv = (iv < 0 ? 0 : iv); iv = (iv > 255 ? 255 : iv);
	int in = (int) (127 + n * 127); in = (in < 0 ? 0 : in); in = (in > 255 ? 255 : in);

	R = (uchar) iu;
	G = (uchar) iv;
	B = (uchar) in;
	A = 0;
}
