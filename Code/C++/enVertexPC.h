/*
	enVertexPC defines a vertex containing a point and a color.
*/

#ifndef _enVertexPC
#define _enVertexPC

#include "enColorC4.h"
#include "enF3.h"

class enVertexPC
{
public:
	enF3		Pos;
	enColorC4	Color;
};

#endif
