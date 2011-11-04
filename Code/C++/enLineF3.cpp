#include "enLineF3.h"

/*******************************************************************/

enLineF3::enLineF3()
{
	Length = 0;
}

enLineF3::enLineF3(const enF3& from, const enF3& to)
{
	From = from;
	To	 = to;

	Dir.subSet(To, From);

	Length = Dir.normalize();
}

enLineF3::enLineF3(enLineF3& line)
{
	Dir		= line.Dir;
	From	= line.From;
	Length	= line.Length;
	To		= line.To;
}

float enLineF3::getDistance(enF3& pos)
{
	enF3 result;

	getNearest(pos, result);

	return result.distance(pos);
}

void enLineF3::getMinMax(enF3& min, enF3& max)
{
	min.X = (From.X <= To.X ? From.X : To.X);
	min.Y = (From.Y <= To.Y ? From.Y : To.Y);
	min.Z = (From.Z <= To.Z ? From.Z : To.Z);

	max.X = (From.X >= To.X ? From.X : To.X);
	max.Y = (From.Y >= To.Y ? From.Y : To.Y);
	max.Z = (From.Z >= To.Z ? From.Z : To.Z);
}

void enLineF3::getNearest(const enF3& pos, enF3& result) const
{
// Get normalized line vector:

	enF3 line(From, To);

	float lineLen = line.normalize();

// Get local vector:

	enF3 local(From, pos);

// Get dot (length of local vector x cos(v)):

	float dot = line.dot(local);

// Handle behind/front cases:

	if(dot < 0)
		result = From;
	else if(dot > lineLen)
		result = To;
	else
	{
		result = From;

		result.scaleAdd(line, dot);
	}
}

void enLineF3::set(enF3& from, enF3& to)
{
	From = from;
	To	 = to;

	Dir.subSet(To, From);

	Length = Dir.normalize();
}

void enLineF3::test()
{
	enF3		from(0,  50, 0);
	enF3		to	(0, 100, 0);
	enLineF3	line(from, to);
	enF3		result;

	line.getNearest(enF3(0,   0, 0), result);
	line.getNearest(enF3(0,  75, 0), result);
	line.getNearest(enF3(0, 150, 0), result);

	line.getNearest(enF3(-10000,  49, 0), result);
	line.getNearest(enF3(-10000,  60, 0), result);
}
