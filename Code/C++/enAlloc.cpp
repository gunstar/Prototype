#include "enAlloc.h"
#include "enAssert.h"

#include <malloc.h>

#ifdef WIN32
#include <intrin.h>
#endif

/*******************************************************************/

struct Block
{
	int	Size;		// Bytes allocated in memory block.
};

#ifdef WIN32
static volatile long Size = 0;	// Thread safe because using _Interlocked* intrinsics to modify.
#else
static long Size = 0;			// NOT thread safe!
#endif

/*******************************************************************/

int enAllocGetSize()
{
	return (int) Size;
}

void enAllocKill(void* m)
{
// Check m:

	if(m == 0)
		return;

// Update total:

	Block* b = (Block*) m - 1;

	#ifdef WIN32
	_InterlockedExchangeAdd(&Size, (long) (- b->Size));
	#else
	Size += (long) - b->Size;
	#endif

// Free block:

	free(b);
}

void* enAllocMake(int size)
{
// Check:

	enAssert(size >= 0);

// Alloc block:

	Block*	b = (Block*) malloc(sizeof(Block) + size);
	void*	m = b + 1;

	b->Size	= size;

// Update size:

	#ifdef WIN32
	_InterlockedExchangeAdd(&Size, (long) size);
	#else
	Size += (long) size;
	#endif

// Return result:

	return m;
}

void* enAllocResize(void* m, int size)
{
// Check:

	if(m == 0)
		return enAllocMake(size);

	enAssert(size >= 0);

// Update size:

	Block* b = (Block*) m - 1;

	#ifdef WIN32
	_InterlockedExchangeAdd(&Size, (long) (- b->Size + size));
	#else
	Size += (long) (- b->Size + size);
	#endif

// Realloc block:

	b = (Block*) realloc(b, sizeof(Block) + size);
	m = b + 1;

	b->Size	= size;

// Return result:

	return m;
}

/*******************************************************************/

void operator delete(void* m)
{
	enAllocKill(m);
}

void* operator new(size_t size)
{
	return enAllocMake(size);
}

void* operator new(size_t, void* ptr)
{
	return ptr;
}
