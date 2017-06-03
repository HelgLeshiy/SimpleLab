#include "Workspace.h"



Workspace::Workspace()
{
	writeLine();
}


Workspace::~Workspace()
{
}

void Workspace::writeLine(const std::string& text)
{
	m_lines.push_back(text);
	slideLines();
}

void Workspace::onEvent(SDL_Event *event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		if (event->key.keysym.sym == SDLK_RETURN)
			writeLine();
		else if (event->key.keysym.sym == SDLK_BACKSPACE)
		{
			if (m_lines.back().length() > 0)
			{
				m_lines.back().pop_back();
			}
		}
		break;
	case SDL_TEXTINPUT:
	{
		std::string inp;
		m_lines.back() += event->text.text;
		break;
	}
	}
}

const std::string& Workspace::getLastLine() const
{
	return m_lines.back();
}

void Workspace::slideLines()
{
	while(m_lines.size() > MAX_LINES)
	{
		m_lines.pop_front();
	}
}
