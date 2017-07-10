#include "SpriteFont.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <stdexcept>

#define FONT_SIZE 20

void RenderTexture( SDL_Renderer * rnd, SDL_Texture * tex, int x, int y, int w, int h )
{
	SDL_Rect d;
	d.x = x; d.y = y; d.w = w; d.h = h;
	SDL_RenderCopy( rnd, tex, NULL, &d );
}

void RenderTexture( SDL_Renderer * rnd, SDL_Texture * tex, int x, int y )
{
	int w, h;
	SDL_QueryTexture( tex, NULL, NULL, &w, &h );
	RenderTexture( rnd, tex, x, y, w, h );
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface( source, NULL, destination, &offset );
}

int GetWidthOfSymbol( SDL_Renderer * rnd, TTF_Font * fnot )	//Функция для получения ширины символа в стороннем моноширинном шрифте (ВНИМАНИЕ! Недопустимо для monospace.ttf, так как в нём символ, похожий на символ тильды, сдвигает одну из строк влево, и функция CreateFontMap будет некорректно составлять одину из строк, из-за чего некоторые символы получившегося шрифта могут неправильно отображаться)
{
	int w, h;
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Surface * srf = nullptr;
	const char * asciiStr = "0123456789ABCDEF\0";
	srf = TTF_RenderText_Blended( fnot, ( const char * ) asciiStr, textColor );
	SDL_Texture * texT = SDL_CreateTextureFromSurface( rnd, srf );
	SDL_QueryTexture( texT, NULL, NULL, &w, &h );
	return w;
}

SpriteFont::SpriteFont( )
{ }


SpriteFont::~SpriteFont( )
{
	if ( m_texture != nullptr )
		SDL_DestroyTexture( m_texture );
}

void SpriteFont::init( SDL_Renderer *renderer, const std::string& fontSheetFile, int rows, int columns )
{
	//SDL_Surface *surf = IMG_Load( fontSheetFile.c_str( ) );
	TTF_Font * fnt = TTF_OpenFont( fontSheetFile.c_str( ), FONT_SIZE );
	SDL_Color textColor = { 255, 255, 0, 255 };
	SDL_Surface *surf = CreateFontMap( renderer, fontSheetFile.c_str( ), textColor, rows, columns );
	if ( !surf )
		throw std::runtime_error( "Failed to open font file: " + fontSheetFile + SDL_GetError( ) );

	m_texture = SDL_CreateTextureFromSurface( renderer, surf );
	m_texWidth = surf->w;
	m_texHeight = surf->h;
	m_rows = rows;
	m_columns = columns;
	m_symbWidth = m_texWidth / columns;
	m_symbHeight = m_texHeight / rows;

	SDL_FreeSurface( surf );
}

void SpriteFont::draw( SDL_Renderer *renderer, const std::string& text, const vec2& pos, const vec2& scaling, const ColorRGBA8& color, FontAlign align )
{
	SDL_Rect srcRect = { 0, 0, m_symbWidth, m_symbHeight };
	SDL_Rect dstRect = { 0, 0, m_symbWidth * scaling.x, m_symbHeight * scaling.y };
	dstRect.y = pos.y;
	SDL_SetTextureColorMod( m_texture, color.r, color.g, color.b );

	for ( int i = 0; i < text.length( ); ++i )
	{
		dstRect.x = pos.x + m_symbWidth * scaling.x * ( float ) i;
		srcRect.x = ( text[ i ] % m_rows ) * m_symbWidth;
		srcRect.y = ( text[ i ] / m_rows ) * m_symbHeight;
		if ( align == FontAlign::CENTERED )
			dstRect.x -= text.length( ) * m_symbWidth * scaling.x / 2;
		else if ( align == FontAlign::RIGHT )
			dstRect.x -= text.length( ) * m_symbWidth * scaling.x;

		SDL_RenderCopy( renderer, m_texture, &srcRect, &dstRect );
	}
}

SDL_Surface * SpriteFont::CreateFontMap( SDL_Renderer * rnd, const char * fontFile, SDL_Color textColor, int rows, int clms )
{
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	TTF_Font * fnt = TTF_OpenFont( "data/fonts/consola.ttf", FONT_SIZE );
	SDL_Surface * srf = nullptr;
	SDL_Surface * Gsrf = SDL_CreateRGBSurface( NULL, GetWidthOfSymbol( rnd, fnt ), rows * FONT_SIZE, 32, rmask, gmask, bmask, amask );
	SDL_Texture * texT = nullptr;
	unsigned char asciiSym = 0;
	int posy = -20;	//Далее будет делаться posy += FONT_SIZE, из-за чего текстура будет начинать рисоваться не с 0-й координаты, а с 20-й

	for ( int i = 0; i < rows; i++ )
	{
		char * asciiStr = new char[ 17 ];
		for ( int j = 0; j < clms; j++, asciiSym++ )
		{
			asciiStr[ j ] = asciiSym;
		}
		asciiStr[ 16 ] = '\0';
		texT = SDL_CreateTextureFromSurface( rnd, srf );
		srf = TTF_RenderText_Blended( fnt, ( const char * ) asciiStr, textColor );
		apply_surface( 0, posy += 20, srf, Gsrf );
		//RenderTexture( rnd, texT, 0, posy += FONT_SIZE );
		delete[ ]asciiStr;
	}
	//SDL_Texture * texTT = SDL_CreateTextureFromSurface( rnd, Gsrf );
	if ( !srf )
		printf( SDL_GetError( ), '\n' );
	SDL_FreeSurface( srf );
	return Gsrf;
}
