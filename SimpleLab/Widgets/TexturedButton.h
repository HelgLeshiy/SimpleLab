#pragma once

#include "SimpleButton.h"

class TexturedButton : public SimpleButton
{
public:
	TexturedButton(Widget *parent = nullptr) : SimpleButton(parent) { }
	virtual ~TexturedButton() { }

	void init(SDL_Texture *releaseTexture, SDL_Texture *pressTexture, std::function<void(void)> cbFunction = nullptr);
	void setText(const std::string& text, const ColorRGBA8& textColor);

	virtual void render(SDL_Renderer *renderer, SpriteFont& spriteFont) override;

protected:
	SDL_Texture *m_releaseTexture = nullptr;
	SDL_Texture *m_pressTexture = nullptr;
};