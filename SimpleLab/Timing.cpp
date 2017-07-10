#include "Timing.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

FPSLimiter::FPSLimiter()
{

}

void FPSLimiter::init(float maxFPS)
{
	setMaxFPS(maxFPS);
}

void FPSLimiter::begin()
{
	_startTicks = SDL_GetTicks();
}

float FPSLimiter::end()
{
	calculateFPS();
	Uint32 frameTicks = SDL_GetTicks() - _startTicks;
	if (1000.f / _maxFPS > frameTicks)
	{
		SDL_Delay(1000.f / _maxFPS - frameTicks);
	}

	return _fps;
}

void FPSLimiter::calculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static Uint32 frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static Uint32 prevTicks = SDL_GetTicks();

	Uint32 currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame++ % NUM_SAMPLES] = _frameTime;
	prevTicks = currentTicks;

	int count;
	if (currentFrame < NUM_SAMPLES)
		count = currentFrame;
	else
		count = NUM_SAMPLES;

	float frameTimeAverage = 0;
	for (int i = 0; i < count; ++i)
		frameTimeAverage += frameTimes[i];
	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
		_fps = 1000.f / frameTimeAverage;
	else
		_fps = 60.f;
}