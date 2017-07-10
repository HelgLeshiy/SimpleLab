#include "Layout.h"
#include "../GUI/guiFuncs.h"
#include "../prefs.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void Layout::init(SDL_Texture *texture)
{
	m_texture = texture;
}

void Layout::render(SDL_Renderer *renderer, SpriteFont& spriteFont)
{
	renderTexture(m_texture, renderer, m_position.x, m_position.y, m_dimensions.x, m_dimensions.y);
}

void Layout::onSwipe(int x, int y, float dx, float dy)
{
	if (-dx > SWIPE_DISTANCE && layoutState == LayoutState::IDLE && m_position.x > SCR_W - m_dimensions.x / 2 && x > SCR_W - WORKSPACE_START_X)
	{
		layoutState = LayoutState::SWIPE_LEFT;
		swipe = 0.f;
	}
	else if (dx > SWIPE_DISTANCE && layoutState == LayoutState::IDLE && m_position.x < SCR_W - m_dimensions.x / 2)
	{
		layoutState = LayoutState::SWIPE_RIGHT;
		swipe = 0.f;
	}
	else if(layoutState == LayoutState::IDLE && m_position.x < SCR_W - m_dimensions.x / 2)
	{
		setInnerStartPosition(getInnerStartPos() + vec2(0, dy));
	}
}

void Layout::onUpdate(float deltaTime)
{
	if (layoutState == LayoutState::SWIPE_LEFT)
	{
		move(vec2(-10.f, 0.f));
		if (m_position.x < SCR_W - m_dimensions.x)
		{
			setRect(vec2(SCR_W - m_dimensions.x, 0.f), m_dimensions);
			layoutState = LayoutState::IDLE;
		}
	}
	else if (layoutState == LayoutState::SWIPE_RIGHT)
	{
		move(vec2(10.f, 0.f));
		if (m_position.x > SCR_W)
		{
			setRect(vec2(SCR_W, 0.f), m_dimensions);
			layoutState = LayoutState::IDLE;
		}
	}
}