#include "include/time_meter.h"

clock_t TimeMeter::lastTime;

void TimeMeter::init()
{
	TimeMeter::lastTime = clock();
}

float TimeMeter::getPastTime()
{
	clock_t current = clock();
	float passed = float(current - TimeMeter::lastTime) / CLOCKS_PER_SEC;
	TimeMeter::lastTime = current;
	return passed;
}
