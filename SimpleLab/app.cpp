#include "app.h"
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include "Functions\Functions.h"
#include "ResourceManager.h"
#include "prefs.h"

std::string dtoa( double a )
{
	std::stringstream ss;
	ss << a;
	return ss.str(  );
}

void app::init( )
{
	SDL_Init( SDL_INIT_EVERYTHING );
	IMG_Init( IMG_INIT_PNG );
	TTF_Init(  );

	wnd = SDL_CreateWindow( "SimpleLab for Smartphones", 100, 100, SCR_W, SCR_H, 0 );
	rnd = SDL_CreateRenderer( wnd, -1, SDL_RENDERER_SOFTWARE );
	global = new Namescope(  );
	spriteFont.init( rnd, "data/images/Bisasam_20x20_ascii.png", 16, 16 );
	global->setVar( std::make_shared< TypedValue<double> >( 3.141592653589793 ), "pi" );
	global->setVar( std::make_shared< TypedValue<double> >( 2.718281828459045 ), "exp" );

	SDL_Rect txtInp;
	txtInp.x = 0;
	txtInp.y = 860;
	txtInp.w = 720;
	txtInp.h = 64;

	SDL_RenderDrawRect( rnd, &txtInp );

	global->installFunction( f_sin, 1, "sin" );
	global->installFunction( f_cos, 1, "cos" );
	global->installFunction( f_tan, 1, "tan" );
	global->installFunction( f_ctan, 1, "ctan" );
	global->installFunction( f_sinh, 1, "sinh" );
	global->installFunction( f_cosh, 1, "cosh" );
	global->installFunction( f_tanh, 1, "tanh" );
	global->installFunction( f_ctanh, 1, "ctanh" );
	global->installFunction( f_logn, 1, "ln" );
	global->installFunction( f_log, 2, "log" );
	global->installFunction( f_lengthStr, 1, "strlen" );
	global->installFunction( f_random, 2, "rand" );
	global->installFunction( f_integral, 3, "int" );
	global->installFunction( f_minFunc, 3, "minF" );
	global->installFunction( f_maxFunc, 3, "maxF" );

	initWidgets();
	workspace.init(20, 20);
}
void app::destroyApp( )
{
	delete global;
	SDL_DestroyRenderer( rnd );
	SDL_DestroyWindow( wnd );
	TTF_Quit(  );
	IMG_Quit(  );
	SDL_Quit(  );
}
void app::event( SDL_Event *evt )
{
	switch ( evt->type )
	{
		case SDL_QUIT:
			quitting = true;
			break;
#ifdef _ANDROID_
		case SDL_FINGERDOWN:
		{
			int x = evt->tfinger.x * SCR_W;
			int y = evt->tfinger.y * SCR_H;
#else
		case SDL_MOUSEBUTTONDOWN:
		{
			int x = evt->button.x;
			int y = evt->button.y;
#endif
			touch = true;
			touchPos.x = x;
			touchPos.y = y;

			if (!SDL_IsTextInputActive())
			{
				SDL_StartTextInput( );
				keyboard = true;
			}
			//spriteFont.draw(rnd, text.c_str(  ), vec2(720, 64), vec2(1.f, 1.f), ColorRGBA8(255, 255, 0, 255), FontAlign::LEFT);

			break;
		}
#ifdef _ANDROID_
		case SDL_FINGERUP:
		{
			int x = evt->tfinger.x * SCR_W;
			int y = evt->tfinger.y * SCR_H;
#else
		case SDL_MOUSEBUTTONUP:
		{
			int x = evt->button.x;
			int y = evt->button.y;
#endif
			touch = false;
			if (touchPos.x - x > SWIPE_DISTANCE && layoutState == LayoutState::IDLE && layout->getPosition().x > SCR_W - layout->getDimensions().x / 2)
			{
				layoutState = LayoutState::SWIPE_LEFT;
				swipe = 0.f;
			}
			else if (x - touchPos.x > SWIPE_DISTANCE && layoutState == LayoutState::IDLE && layout->getPosition().x < SCR_W - layout->getDimensions().x / 2)
			{
				layoutState = LayoutState::SWIPE_RIGHT;
				swipe = 0.f;
			}
		}
		break;
		case SDL_KEYDOWN:
			if ( evt->key.keysym.sym == SDLK_RETURN )
			{
				double result;
				try
				{
					result = parser.parse( workspace.getLastLine(), global );
				}
				catch ( std::exception &ex )
				{
					workspace.writeLine(ex.what());
					break;
				}
				std::string varName = "  " + parser.getLastVar();
				varName += " = " + dtoa(result);
				workspace.writeLine(varName);
			}
			break;
	}

	workspace.onEvent(evt);

	for (auto widget : widgets)
		widget->onEvent(evt);
}

void app::loop( )
{
	if (layoutState == LayoutState::SWIPE_LEFT)
	{
		layout->move(vec2(-10.f, 0.f));
		if (layout->getPosition().x < SCR_W - layout->getDimensions().x)
		{
			layout->setRect(vec2(SCR_W - layout->getDimensions().x, 0.f), layout->getDimensions());
			layoutState = LayoutState::IDLE;
		}
	}
	else if (layoutState == LayoutState::SWIPE_RIGHT)
	{
		layout->move(vec2(10.f, 0.f));
		if (layout->getPosition().x > SCR_W)
		{
			layout->setRect(vec2(SCR_W, 0.f), layout->getDimensions());
			layoutState = LayoutState::IDLE;
		}
	}

	workspace.update(1.f);
}

void app::rend( )
{
	SDL_SetRenderDrawColor( rnd, 0, 0, 0, 255 );
	SDL_RenderClear( rnd );

	renderTexture(ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Background.png"), rnd, 0, 0, SCR_W, SCR_H);

	workspace.render(rnd, spriteFont);

	for (auto widget : widgets)
		widget->render(rnd, spriteFont);

	SDL_RenderPresent( rnd );
}

void app::initWidgets()
{
	std::vector<TexturedButton*> buttons;
	int posX = 64;

	// Undo
	buttons.push_back(new TexturedButton());
	buttons.back()->init(ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Unpressed_Undo.png"),
						 ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Pressed_Undo.png"));
	buttons.back()->setRect(vec2(posX, 0), vec2(100, 60));
	posX += 77;

	// Redo
	buttons.push_back(new TexturedButton());
	buttons.back()->init(ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Unpressed_Redo.png"),
						 ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Pressed_Redo.png"));
	buttons.back()->setRect(vec2(posX, 0), vec2(100, 60));
	posX += 77;

	// Cls
	buttons.push_back(new TexturedButton());
	buttons.back()->init(ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Unpressed_CLS.png"),
						 ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Pressed_CLS.png"));
	buttons.back()->setRect(vec2(posX, 0), vec2(100, 60));
	posX += 77;

	// Save
	buttons.push_back(new TexturedButton());
	buttons.back()->init(ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Unpressed_Save.png"),
						 ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Pressed_Save.png"));
	buttons.back()->setRect(vec2(posX, 0), vec2(100, 60));
	posX += 77;

	// X
	buttons.push_back(new TexturedButton());
	buttons.back()->init(ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Unpressed_EXIT.png"),
						 ResourceManager::getTexture(rnd, "data/textures/SimpleLab_Button_Pressed_EXIT.png"),
						 [this]() { quitting = true; });
	buttons.back()->setRect(vec2(SCR_W - 64 - 84, 6), vec2(84, 54));

	layout = new Layout;
	layout->init(ResourceManager::getTexture(rnd, "data/textures/layout.png"));
	layout->setInnerStartPosition(vec2(10, 10));
	layout->setRect(vec2(SCR_W, 0), vec2(200, SCR_H));

	TexturedButton *test = new TexturedButton(layout);
	test->init(ResourceManager::getTexture(rnd, "data/textures/testButtonReleased.png"),
			   ResourceManager::getTexture(rnd, "data/textures/testButtonPressed.png"),
			   [this]() { workspace.writeLine("textured button pressed!"); });
	test->setRect(vec2(0.f, 0.f), vec2(120, 60));

	for(auto button : buttons)
		widgets.push_back(button);

	widgets.push_back(layout);
	widgets.push_back(test);
}

int app::execute( )
{
	init(  );
	SDL_Event evt;
	while ( !quitting )
	{
		while ( SDL_PollEvent( &evt ) )
			event ( &evt );
		loop(  );	//Логика
		rend(  );	//Отрисовка
		SDL_Delay( 50 );
	}
	destroyApp(  );
	return 0;
}

app::app( )
{ }


app::~app( )
{ }
