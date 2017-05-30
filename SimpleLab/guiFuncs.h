#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "SpriteFont.h"

#define BUTFONTSIZ 20

struct Button
{
	SDL_Renderer *rend;
	char *text;
	int x, y, w, h;
	SDL_Color btnCol;
	SDL_Color txtColr;
	int id;
};

void renderTexture( SDL_Texture *tex, SDL_Renderer *rend, int x, int y, int w, int h );
void renderTexture( SDL_Texture *tex, SDL_Renderer *ren, int x, int y );
SDL_Texture *renderText( char *text, char *fontFile, SDL_Color textColr, int fontSize, SDL_Renderer *rend );
void buttonDraw( SDL_Renderer *renderer, SpriteFont &spriteFont, const std::string& text, const vec2& pos, const vec2 &dims, const ColorRGBA8& color, const ColorRGBA8 &butCol );