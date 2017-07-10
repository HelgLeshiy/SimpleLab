#include "LogoState.h"
#include "RunState.h"

#include "../app.h"
#include "../prefs.h"
#include "../ResourceManager.h"

void LogoState::onInit(SDL_Renderer *renderer, SpriteFont *spriteFont)
{

}

void LogoState::onEvent(SDL_Event *event)
{
	switch (event->type)
	{
#ifdef _ANDROID_
	case SDL_FINGERDOWN:
	{
#else
	case SDL_MOUSEBUTTONDOWN:
	{
#endif
		m_appPtr->popState();
		m_appPtr->pushState(new RunState(m_appPtr));
		break;
	}
	}
}

void LogoState::onLoop(float deltaTime)
{
	switch (logoState)
	{
	case LogoStateType::INCREASE:
		logoTimer += 0.02 * deltaTime;
		if (logoTimer >= 1.f) logoState = LogoStateType::DECREASE;
		break;
	case LogoStateType::DECREASE:
		logoTimer -= 0.02 * deltaTime;
		if (logoTimer <= 0)
		{
			m_appPtr->popState();
			m_appPtr->pushState(new RunState(m_appPtr));
		}
		break;
	}
}

void LogoState::onRender(SDL_Renderer *renderer, SpriteFont *spriteFont)
{
	SDL_Texture *logoTexture = ResourceManager::getTexture(renderer, "data/textures/bigLogo.png");
	int logoW, logoH;

	SDL_QueryTexture(logoTexture, nullptr, nullptr, &logoW, &logoH);
	SDL_SetTextureBlendMode(ResourceManager::getTexture(renderer, "data/textures/bigLogo.png"), SDL_BLENDMODE_ADD);
	SDL_SetTextureAlphaMod(logoTexture, 255 * logoTimer);
	SDL_Rect foxRect;
	foxRect.x = 0;
	foxRect.w = SCR_W;
	SDL_RenderCopy(renderer, logoTexture, 0, &foxRect);
	//renderTexture(logoTexture, rnd, 0, SCR_H / 2 - logoH / 2, logoW, SCR_H / 2 + logoH / 2);
}

void LogoState::onExit()
{

}
