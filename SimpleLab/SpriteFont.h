#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "GUI/gfx.h"

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
	int getFontHeight() const { return m_symbHeight; }
	int getFontWidth() const { return m_symbWidth; }
	SDL_Surface * CreateFontMap( SDL_Renderer * rnd, const char * fontFile, SDL_Color textColor, int rows, int clms );
	int getTextWidth(const std::string& text, const vec2& scaling) const { return text.length() * scaling.x * m_symbWidth; }
	int getSymbolWidth() const { return m_symbWidth; }

private:
	SDL_Texture *m_texture = nullptr;
	int m_texWidth = 0;
	int m_texHeight = 0;
	int m_rows = 0;
	int m_columns = 0;
	int m_symbWidth = 0;
	int m_symbHeight = 0;
};
