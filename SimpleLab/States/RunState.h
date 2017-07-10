#pragma once
#include "BaseState.h"
#include "../Parser/Parser.h"
#include "../Widgets/MultilineEdit.h"

class RunState : public BaseState
{
public:
	RunState(app *appPtr) : BaseState(appPtr) { }
	
	void onInit(SDL_Renderer *renderer, SpriteFont *spriteFont) override;
	void onEvent(SDL_Event *event) override;
	void onLoop(float deltaTime) override;
	void onRender(SDL_Renderer *renderer, SpriteFont *spriteFont) override;
	void onExit() override;

private:
	void initWidgets(SDL_Renderer *renderer, SpriteFont *spriteFont);

private:
	Namescope *global = nullptr;
	Parser parser;
	std::string text;

	MultilineEdit *workspace = nullptr;

	bool touch = false;
	vec2 touchPos;

	bool keyboard = false;

	std::vector< std::pair<Widget*, float> > widgets;
};