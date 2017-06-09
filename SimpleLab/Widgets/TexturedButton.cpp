#include "TexturedButton.h"
#include "../GUI/guiFuncs.h"

void TexturedButton::init(SDL_Texture *releaseTexture, SDL_Texture *pressTexture, std::function<void(void)> cbFunction /*= nullptr*/)
{
	m_releaseTexture = releaseTexture;
	m_pressTexture = pressTexture;
	m_cbFunction = cbFunction;
}

void TexturedButton::setText(const std::string & text, const ColorRGBA8 & textColor)
{
	m_text = text;
	m_textColor = textColor;
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

	if (!m_text.empty())
		spriteFont.draw(renderer, m_text, vec2(absPos.x + m_dimensions.x / 2, absPos.y + m_dimensions.y / 2 - spriteFont.getFontHeight() / 2), vec2(1.f, 1.f), m_textColor, FontAlign::CENTERED);
}