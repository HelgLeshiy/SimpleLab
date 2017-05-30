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

//void buttonDraw( SDL_Renderer *rend, char *text, int x, int y, int w, int h, SDL_Color butColr, SDL_Color textColr )
void buttonDraw( SDL_Renderer *renderer, SpriteFont &spriteFont, const std::string& text, const vec2& pos, const vec2 &dims, const ColorRGBA8& color, const ColorRGBA8 &butCol )
{
	SDL_Rect button;
	button.x = pos.x;
	button.y = pos.y;
	button.w = dims.x;
	button.h = dims.y;
	SDL_SetRenderDrawColor( renderer, butCol.r, butCol.g, butCol.b, butCol.a );
	SDL_RenderFillRect( renderer, &button );
	//SDL_RenderDrawRect( renderer, &button );

	spriteFont.draw(renderer, text, vec2 (pos.x + dims.x  / 2, pos.y + dims.y / 2), vec2(1.f, 1.f), color, FontAlign::CENTERED);

	//SDL_Texture *imagText = renderText( text, "data/fonts/monospace.ttf", textColr, BUTFONTSIZ, rend );
	//int x1, y1;
	//SDL_QueryTexture( imagText, NULL, NULL, &x1, &y1 );
	//int xx = x / 2, yy = y / 2;
	//SDL_RenderClear( rend );
	//int hBut = imagText->h;
	//int wBut = imagText->w;
	//renderTexture( imagText, rend, x + 0.45f * h, y );

}