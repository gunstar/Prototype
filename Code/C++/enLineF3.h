/*
	enLineF3 represents a 3D float line.
*/

#ifndef _enLineF3
#define	_enLineF3

#include "enF3.h"

class enLineF3
{
public:
				enLineF3		();
				enLineF3		(const enF3& from, const enF3& to);
				enLineF3		(enLineF3& line);

	void		extendFrom		(float length)						{ From.scaleAdd(Dir, length); }

	float		getDistance		(enF3& pos);
	void		getMinMax		(enF3& min, enF3& max);
	void		getNearest		(const enF3& pos, enF3& nearest) const;

	void		set				(enF3& from, enF3& to);

public:
	static void	test			();

public:
	enF3	Dir;				// Normalized direction from From to To.
	enF3	From;
	float	Length;				// Length from From to To.
	enF3	To;
};

#endif
