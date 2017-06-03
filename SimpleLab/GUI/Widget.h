#pragma once

#include <SDL2/SDL.h>

#include <string>
#include <functional>
#include "gfx.h"
#include "../SpriteFont.h"

class Widget
{
public:
	Widget(Widget *parent = nullptr) : m_parent(parent) { }
	virtual ~Widget() { }

	virtual void render(SDL_Renderer *renderer, SpriteFont& spriteFont) = 0;

	virtual void onEvent(SDL_Event *event) { }
	virtual void onUpdate(float deltaTime) { }

	void setRect(const vec2& pos, const vec2& dims) { m_position = pos; m_dimensions = dims; }
	void setInnerStartPosition(const vec2& pos) { m_innerStartPos = pos; }
	void move(const vec2& velocity) { m_position += velocity; }

	const vec2& getPosition() const { return m_position; }
	const vec2& getDimensions() const { return m_dimensions; }
	const vec2& getInnerStartPos() const { return m_innerStartPos; }

protected:
	Widget *m_parent = nullptr;

	vec2 m_position;
	vec2 m_innerStartPos;
	vec2 m_dimensions;
};

class SimpleButton : public Widget
{
public:
	SimpleButton(Widget *parent = nullptr) : Widget(parent) { }
	virtual ~SimpleButton() { }

	void init(const std::string& text, const ColorRGBA8& textColor,
		      const ColorRGBA8& fillColor, const ColorRGBA8& pressColor,
		      std::function<void(void)> cbFunction = nullptr);

	virtual void render(SDL_Renderer *renderer, SpriteFont& spriteFont) override;

	virtual void onEvent(SDL_Event *event) override;

protected:
	std::string m_text;
	ColorRGBA8 m_textColor;
	ColorRGBA8 m_fillColor;
	ColorRGBA8 m_pressColor;

	std::function<void(void)> m_cbFunction;

	bool m_pressed = false;
};