#include "stdafx.h"
#include "Game.h"
#include "TestUnit.h"

int main(int argc, char* argv[])
{
	const int SCREEN_WIDTH = 720;
	const int SCREEN_HEIGHT = 580;
	//Game* g = new Game(SCREEN_WIDTH, SCREEN_HEIGHT);
	//g->GameLoop();
	//delete g;
	TestUnit::RunTests();
	return 0;
}
