#include "SimpleButton.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void SimpleButton::init(const std::string& text, const ColorRGBA8& textColor,
	const ColorRGBA8& fillColor, const ColorRGBA8& pressColor,
	std::function<void(void)> cbFunction)
{
	m_text = text;
	m_textColor = textColor;
	m_fillColor = fillColor;
	m_pressColor = pressColor;
	m_cbFunction = cbFunction;
}

void SimpleButton::render(SDL_Renderer *renderer, SpriteFont& spriteFont)
{
	vec2 absPos(0.f, 0.f);
	if (m_parent != nullptr)
	{
		absPos = m_parent->getPosition() + m_parent->getInnerStartPos();
	}
	absPos += m_position;

	SDL_Rect button;
	button.x = absPos.x;
	button.y = absPos.y;
	button.w = m_dimensions.x;
	button.h = m_dimensions.y;
	if (m_pressed)
		SDL_SetRenderDrawColor(renderer, m_pressColor.r, m_pressColor.g, m_pressColor.b, m_pressColor.a);
	else
		SDL_SetRenderDrawColor(renderer, m_fillColor.r, m_fillColor.g, m_fillColor.b, m_fillColor.a);

	SDL_RenderFillRect(renderer, &button);

	spriteFont.draw(renderer, m_text, vec2(absPos.x + m_dimensions.x / 2, absPos.y + m_dimensions.y / 2 - spriteFont.getFontHeight() / 2), vec2(1.f, 1.f), m_textColor, FontAlign::CENTERED);
}

void SimpleButton::onTouch(int x, int y)
{
}

void SimpleButton::onDetouch(int x, int y)
{
	if (m_cbFunction)
		m_cbFunction();
}

void SimpleButton::onSwipe(int x, int y, float dx, float dy)
{
	m_pressed = false;
}
