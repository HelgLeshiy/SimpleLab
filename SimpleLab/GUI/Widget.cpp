#include "Widget.h"
#include "../guiFuncs.h"

#include "../SpriteFont.h"

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
	if(m_pressed)
		SDL_SetRenderDrawColor(renderer, m_pressColor.r, m_pressColor.g, m_pressColor.b, m_pressColor.a);
	else
		SDL_SetRenderDrawColor(renderer, m_fillColor.r, m_fillColor.g, m_fillColor.b, m_fillColor.a);

	SDL_RenderFillRect(renderer, &button);

	spriteFont.draw(renderer, m_text, vec2(absPos.x + m_dimensions.x / 2, absPos.y + m_dimensions.y / 2 - spriteFont.getFontHeight() / 2), vec2(1.f, 1.f), m_textColor, FontAlign::CENTERED);
}

void SimpleButton::onEvent(SDL_Event *event)
{
	vec2 absPos(0.f, 0.f);
	if (m_parent != nullptr)
	{
		absPos = m_parent->getPosition() + m_parent->getInnerStartPos();
	}
	absPos += m_position;

#ifdef _ANDROID_
	if (event->type == SDL_FINGERDOWN)
	{
		int x = event->tfinger.x * SCR_W;
		int y = event->tfinger.y * SCR_H;
#else
	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		int x = event->button.x;
		int y = event->button.y;
#endif

		if (x > absPos.x && x < absPos.x + m_dimensions.x && y > absPos.y && y < absPos.y + m_dimensions.y)
		{
			if (!m_pressed)
			{
				m_pressed = true;
				if(m_cbFunction)
					m_cbFunction();
			}
		}
	}
#ifdef _ANDROID_
	else if (event->type == SDL_FINGERUP)
		{
			int x = event->tfinger.x * SCR_W;
			int y = event->tfinger.y * SCR_H;
#else
	else if (event->type == SDL_MOUSEBUTTONUP)
		{
			int x = event->button.x;
			int y = event->button.y;

			m_pressed = false;
		}
#endif
}

void TexturedButton::init(SDL_Texture *releaseTexture, SDL_Texture *pressTexture, std::function<void(void)> cbFunction /*= nullptr*/)
{
	m_releaseTexture = releaseTexture;
	m_pressTexture = pressTexture;
	m_cbFunction = cbFunction;
}

void TexturedButton::render(SDL_Renderer *renderer, SpriteFont& spriteFont)
{
	vec2 absPos(0.f, 0.f);
	if (m_parent != nullptr)
	{
		absPos = m_parent->getPosition() + m_parent->getInnerStartPos();
	}
	absPos += m_position;
	if (!m_pressed)
		renderTexture(m_releaseTexture, renderer, absPos.x, absPos.y, m_dimensions.x, m_dimensions.y);
	else
		renderTexture(m_pressTexture, renderer, absPos.x, absPos.y, m_dimensions.x, m_dimensions.y);
}

void TexturedButton::onEvent(SDL_Event *event)
{
	vec2 absPos(0.f, 0.f);
	if (m_parent != nullptr)
	{
		absPos = m_parent->getPosition() + m_parent->getInnerStartPos();
	}
	absPos += m_position;

#ifdef _ANDROID_
	if (event->type == SDL_FINGERDOWN)
	{
		int x = event->tfinger.x * SCR_W;
		int y = event->tfinger.y * SCR_H;
#else
	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		int x = event->button.x;
		int y = event->button.y;
#endif

		if (x > absPos.x && x < absPos.x + m_dimensions.x && y > absPos.y && y < absPos.y + m_dimensions.y)
		{
			if (!m_pressed)
			{
				m_pressed = true;
				if (m_cbFunction)
					m_cbFunction();
			}
		}
	}
#ifdef _ANDROID_
	else if (event->type == SDL_FINGERUP)
	{
		int x = event->tfinger.x * SCR_W;
		int y = event->tfinger.y * SCR_H;
#else
	else if (event->type == SDL_MOUSEBUTTONUP)
	{
		int x = event->button.x;
		int y = event->button.y;

		m_pressed = false;
	}
#endif
}

void Layout::init(SDL_Texture *texture)
{
	m_texture = texture;
}

void Layout::render(SDL_Renderer *renderer, SpriteFont& spriteFont)
{
	renderTexture(m_texture, renderer, m_position.x, m_position.y, m_dimensions.x, m_dimensions.y);
}

void Layout::onEvent(SDL_Event *event)
{
	// Empty
}
