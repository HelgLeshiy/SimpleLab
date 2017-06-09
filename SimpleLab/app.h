#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GUI/guiFuncs.h"
#include "SpriteFont.h"
#include "Parser/Parser.h"
#include <string>
#include <list>
#include "Widgets/Widget.h"
#include "Widgets/MultilineEdit.h"
#include "ResourceManager.h"

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
	std::string text;
	
	MultilineEdit *workspace = nullptr;
	
	bool touch = false;
	vec2 touchPos;

	bool keyboard = false;

	std::vector< std::pair<Widget*, float> > widgets;

public:
	int execute(  );	//Вызывает главный цикл
	app(  );
	~app(  );
};

