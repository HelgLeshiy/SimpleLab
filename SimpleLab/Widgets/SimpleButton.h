#pragma once

#include "Widget.h"

class SimpleButton : public Widget
{
public:
	SimpleButton(Widget *parent = nullptr) : Widget(parent) { }
	virtual ~SimpleButton() { }

	void init(const std::string& text, const ColorRGBA8& textColor,
		const ColorRGBA8& fillColor, const ColorRGBA8& pressColor,
		std::function<void(void)> cbFunction = nullptr);

	virtual void render(SDL_Renderer *renderer, SpriteFont& spriteFont) override;
	void onTouch(int x, int y) override;

protected:
	std::string m_text;
	ColorRGBA8 m_textColor;
	ColorRGBA8 m_fillColor;
	ColorRGBA8 m_pressColor;

	std::function<void(void)> m_cbFunction;
};
