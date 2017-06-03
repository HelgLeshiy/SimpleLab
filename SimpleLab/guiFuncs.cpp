#include "guiFuncs.h"
void renderTexture( SDL_Texture *tex, SDL_Renderer *rend, int x, int y, int w, int h )
{
	SDL_Rect d;
	d.x = x; d.y = y; d.w = w; d.h = h;
	SDL_RenderCopy( rend, tex, NULL, &d );
}

void renderTexture( SDL_Texture *tex, SDL_Renderer *ren, int x, int y )
{
	int w, h;
	SDL_QueryTexture( tex, NULL, NULL, &w, &h );
	renderTexture( tex, ren, x, y, w, h );
}

SDL_Texture *renderText( char *text, char *fontFile, SDL_Color textColr, int fontSize, SDL_Renderer *rend )
{
	TTF_Font *font = TTF_OpenFont( fontFile, fontSize );
	SDL_Surface *tsrf = TTF_RenderText_Blended( font, text, textColr );
	SDL_Texture *texT = SDL_CreateTextureFromSurface( rend, tsrf );
	SDL_FreeSurface( tsrf );
	return texT;
}