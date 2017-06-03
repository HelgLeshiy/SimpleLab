#pragma once
#include <list>
#include <SDL2/SDL.h>

const int MAX_LINES = 7;

class Workspace
{
public:
	Workspace();
	~Workspace();

	void writeLine(const std::string& text = "");
	void onEvent(SDL_Event *event);
	const std::string& getLastLine() const;

	std::list < std::string >::const_iterator begin() const { return m_lines.begin(); }
	std::list < std::string >::const_iterator end() const { return m_lines.end(); }

private:
	void slideLines();

	std::list < std::string > m_lines;
};

