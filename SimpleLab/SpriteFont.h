#pragma once

#include <SDL2/SDL.h>
#include <string>

struct vec2
{
	vec2( ) = default;
	vec2( float X, float Y ) : x( X ), y( Y ) { }
	float x, y;
};

struct ColorRGBA8
{
	ColorRGBA8( ) : r( 0 ), g( 0 ), b( 0 ), a( 0 ) { }
	ColorRGBA8( unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a = 0 ) : r( _r ), g( _g ), b( _b ), a( _a ) { }
	unsigned char r, g, b, a;
};

enum class FontAlign
{
	CENTERED,
	LEFT,
	RIGHT
};

class SpriteFont
{
public:
	SpriteFont( );
	~SpriteFont( );

	void init( SDL_Renderer *renderer, const std::string& fontSheetFile, int rows, int columns );
	void draw( SDL_Renderer *renderer, const std::string& text, const vec2& pos, const vec2& scaling, const ColorRGBA8& color, FontAlign align = FontAlign::LEFT );

private:
	SDL_Texture *m_texture = nullptr;
	int m_texWidth = 0;
	int m_texHeight = 0;
	int m_rows = 0;
	int m_columns = 0;
	int m_symbWidth = 0;
	int m_symbHeight = 0;
};