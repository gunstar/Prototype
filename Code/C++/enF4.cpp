#include "enF4.h"

void enF4::clamp(float min, float max)
{
	X = (X < min) ? min : X;
	X = (X > max) ? max : X;
	Y = (Y < min) ? min : Y;
	Y = (Y > max) ? max : Y;
	Z = (Z < min) ? min : Z;
	Z = (Z > max) ? max : Z;
	W = (W < min) ? min : W;
	W = (W > max) ? max : W;
}
