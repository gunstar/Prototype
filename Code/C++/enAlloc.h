/*
	enAlloc
*/

#ifndef _enAlloc
#define	_enAlloc

int		enAllocGetSize		();							// Returns the memory allocated in bytes.
void	enAllocKill			(void* m);
void*	enAllocMake			(int size);
void*	enAllocResize		(void* m, int size);

#endif
