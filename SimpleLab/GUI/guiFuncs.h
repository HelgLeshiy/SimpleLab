#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

void renderTexture( SDL_Texture *tex, SDL_Renderer *rend, int x, int y, int w, int h );
void renderTexture( SDL_Texture *tex, SDL_Renderer *ren, int x, int y );
SDL_Texture *renderText( char *text, char *fontFile, SDL_Color textColr, int fontSize, SDL_Renderer *rend );