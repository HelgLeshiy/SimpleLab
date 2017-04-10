#pragma once

#include <SDL.h>
#include <iostream>
#include <cmath>

SDL_Window *wnd = nullptr;
SDL_Renderer *rnd = nullptr;

#undef main

#define	WIDTH_SCR	1280
#define	HEIGH_SCR	720
#define	DEPTH		8

#define	CLOS	0
#define	SAVE	1
#define	LOAD	2
#define	UNDO	3
#define	REDO	4
#define	GRPH	5
#define	TEXT	6

using namespace std;

int butttonPush( int code );
void buttonsDraw( SDL_Renderer &rnd );

SDL_Texture *LoadImage( char *file )
{
	SDL_Surface *loadedImage = nullptr;
	SDL_Texture *texture = nullptr;
	loadedImage = SDL_LoadBMP( file );
	if ( loadedImage != nullptr )
	{
		texture = SDL_CreateTextureFromSurface( rnd, loadedImage );
		SDL_FreeSurface( loadedImage );
	}
	else
		cout << SDL_GetError( ) << endl;
	return texture;
}

void ApplySurface( int x, int y, SDL_Texture *tex, SDL_Renderer *rend )
{
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	SDL_QueryTexture( tex, nullptr, nullptr, &pos.w, &pos.h );
	SDL_RenderCopy( rend, tex, nullptr, &pos );
}