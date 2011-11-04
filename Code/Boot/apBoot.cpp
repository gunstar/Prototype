#include "enAlloc.h"
#include "gwEngine.h"

#ifdef WIN32
	#include <windows.h>
	#include <commctrl.h>
#else
	#include <iostream>

	using namespace std;
#endif

#include <stdio.h>

/*******************************************************************/

#include "../Games/CityGame/ciMain.h"

void runCityGame()
{
	gwEngine* engine = new gwEngine();

	if(engine->open("City Game"))
	{
		ciMain* game = new ciMain(engine);

		game->run();

		delete game;

		engine->close();
	}

	delete engine;
}

/*******************************************************************/

#include "../Games/DungeonGame/duMain.h"

void runDungeonGame()
{
	gwEngine* engine = new gwEngine();

	if(engine->open("Dungeon Game"))
	{
		duMain* game = new duMain(engine);

		game->run();

		delete game;

		engine->close();
	}

	delete engine;
}

/*******************************************************************/

#include "../Games/FencingGame/feMain.h"

void runFencingGame()
{
	gwEngine* engine = new gwEngine();

	if(engine->open("Fencing Game"))
	{
		feMain* game = new feMain(engine);

		game->run();

		delete game;

		engine->close();
	}

	delete engine;
}

/*******************************************************************/

#include "../Games/FPRTSGame/fpMain.h"

void runFPRTSGame()
{
	gwEngine* engine = new gwEngine();

	if(engine->open("FP RTS Game"))
	{
		fpMain* game = new fpMain(engine);

		game->run();

		delete game;

		engine->close();
	}

	delete engine;
}

/*******************************************************************/

#include "../Games/IGI/igMain.h"

void runIGIGame()
{
	gwEngine* engine = new gwEngine();

	if(engine->open("IGI Game"))
	{
		igMain* game = new igMain(engine);

		game->run();

		delete game;

		engine->close();
	}

	delete engine;
}

/*******************************************************************/

#include "../Games/RacingGame/raMain.h"

void runRacingGame()
{
	gwEngine* engine = new gwEngine();

	if(engine->open("Racing Game"))
	{
		raMain* game = new raMain(engine);

		game->run();

		delete game;

		engine->close();
	}

	delete engine;
}

/*******************************************************************/

#include "../Games/ShootingGame/shMain.h"

void runShootingGame()
{
	gwEngine* engine = new gwEngine();

	if(engine->open("Shooting Game"))
	{
		shMain* game = new shMain(engine);

		game->run();

		delete game;

		engine->close();
	}

	delete engine;
}

/*******************************************************************/

#include "../Games/TestGame/teMain.h"

void runTestGame()
{
	gwEngine* engine = new gwEngine();

	if(engine->open("Test Game"))
	{
		teMain* game = new teMain(engine);

		game->run();

		delete game;

		engine->close();
	}

	delete engine;
}

/*******************************************************************/

#ifdef WIN32
int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)
#else
int main(int, char*[])
#endif
{
// Initialize common controls (make sure to include Comctl32.lib in project):

	#ifdef WIN32
	InitCommonControls();
	#endif

// Get current memory count:

	int memory = enAllocGetSize();

// Run:

	//runCityGame();
	//runDungeonGame();
	//runFencingGame();
	//runFPRTSGame();
	//runIGIGame();
	//runRacingGame();
	runShootingGame();
	//runTestGame();

// Check memory:

	int memoryLost = enAllocGetSize() - memory;

	if(memoryLost > 0)
	{
		char text[100];

		sprintf(text, "Error: Memory Overflow (%d bytes)\n", memoryLost);

		#ifdef WIN32
			MessageBox(0, text, "Boot", MB_OK | MB_ICONERROR);
		#else
			cerr << text << flush;
		#endif
	}

	return 0;
}
