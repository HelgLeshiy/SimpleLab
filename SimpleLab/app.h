#pragma once
#include <SDL2/SDL.h>
#include "SpriteFont.h"
#include <stack>
#include <sstream>

class BaseState;

class app
{
private:
	SDL_Window *wnd = nullptr;
	SDL_Renderer *rnd = nullptr;

	void init(  );
	void destroyApp(  );
	void onEvent(SDL_Event *event);
	void onLoop(float deltaTime);
	void rend(  );

	SpriteFont spriteFont;

	float fps = 60;

	std::stack<BaseState*> m_states;

public:
	int execute(  );	//Вызывает главный цикл
	void pushState(BaseState *state);
	void popState();
	app(  );
	~app(  );

	template <typename T>
	static std::string toString(T a)
	{
		std::stringstream ss;
		ss << a;
		return ss.str();
	}
};

