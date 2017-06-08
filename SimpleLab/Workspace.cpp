#include "Workspace.h"
#include "prefs.h"
#include <cctype>

Workspace::Workspace()
{
	writeLine();
}


Workspace::~Workspace()
{
}

void Workspace::init(int symbolWidth, int symbolHeight)
{
	m_symbolWidth = symbolWidth;
	m_symbolHeight = symbolHeight;
}

void Workspace::writeLine(const std::string& text)
{
	m_lines.push_back(text);
	m_cursor.goTo(text.length());
	slideLines();
}

void Workspace::insertToCursor(const std::string & text)
{
	m_lines.back().insert(m_cursor.getPos(), text);
}

void Workspace::onEvent(SDL_Event *event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_RETURN:
			writeLine();
			break;

		case SDLK_BACKSPACE:
			if (m_cursor.getPos() > 0)
			{
				m_lines.back().erase(m_cursor.getPos() - 1, 1);
				m_cursor.goTo(m_cursor.getPos() - 1);
			}
			break;
		case SDLK_LEFT:
			if (m_cursor.getPos() > 0)
			{
				m_cursor.goTo(m_cursor.getPos() - 1);
			}
			break;
		case SDLK_RIGHT:
			if (m_cursor.getPos() < m_lines.back().length())
			{
				m_cursor.goTo(m_cursor.getPos() + 1);
			}
			break;
		}
		break;
	case SDL_TEXTINPUT:
	{
		for(int i = 0; i < strlen(event->text.text); ++i)
			if (std::isprint(event->text.text[i]))
			{
				m_lines.back().insert(m_cursor.getPos(), 1, event->text.text[i]);
				m_cursor.goTo(m_cursor.getPos() + 1);
			}
		break;
	}
#ifdef _ANDROID_
	case SDL_FINGERDOWN:
	{
		int x = event->tfinger.x * SCR_W;
		int y = event->tfinger.y * SCR_H;
#else
	case SDL_MOUSEBUTTONDOWN:
	{
		int x = event->button.x;
		int y = event->button.y;
#endif
		int curPos = (x - WORKSPACE_START_X + m_symbolWidth / 2) / m_symbolWidth;
		
		if (curPos < 0)
			curPos = 0;
		else if (curPos >= m_lines.back().length())
			curPos = m_lines.back().length();
		
		m_cursor.goTo(curPos);
		
		break;
	}
	}
}

void Workspace::update(float deltaTime)
{
	m_cursor.update(deltaTime);
}

void Workspace::render(SDL_Renderer * renderer, SpriteFont & font)
{
	int h = WORKSPACE_START_Y;
	for (auto &line : m_lines)
	{
		font.draw(renderer, line, vec2(WORKSPACE_START_X, h), vec2(1, 1), ColorRGBA8(255, 255, 0, 255));
		h += WORKSPACE_LINE_HEIGHT;
	}
	if (m_cursor.show())
	{
		SDL_Rect r;
		r.w = 3;
		r.h = m_symbolHeight;
		r.x = m_cursor.getPos() * m_symbolWidth - 2 + WORKSPACE_START_X;
		r.y = (m_lines.size() - 1) * WORKSPACE_LINE_HEIGHT + WORKSPACE_START_Y;

		SDL_SetRenderDrawColor(renderer, 185, 185, 185, 255);
		SDL_RenderFillRect(renderer, &r);
	}
}

const std::string& Workspace::getLastLine() const
{
	return m_lines.back();
}

std::string& Workspace::getLastLine()
{
	return m_lines.back();
}

void Workspace::shiftCursor(int n)
{
	if (m_lines.back().length() == 0) return;
	int newPos = m_cursor.getPos() + n;
	newPos %= m_lines.back().length();
	m_cursor.goTo(newPos);
}

void Workspace::slideLines()
{
	while(m_lines.size() > MAX_LINES)
	{
		m_lines.pop_front();
	}
}
