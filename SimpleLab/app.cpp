#include "app.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "prefs.h"
#include "Timing.h"
#include "States/LogoState.h"
#include "GUI/guiFuncs.h"
#include "ResourceManager.h"

void app::init( )
{
	SDL_Init( SDL_INIT_EVERYTHING );
	IMG_Init( IMG_INIT_PNG );
	TTF_Init(  );

	wnd = SDL_CreateWindow( "SimpleLab for Smartphones", 100, 100, SCR_W, SCR_H, 0 );
	rnd = SDL_CreateRenderer( wnd, -1, SDL_RENDERER_ACCELERATED );

	SDL_RenderSetLogicalSize(rnd, 480, 800);

	spriteFont.init(rnd, "data/images/Bisasam_20x20_ascii.png", 16, 16);

	pushState(new LogoState(this));
}

void app::destroyApp( )
{
	while (!m_states.empty())
	{
		popState();
	}

	SDL_DestroyRenderer( rnd );
	SDL_DestroyWindow( wnd );
	TTF_Quit(  );
	IMG_Quit(  );
	SDL_Quit(  );
}

void app::onEvent(SDL_Event *event)
{
	if (m_states.empty()) return;
	m_states.top()->onEvent(event);
}

void app::onLoop(float deltaTime)
{
	if (m_states.empty()) return;
	m_states.top()->onLoop(deltaTime);
}

void app::rend( )
{
	SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
	SDL_RenderClear(rnd);

	renderTexture(ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Background.png"), rnd, 0, 0, SCR_W, SCR_H);
	/*SDL_Rect screenRect = { 0, 0, SCR_W, SCR_H };
	SDL_SetRenderDrawColor(rnd, 24, 24, 25, 255);
	SDL_RenderFillRect(rnd, &screenRect);
	SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);*/

	if (m_states.empty()) return;
	m_states.top()->onRender(rnd, &spriteFont);

	spriteFont.draw(rnd, toString((int)fps), vec2(20, 20), vec2(1.f, 1.f), ColorRGBA8(0, 255, 60, 255));

	SDL_RenderPresent( rnd );
}

int app::execute( )
{
	init(  );
	SDL_Event evt;

	const float MS_PER_SEC = 1000.f;
	const float DESIRED_FPS = 60.f;
	const float DESIRED_FRAMETIME = MS_PER_SEC / DESIRED_FPS;

	FPSLimiter fpsLimiter;
	fpsLimiter.init(DESIRED_FPS);

	float previousTicks = SDL_GetTicks();

	while ( !m_states.empty() )
	{
		fpsLimiter.begin();

		while (SDL_PollEvent(&evt))
			onEvent(&evt);

		float currentTicks = SDL_GetTicks();
		float frameTime = currentTicks - previousTicks;
		previousTicks = currentTicks;

		float totalDelta = frameTime / DESIRED_FRAMETIME;

		onLoop(totalDelta);
		rend();	//Отрисовка

		fps = fpsLimiter.end();
	}
	destroyApp(  );
	return 0;
}

void app::pushState(BaseState * state)
{
	m_states.push(state);
	m_states.top()->onInit(rnd, &spriteFont);
}

void app::popState()
{
	if (!m_states.empty())
	{
		delete m_states.top();
		m_states.pop();
	}
}

app::app( )
{ }


app::~app( )
{ }
