#include "SpriteFont.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <stdexcept>

SpriteFont::SpriteFont( )
{ }


SpriteFont::~SpriteFont( )
{
	if ( m_texture != nullptr )
		SDL_DestroyTexture( m_texture );
}

void SpriteFont::init( SDL_Renderer *renderer, const std::string& fontSheetFile, int rows, int columns )
{
	SDL_Surface *surf = IMG_Load( fontSheetFile.c_str( ) );
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