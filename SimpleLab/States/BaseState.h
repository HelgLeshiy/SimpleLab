#pragma once
#include <SDL2/SDL.h>
#include "../SpriteFont.h"

class app;

class BaseState
{
public:
	BaseState(app *appPtr) : m_appPtr(appPtr) { }
	
	virtual void onInit(SDL_Renderer *renderer, SpriteFont *spriteFont) = 0;
	virtual void onEvent(SDL_Event *event) = 0;
	virtual void onLoop(float deltaTime) = 0;
	virtual void onRender(SDL_Renderer *renderer, SpriteFont *spriteFont) = 0;
	virtual void onExit() = 0;

protected:
	app *m_appPtr = nullptr;
};