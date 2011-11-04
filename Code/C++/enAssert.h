/*
	enAssert
*/

#ifndef _enAssert
#define	_enAssert

void	enAssertHandler	(const char* test, const char* file, int line);											// The default implementation is in enAssert.cpp - simply don't include the .cpp in your project if you want to write your own.

#define	enAssert(e)		if(!(e)) { enAssertHandler(#e, __FILE__, __LINE__); *((int*) 0) = 0; }		// Make sure that the code crashes here instead of in enAssert.cpp => easier debugging.

#endif
