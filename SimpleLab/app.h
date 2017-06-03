#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "guiFuncs.h"
#include "SpriteFont.h"
#include "Parser/Parser.h"
#include <string>
#include <list>
#include "GUI/Widget.h"
#include "Workspace.h"
#include "ResourceManager.h"

enum class LayoutState
{
	IDLE,
	SWIPE_LEFT,
	SWIPE_RIGHT
};

class app
{
private:
	SDL_Window *wnd = nullptr;
	SDL_Renderer *rnd = nullptr;
	bool quitting = false;

	void init(  );
	void destroyApp(  );
	void event( SDL_Event *evt );
	void loop(  );
	void rend(  );

	void initWidgets();

	SpriteFont spriteFont;
	Namescope *global = nullptr;
	Parser parser;
	Workspace workspace;
	std::string text;
	
	LayoutState layoutState = LayoutState::IDLE;
	float swipe = 0.f;
	bool touch = false;
	vec2 touchPos;
	Layout *layout = nullptr;

	bool keyboard = false;

	std::vector<Widget*> widgets;



public:
	int execute(  );	//Вызывает главный цикл
	app(  );
	~app(  );
};

