#include "MultilineEdit.h"
#include "../prefs.h"
#include <cctype>
#include <cstring>

MultilineEdit::MultilineEdit(Widget *parent)
	: Widget(parent), m_contentShift(0.f, 0.f)
{
	writeLine();
}


MultilineEdit::~MultilineEdit()
{
}

void MultilineEdit::init(int symbolWidth, int symbolHeight)
{
	m_symbolWidth = symbolWidth;
	m_symbolHeight = symbolHeight;
}

void MultilineEdit::writeLine(const std::string& text)
{
	m_lines.push_back(text);
	m_cursor.goTo(text.length());
	slideLines();
}

void MultilineEdit::insertToCursor(const std::string & text)
{
	m_lines.back().insert(m_cursor.getPos(), text);
}

void MultilineEdit::onTouch(int x, int y)
{
	if (x > SCR_W - 36) return;
	int curPos = (x - WORKSPACE_START_X - m_contentShift.x + m_symbolWidth / 2) / m_symbolWidth;
	m_pressed = true;

	if (curPos < 0)
		curPos = 0;
	else if (curPos >= m_lines.back().length())
		curPos = m_lines.back().length();

	m_cursor.goTo(curPos);
}

void MultilineEdit::onSwipe(int x, int y, float dx, float dy)
{
	if (m_pressed)
	{
		if (m_symbolWidth * (int)m_lines.back().length() < SCR_W - WORKSPACE_START_X * 2) return;
		m_contentShift.x += dx;
		if (m_contentShift.x > 0)
			m_contentShift.x = 0;
		else if (m_contentShift.x < SCR_W - WORKSPACE_START_X * 2 - m_symbolWidth * (int)m_lines.back().length())
			m_contentShift.x = SCR_W - WORKSPACE_START_X * 2 - m_symbolWidth * (int)m_lines.back().length();
	}
}

void MultilineEdit::onTextInput(const char *text)
{
	for (int i = 0; i < strlen(text); ++i)
		if (std::isprint(text[i]))
		{
			m_lines.back().insert(m_cursor.getPos(), 1, text[i]);
			m_cursor.goTo(m_cursor.getPos() + 1);
		}
}

void MultilineEdit::onKeyDown(int key)
{
	switch (key)
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
}

void MultilineEdit::onUpdate(float deltaTime)
{
	m_cursor.update(deltaTime);
}

void MultilineEdit::render(SDL_Renderer * renderer, SpriteFont & font)
{
	int h = WORKSPACE_START_Y;
	for (auto &line : m_lines)
	{
		font.draw(renderer, line, vec2(WORKSPACE_START_X, h) + m_contentShift, vec2(1, 1), ColorRGBA8(255, 255, 0, 255));
		h += WORKSPACE_LINE_HEIGHT;
	}
	if (m_cursor.show())
	{
		SDL_Rect r;
		r.w = 3;
		r.h = m_symbolHeight;
		r.x = m_cursor.getPos() * m_symbolWidth - 2 + WORKSPACE_START_X + m_contentShift.x;
		r.y = (m_lines.size() - 1) * WORKSPACE_LINE_HEIGHT + WORKSPACE_START_Y + m_contentShift.y;

		SDL_SetRenderDrawColor(renderer, 185, 185, 185, 255);
		SDL_RenderFillRect(renderer, &r);
	}
}

const std::string& MultilineEdit::getLastLine() const
{
	return m_lines.back();
}

std::string& MultilineEdit::getLastLine()
{
	return m_lines.back();
}

void MultilineEdit::shiftCursor(int n)
{
	if (m_lines.back().length() == 0) return;
	int newPos = m_cursor.getPos() + n;
	newPos %= m_lines.back().length();
	m_cursor.goTo(newPos);
}

void MultilineEdit::slideLines()
{
	while (m_lines.size() > MAX_LINES)
	{
		m_lines.pop_front();
	}
}
