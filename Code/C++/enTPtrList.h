/*
	enTPtrList manages a list of pointers to Template Class objects.
	Using enTPtrList combined with enTBag => VERY fast
	insert/remove even if T is big because only moving pointers.

	Multiple enTPtrList's can reuse the same enTBag => VERY efficient
	usage of memory (avoids waste in every list).

	IMPORTANT: If objects doesn't need to be kept in a specific order
	then only enTBag is needed. enTPtrList is only needed if an
	ordered	list of	objects are needed.
*/

#ifndef _enTPtrList
#define	_enTPtrList

#include "enAlloc.h"
#include <string.h>

/*******************************************************************/

template<typename T> class enTPtrList_NoKill
{
public:
			enTPtrList_NoKill	(int initialCapacity = 16);
			~enTPtrList_NoKill	();

	T*		get					(int index) const			{ T** tp = Min + index; return (tp >= Min && tp < Top) ? *tp : 0; }
	T*		getFirst			()							{ Seek = Min; return (Seek < Top) ? *Seek++ : 0; }
	int		getIndex			(T* t);						// == -1 if not in list.
	T*		getLast				()							{ return (Top > Min) ? *(Top - 1) : 0; }
	T**		getMax				()							{ return Top; }
	T**		getMin				()							{ return Min; }
	T*		getNext				()							{ return (Seek < Top) ? *Seek++ : 0; }
	int		getSize				() const					{ return Top - Min; }

	T*		insert				(T* t);
	bool	insertAt			(int index, T* t);
	void	insertList			(enTPtrList_NoKill<T>* list);

	bool	isEmpty				()							{ return Top == Min; }
	bool	isIn				(T* t);

	void	remove				(T* t);
	void	removeAll			()							{ Top = Min; }
	T*		removeAt			(int index);
	T*		removeLast			()							{ return (Top > Min) ? *--Top : 0; }

	void	set					(int index, T* t);
	void	set					(enTPtrList_NoKill<T>* list){ removeAll(); insertList(list); }

	void	sort				();

	void	swap				(int index0, int index1);
	void	swap				(T* from, T* to);
	void	swap				(enTPtrList_NoKill& other);
	
	T*		operator[]			(int index)					{ T** tp = Min + index; return (tp >= Min && tp < Top) ? *tp : 0; }

protected:
	T**		Min;
	T**		Seek;
	T**		Top;
	T**		Max;
};

/*******************************************************************/

template<typename T> class enTPtrList: public enTPtrList_NoKill<T>
{
public:
			~enTPtrList		();

	void	killAll			();
};

/*******************************************************************/

template<typename T> enTPtrList<T>::~enTPtrList()
{
	killAll();
}

template<typename T> void enTPtrList<T>::killAll()
{
	for(T** p = enTPtrList_NoKill<T>::Top - 1; p >= enTPtrList_NoKill<T>::Min; p--)
		delete *p;

	enTPtrList_NoKill<T>::Top = enTPtrList_NoKill<T>::Min;
}

/*******************************************************************/

template<typename T> enTPtrList_NoKill<T>::enTPtrList_NoKill(int initialCapacity)
{
	Min	= (T**) enAllocMake(initialCapacity * sizeof(T*));
	Top = Min;
	Max	= Min + initialCapacity;
}

template<typename T> enTPtrList_NoKill<T>::~enTPtrList_NoKill()
{
	enAllocKill(Min);
}

template<typename T> int enTPtrList_NoKill<T>::getIndex(T* t)
{
	for(T** tp = Min; tp < Top; tp++)
		if(*tp == t)
			return tp - Min;

	return -1;
}

template<typename T> T* enTPtrList_NoKill<T>::insert(T* t)
{
	if(Top == Max)
	{
		int	os = Top - Min;
		int	ns = 2 * (Max - Min);

		Min = (T**) enAllocResize(Min, ns * sizeof(T*));
		Top	= Min + os;
		Max	= Min + ns;
	}

	*Top++ = t;
	
	return t;
}

template<typename T> bool enTPtrList_NoKill<T>::insertAt(int index, T* t)
{
// Check index:

	if(index < 0 || index > Top - Min)
		return false;

// Make space:

	if(Top == Max)
	{
		int	os = Max - Min;
		int	ns = 2 * (Max - Min);

		Min = (T**) enAllocResize(Min, ns * sizeof(T*));
		Top	= Min + os;
		Max	= Min + ns;
	}

// Move:

	T** tp = Min + index;

	memmove(tp + 1, tp, (char*) (Top++) - (char*) tp);

	*tp = t;

	return true;
}

template<typename T> void enTPtrList_NoKill<T>::insertList(enTPtrList_NoKill<T>* list)
{
	if(list == this)
		return;

	for(T** tp = list->Min; tp < list->Top; tp++)
		insert(*tp);
}

template<typename T> bool enTPtrList_NoKill<T>::isIn(T* t)
{
	for(T** tp = Min; tp < Top; tp++)
		if(*tp == t)
			return true;

	return false;
}

template<typename T> void enTPtrList_NoKill<T>::remove(T* t)
{
	for(T** tp = Min; tp < Top; tp++)
	{
		if(*tp == t)
		{
			memmove(tp, tp + 1, (Top - (tp + 1)) * sizeof(T*));

			Top--;

			return;
		}
	}
}

template<typename T> T* enTPtrList_NoKill<T>::removeAt(int index)
{
	T** tp = Min + index;

	if(tp < Min || tp >= Top)
		return 0;

	T* result = *tp;

	memmove(tp, tp + 1, (char*) (Top--) - (char*) (tp + 1));

	return result;
}

template<typename T> void enTPtrList_NoKill<T>::set(int index, T* t)
{
	T** tp = Min + index;

	if(tp >= Min && tp < Top)
		*tp = t;
}

template<typename T> void enTPtrList_NoKill<T>::sort()
{
	for(T** p0 = Min; p0 + 1 < Top; p0++)
		for(T** p1 = p0 + 1; p1 < Top; p1++)
			if((*p0)->compare(*p1) > 0)
			{
				T* tmp	= *p0;
				*p0		= *p1;
				*p1		= tmp;
			}
}

template<typename T> void enTPtrList_NoKill<T>::swap(int index0, int index1)
{
	T** p0 = Min + index0;
	T** p1 = Min + index1;

	if(p0 < Min || p0 >= Top || p1 < Min || p1 >= Top)
		return;

	T* tmp	= *p0;
	*p0		= *p1;
	*p1		= tmp;
}

template<typename T> void enTPtrList_NoKill<T>::swap(T* from, T* to)
{
	for(T** tp = Min; tp < Top; tp++)
		if(*tp == from)
			*tp = to;
}

template<typename T> void enTPtrList_NoKill<T>::swap(enTPtrList_NoKill& other)
{
	T** tMin = Min;
	T** tTop = Top;
	T** tMax = Max;

	Min	= other.Min;
	Top	= other.Top;
	Max	= other.Max;

	other.Min = tMin;
	other.Top = tTop;
	other.Max = tMax;
}

#endif
