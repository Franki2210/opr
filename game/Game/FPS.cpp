#include "Header.h"
#include "FPS.h"

FPS::FPS() :timer(0), fps(0) {};
FPS::~FPS() = default;

void FPS::printFPS(const float time)
{
	timer += time;
	fps++;
	if (timer >= 1000) //Каждую секунду
	{
		cout << fps << endl;
		fps = 0;
		timer = 0;
	}
}