#pragma once

#include "Widget.h"

enum class LayoutState
{
	IDLE,
	SWIPE_LEFT,
	SWIPE_RIGHT
};

class Layout : public Widget
{
public:
	Layout(Widget *parent = nullptr) : Widget(parent) { }
	virtual ~Layout() { }

	void init(SDL_Texture *texture);

	virtual void render(SDL_Renderer *renderer, SpriteFont& spriteFont) override;

	void onSwipe(int x, int y, float dx, float dy);
	void onUpdate(float deltaTime) override;

protected:
	SDL_Texture *m_texture = nullptr;
	LayoutState layoutState = LayoutState::IDLE;
	float swipe = 0.f;
};