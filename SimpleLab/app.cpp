#include "app.h"
#include <SDL2/SDL_ttf.h>
#include <sstream>

#define SCR_W 640
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

	workspace.push_back( "" );
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
			//if ( ( x < 100 ) && ( x > 0 ) && ( y > 0 ) && ( y < 60 ) )
			//{
			//	buttonDraw( rnd, "Undo", 0, 0, 100, 60, PrsBtColr, tbCol );
			//}
			//else if ( ( x < 200 ) && ( x > 100 ) && ( y > 0 ) && ( y < 60 ) )
			//{
			//	buttonDraw( rnd, "Redo", 100, 0, 100, 60, PrsBtColr, tbCol );
			//}
			//else if ( ( x < 300 ) && ( x > 200 ) && ( y > 0 ) && ( y < 60 ) )
			//{
			//	buttonDraw( rnd, "ClearAll", 200, 0, 100, 60, PrsBtColr, tbCol );
			//}
			//else if ( ( x < 400 ) && ( x > 300 ) && ( y > 0 ) && ( y < 60 ) )
			//{
			//	buttonDraw( rnd, "Save", 300, 0, 100, 60, PrsBtColr, tbCol );
			//}
			if ( x > 600 && y < 60 )
			{
				//buttonDraw( rnd, "X", 600, 0, 60, 60, PrsClsBtn, BlackColr );
				quitting = true;
			}
			//else if ( ( x < 60 ) && ( x > 0 ) && ( y > 1088 ) && ( y < 1027 ) )
			//{
			//	buttonDraw( rnd, "0", 0, 1088, 59, 60, PrsBtColr, tbCol );
			//}

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
		//case SDL_FINGERUP:
		//{
		//	buttonDraw( rnd, "Undo", 0, 0, 100, 60, bCols, tbCol );
		//	buttonDraw( rnd, "Redo", 100, 0, 100, 60, bCols, tbCol );
		//	buttonDraw( rnd, "ClearAll", 200, 0, 100, 60, bCols, tbCol );
		//	buttonDraw( rnd, "Save", 300, 0, 100, 60, bCols, tbCol );
		//	//buttonDraw( rnd, "Load", 400, 0, 100, 60, bCols, tbCol );
		//	//buttonDraw( rnd, "GraphOut", 500, 0, 100, 60, bCols, tbCol );
		//	buttonDraw( rnd, "X", 660, 0, 60, 60, ClosBtCol, bCols );
		//}
		//break;
		case SDL_KEYDOWN:
			if ( evt->key.keysym.sym == SDLK_RETURN )
			{
				double result = parser.parse( workspace.back(  ), global );
				std::string varName = parser.getLastVar(  );
				varName += " = " + dtoa( result );
				workspace.push_back( varName );
				workspace.emplace_back( "" );

				if ( workspace.size(  ) > 7 )
				{
					workspace.pop_front(  );
					workspace.pop_front(  );
				}

				//text.clear(  );
			}
			break;
		case SDL_TEXTINPUT:
		{
			std::string inp;
			//workspace.emplace_back( evt->text.text );
			workspace.back(  ) += evt->text.text;
		}
		break;
		//case SDL_TEXTEDITING:
		{
			//composition = event.edit.text;
			//cursor = event.edit.start;
			//selection_len = event.edit.length;
		}
		//break;
	}
}
void app::loop( )
{

}
void app::rend( )
{
	SDL_SetRenderDrawColor( rnd, 0, 0, 0, 255 );
	SDL_RenderClear( rnd );

	//void buttonDraw( SDL_Renderer *renderer, SpriteFont &spriteFont, const std::string& text, const vec2& pos, const vec2 &dims, const vec2& scaling, const ColorRGBA8& color, const ColorRGBA8 &butCol )

	buttonDraw( rnd, spriteFont, "Undo", vec2(0,0), vec2( 100, 60 ), bCols, tbCol );
	buttonDraw( rnd, spriteFont, "Redo", vec2(100,0), vec2( 100, 60 ), bCols, tbCol );
	buttonDraw( rnd, spriteFont, "Cls", vec2(200,0), vec2( 100, 60 ), bCols, tbCol );
	buttonDraw( rnd, spriteFont, "Save", vec2(300,0), vec2( 100, 60 ), bCols, tbCol );
	buttonDraw( rnd, spriteFont, "X", vec2(400,0), vec2( 60, 60 ), ClosBtCol, BlackColr );

	int h = 60;
	for ( auto &line:workspace )
	{
		spriteFont.draw( rnd, line, vec2( 2, h ), vec2( 1, 1 ), ColorRGBA8( 255, 255, 0, 255 ) );	//TODO: why -260, spriteFont???
		h += 60;
	}
	SDL_RenderPresent( rnd );
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
