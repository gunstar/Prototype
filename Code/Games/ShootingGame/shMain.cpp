#include "shMain.h"

/*******************************************************************/

shMain::shMain(eiEngine* engine)
{
	Engine	= engine;

	Map		= new shMap(engine);
	Player	= new shPlayer(engine);
	Camera	= Player->makeCamera();
}

shMain::~shMain()
{
	delete Camera;
	delete Map;
	delete Player;
}

void shMain::run()
{
	Engine->setInput(this);
	Engine->setTicker(this);

	Engine->run();
}

/*******************************************************************/

void shMain::eiInput_key(int key, bool down)
{
	Camera->eiInput_key(key, down);

	if(key == eiInput::Home && down)
	{
		Player->reset();
		Camera->reset();
	}
}

void shMain::eiTicker_tick(float secs)
{
	Player->tick(secs);
	Camera->tick(secs);
}
