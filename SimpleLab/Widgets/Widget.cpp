#include "Widget.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

bool Widget::onEvent(SDL_Event *event)
{
	vec2 absPos(0.f, 0.f);
	if (m_parent != nullptr)
	{
		absPos = m_parent->getPosition() + m_parent->getInnerStartPos();
	}
	absPos += m_position;

	switch (event->type)
	{
	case SDL_KEYDOWN:
		onKeyDown(event->key.keysym.sym);
		break;

	case SDL_KEYUP:
		onKeyUp(event->key.keysym.sym);
		break;

	case SDL_TEXTINPUT:
		onTextInput(event->text.text);
		break;

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
		if (x > absPos.x && x < absPos.x + m_dimensions.x && y > absPos.y && y < absPos.y + m_dimensions.y)
		{
			m_pressed = true;
			onTouch(x, y);
			return true;
		}
		break;
	}

#ifdef _ANDROID_
	case SDL_FINGERUP:
	{
		int x = event->tfinger.x * SCR_W;
		int y = event->tfinger.y * SCR_H;
#else
	case SDL_MOUSEBUTTONUP:
	{
		int x = event->button.x;
		int y = event->button.y;
#endif
		if (m_pressed)
		{
			m_pressed = false;
			onDetouch(x, y);
		}
	}
	break;

#ifdef _ANDROID_
	case SDL_FINGERMOTION:
	{
		int x = event->tfinger.x * SCR_W;
		int y = event->tfinger.y * SCR_H;
		int dx = event->tfinger.dx * SCR_W;
		int dy = event->tfinger.dy * SCR_H;
#else
	case SDL_MOUSEMOTION:
	{
		int x = event->motion.x;
		int y = event->motion.y;
		int dx = event->motion.xrel;
		int dy = event->motion.yrel;
#endif
		//if (m_pressed && x > absPos.x && x < absPos.x + m_dimensions.x && y > absPos.y && y < absPos.y + m_dimensions.y)
		//{
		if (SDL_BUTTON(SDL_GetMouseState(nullptr, nullptr)) == SDL_BUTTON_LMASK)
		{
			onSwipe(x, y, dx, dy);
		}
			//return true;
		//}
	}
	}
	return false;
}





