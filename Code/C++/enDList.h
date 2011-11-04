/*
	enDList owns a list of template data.

	IMPORTANT: enDList does NOT call constructors/destructors so perfect for vertex data etc. but not for general objects.
*/

#ifndef _enDList
#define _enDList

#include "enAlloc.h"
#include "enAssert.h"
#include "enStream.h"
#include <string.h>

template<typename D>
class enDList
{
public:
			enDList			(int initialCapacity = 16);
			~enDList		();

// Get:

	bool	get				(int index, D& d);
	D*		get				(int index);							// == 0 if none.
	int		getByteSize		()										{ return (char*) Top - (char*) Min; }
	D*		getLast			()										{ return Top > Min ? (Top - 1) : 0; }
	D*		getMax			()										{ return Top; }
	D*		getMin			()										{ return Min; }
	int		getSize			()										{ return Top - Min; }
	int		getStride		()										{ return sizeof(D); }

// Insert:

	D*		insert			()										{ return insertRange(1); }
	void	insert			(const D& v);
	D*		insertRange		(int count);

// Is:

	bool	isEmpty			()										{ return Top == Min; }
	bool	isInRange		(D* min, D* max)						{ return Min <= min && min <= max && max <= Top; }

// Read:

	bool	read			(enStreamIn* s);

// Remove:

	void	remove			(D& d);
	void	removeAt		(D* d);									// Min <= d < Top.
	void	removeAt		(int index);
	void	removeLast		(int count)								{ Top -= count; Top = (Top < Min ? Min : Top); }

// Reset:

	void	reset			()										{ Top = Min; }

// Set:

	void	set				(int index, const D& d);

// Swap:

	void	swap			(int index0, int index1);
	void	swap			(enDList<D>& other);

// Write:

	bool	write			(enStreamOut* s);

// Verify:

	void	verify			(D* d);
	
// []

	D&		operator[]		(int index)								{ return Min[index]; }

private:
	D*		Min;
	D*		Top;
	D*		Max;
};

/*******************************************************************/

template<typename D>
enDList<D>::enDList(int initialCapacity)
{
	Min	= (D*) enAllocMake(initialCapacity * sizeof(D));
	Top = Min;
	Max = Min + initialCapacity;
}

template<typename D>
enDList<D>::~enDList()
{
	enAllocKill(Min);
}

template<typename D>
D* enDList<D>::get(int index)
{
	D* d = Min + index;

	return (d < Min || d >= Top) ? 0 : d;
}

template<typename D>
bool enDList<D>::get(int index, D& d)
{
	D* pd = Min + index;

	if(pd < Min || pd >= Top)
		return false;

	d = *pd;

	return true;
}

template<typename D>
void enDList<D>::insert(const D& v)
{
	if(Top == Max)
	{
		int	os = Top - Min;
		int	ns = 2 * (Max - Min);

		Min	= (D*) enAllocResize(Min, ns * sizeof(D));
		Top = Min + os;
		Max	= Min + ns;
	}

	*Top++ = v;
}

template<typename D>
D* enDList<D>::insertRange(int count)
{
// Check size:

	if(Top + count > Max)
	{
		int	os = Top - Min;
		int	ns = 2 * (Max - Min);

		for(; os + count > ns; ns *= 2);

		Min	= (D*) enAllocResize(Min, ns * sizeof(D));
		Top = Min + os;
		Max	= Min + ns;
	}

// Return result:

	D* v = Top;

	Top += count;

	return v;
}

template<typename D>
bool enDList<D>::read(enStreamIn* s)
{
// Reset:

	reset();

// Read count:

	int count;

	if(! s->read(count))
		return false;

// Read D's:

	D* d = insertRange(count);

	if(s->read(d, count * sizeof(D)))
		return true;

// Error:

	reset();

	return false;
}

template<typename D>
void enDList<D>::remove(D& d)
{
	for(D* p = Min; p < Top; p++)
	{
		if(! p->isEqual(d))
			continue;

		memmove(p, p + 1, (char*) Top - (char*) (p + 1));

		Top--;

		return;
	}
}

template<typename D>
void enDList<D>::removeAt(int index)
{
	D* d = Min + index;

	if(d < Min || d >= Top)
		return;

	memmove(d, d + 1, (char*) Top - (char*) (d + 1));

	Top--;
}

template<typename D>
void enDList<D>::removeAt(D* d)
{
	if(d < Min || d >= Top)
		return;

	memmove(d, d + 1, (char*) Top - (char*) (d + 1));

	Top--;
}

template<typename D>
void enDList<D>::set(int index, const D& d)
{
	D* pd = Min + index;

	if(pd < Min || pd >= Top)
		return;

	*pd = d;
}

template<typename D>
void enDList<D>::swap(int index0, int index1)
{
	D tmp = Min[index0];

	Min[index0] = Min[index1];
	Min[index1] = tmp;
}

template<typename D>
void enDList<D>::swap(enDList<D>& other)
{
	D* tmpMin = Min;
	D* tmpTop = Top;
	D* tmpMax = Max;

	Min = other.Min;
	Top = other.Top;
	Max = other.Max;

	other.Min = tmpMin;
	other.Top = tmpTop;
	other.Max = tmpMax;
}

template<typename D>
void enDList<D>::verify(D* d)
{
	enAssert(Min <= d && d < Top && (((char*) d - (char*) Min) % sizeof(D)) == 0);
}

template<typename D>
bool enDList<D>::write(enStreamOut* s)
{
	int count = Top - Min;

	return s->write(count) && s->write(Min, (char*) Top - (char*) Min);
}

#endif
