#pragma once
#include "BaseState.h"

enum class LogoStateType
{
	INCREASE,
	DECREASE
};

class LogoState : public BaseState
{
public:
	LogoState(app *appPtr) : BaseState(appPtr) { }
	
	void onInit(SDL_Renderer *renderer, SpriteFont *spriteFont) override;
	void onEvent(SDL_Event *event) override;
	void onLoop(float deltaTime) override;
	void onRender(SDL_Renderer *renderer, SpriteFont *spriteFont) override;
	void onExit() override;

private:
	LogoStateType logoState = LogoStateType::INCREASE;
	float logoTimer = 0.f;
};