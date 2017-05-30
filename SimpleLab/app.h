#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "guiFuncs.h"
#include "SpriteFont.h"
#include "Parser/Parser.h"
#include <string>
#include <list>

const ColorRGBA8 bCols = { 255, 255, 255, 100 };
const ColorRGBA8 tbCol = { 0  , 0  , 255, 100 };
const ColorRGBA8 ClosBtCol = { 255, 0, 0, 100 };
const ColorRGBA8 PrsBtColr = { 128, 128, 128, 100 };
const ColorRGBA8 PrsClsBtn = { 125, 0, 0, 100 };
const ColorRGBA8 BlackColr = { 0, 0, 0, 0 };

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

	SpriteFont spriteFont;
	Namescope *global = nullptr;
	Parser parser;

	std::string text;
	std::list < std::string > workspace;
	bool keyboard = false;

public:
	int execute(  );	//Вызывает главный цикл
	app(  );
	~app(  );
};

