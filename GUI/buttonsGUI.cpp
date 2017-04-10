#include "hdr.h"

int butttonPush( int code )
{
	

}

void buttonsDraw( SDL_Renderer &rnd )
{
	SDL_SetRenderDrawColor( &rnd, 0, 0, 0, SDL_ALPHA_OPAQUE );
	SDL_RenderClear( &rnd );
	SDL_SetRenderDrawColor( &rnd, 128, 128, 128, SDL_ALPHA_OPAQUE );

	for ( int i = 0; i < 6; i++ )	//6 - кол-во рисуемых кнопок минус кнопка выхода
	{

	}

}
