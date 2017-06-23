#pragma once

#include <SDL2/SDL.h>

#include <string>
#include <functional>
#include "../GUI/gfx.h"
#include "../SpriteFont.h"

class Widget
{
public:
	Widget(Widget *parent = nullptr) : m_parent(parent) { }
	virtual ~Widget() { }

	virtual void render(SDL_Renderer *renderer, SpriteFont& spriteFont) = 0;

	bool onEvent(SDL_Event *event);
	virtual void onUpdate(float deltaTime) { }

	void setRect(const vec2& pos, const vec2& dims) { m_position = pos; m_dimensions = dims; }
	void setInnerStartPosition(const vec2& pos) { m_innerStartPos = pos; }
	void move(const vec2& velocity) { m_position += velocity; }

	const vec2& getPosition() const { return m_position; }
	const vec2& getDimensions() const { return m_dimensions; }
	const vec2& getInnerStartPos() const { return m_innerStartPos; }

private:
	virtual void onTouch(int x, int y) { }
	virtual void onDetouch(int x, int y) { }
	virtual void onKeyDown(int key) { }
	virtual void onKeyUp(int key) { }
	virtual void onSwipe(int x, int y, float dx, float dy) { }
	virtual void onTextInput(const char *text) { }

protected:
	Widget *m_parent = nullptr;

	vec2 m_position;
	vec2 m_innerStartPos;
	vec2 m_dimensions;

	bool m_pressed = false;
};





