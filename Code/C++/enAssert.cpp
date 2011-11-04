#include "enAssert.h"

#ifdef WIN32
#include <Windows.h>
#endif

#include <stdio.h>

/*******************************************************************/

void enAssertHandler(const char* test, const char* file, int line)
{
// Show message in case this is a release version and debugger not available:

	printf("Assertion triggered in file:%s line:%d (%s)\n", file, line, test);
	fflush(stdout);

	#ifdef WIN32
	{
		static char tmp[100];

		sprintf(tmp, "Assertion triggered:\n\n%s\n\nFile: %s\nLine: %d\n", test, file, line);

		MessageBox(0, tmp, "enAssert", MB_OK | MB_ICONERROR);
	}
	#endif

// enAssert() implements *((int*) 0) = 0 => easier debugging (will jump to the right line).
// So don't put *((int*) 0) = 0 here.
}
