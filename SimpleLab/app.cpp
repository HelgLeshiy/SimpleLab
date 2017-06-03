#include "app.h"
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include "Functions\Functions.h"
#include "ResourceManager.h"

#define SCR_W 720
#define SCR_H 480

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
			if ( x > 600 && y < 60 )
			{
				quitting = true;
			}

			if ( keyboard )
			{
				SDL_StopTextInput( );
				keyboard = false;
			}
			else
			{
				SDL_StartTextInput( );
				keyboard = true;
			}
			//spriteFont.draw(rnd, text.c_str(  ), vec2(720, 64), vec2(1.f, 1.f), ColorRGBA8(255, 255, 0, 255), FontAlign::LEFT);

			break;
		}
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

}
void app::rend( )
{
	SDL_SetRenderDrawColor( rnd, 0, 0, 0, 255 );
	SDL_RenderClear( rnd );

	//void buttonDraw( SDL_Renderer *renderer, SpriteFont &spriteFont, const std::string& text, const vec2& pos, const vec2 &dims, const vec2& scaling, const ColorRGBA8& color, const ColorRGBA8 &butCol )

	

	int h = 85;
	for ( auto &line:workspace )
	{
		spriteFont.draw( rnd, line, vec2( 2, h ), vec2( 1, 1 ), ColorRGBA8( 255, 255, 0, 255 ) );	//TODO: why -260, spriteFont???
		h += 32;
	}

	for (auto widget : widgets)
		widget->render(rnd, spriteFont);

	SDL_RenderPresent( rnd );
}

void app::initWidgets()
{
	std::vector<SimpleButton*> buttons;

	buttons.push_back(new SimpleButton());
	buttons.back()->init("Undo", tbCol, bCols, PrsBtColr);
	buttons.back()->setRect(vec2(0, 0), vec2(100, 60));

	buttons.push_back(new SimpleButton());
	buttons.back()->init("Redo", tbCol, bCols, PrsBtColr);
	buttons.back()->setRect(vec2(100, 0), vec2(100, 60));

	buttons.push_back(new SimpleButton());
	buttons.back()->init("Cls", tbCol, bCols, PrsBtColr);
	buttons.back()->setRect(vec2(200, 0), vec2(100, 60));

	buttons.push_back(new SimpleButton());
	buttons.back()->init("Save", tbCol, bCols, PrsBtColr);
	buttons.back()->setRect(vec2(300, 0), vec2(100, 60));

	buttons.push_back(new SimpleButton());
	buttons.back()->init("X", BlackColr, ClosBtCol, PrsClsBtn);
	buttons.back()->setRect(vec2(600, 0), vec2(60, 60));

	TexturedButton *test = new TexturedButton;
	test->init(ResourceManager::getTexture(rnd, "data/textures/testButtonReleased.png"),
		ResourceManager::getTexture(rnd, "data/textures/testButtonPressed.png"),
		[this]() { workspace.writeLine("textured button pressed!"); });
	test->setRect(vec2(SCR_W/2, SCR_H/2), vec2(120, 60));

	for(auto button : buttons)
		widgets.push_back(button);

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
