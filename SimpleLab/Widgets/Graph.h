#pragma once

#include "Widget.h"
#include <vector>

class Namescope;

class Graph : public Widget
{
public:
	Graph(Widget *parent = nullptr) : Widget(parent) { }
	virtual ~Graph() { }

	void init(const std::string& expr, double start, double end, Namescope *ns);

	virtual void render(SDL_Renderer *renderer, SpriteFont& spriteFont) override;
	void onTouch(int x, int y) override;

protected:
	void createPoints(Namescope *ns);

protected:
	std::string m_expression;
	double m_start;
	double m_end;
	double m_h;

	std::vector<double> m_x, m_y;
};
