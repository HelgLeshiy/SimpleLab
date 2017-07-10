#pragma once

#include <SDL2/SDL.h>

class FPSLimiter
{
public:
	FPSLimiter();
	void init(float maxFPS);
	void setMaxFPS(float maxFPS) { _maxFPS = maxFPS; }
	void begin();
	float end();

private:
	void calculateFPS();

private:
	float _maxFPS;
	Uint32 _startTicks;
	Uint32 _frameTime;
	float _fps;
};