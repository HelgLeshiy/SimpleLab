#pragma once
#include <list>
#include <SDL2/SDL.h>
#include "Cursor.h"
#include "SpriteFont.h"

class Workspace
{
public:
	Workspace();
	~Workspace();

	void init(int symbolWidth, int symbolHeight);
	void writeLine(const std::string& text = "");
	void insertToCursor(const std::string& text);
	void onEvent(SDL_Event *event);
	void update(float deltaTime);
	void render(SDL_Renderer *renderer, SpriteFont& font);
	const std::string& getLastLine() const;
	std::string& getLastLine();

	void shiftCursor(int n);

	std::list < std::string >::const_iterator begin() const { return m_lines.begin(); }
	std::list < std::string >::const_iterator end() const { return m_lines.end(); }

private:
	void slideLines();
	Cursor m_cursor;
	int m_symbolWidth;
	int m_symbolHeight;
	vec2 m_contentShift;
	bool m_pressed = false;

	std::list < std::string > m_lines;
};

