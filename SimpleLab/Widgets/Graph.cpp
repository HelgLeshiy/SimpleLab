#include "Graph.h"
#include "../Parser/Parser.h"
#include "../prefs.h"
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void Graph::init(const std::string& expr, double start, double end, Namescope *ns)
{
	m_expression = expr;
	m_start = start;
	m_end = end;
	m_h = (end - start) / 100.0;

	createPoints(ns);
}

void Graph::render(SDL_Renderer *renderer, SpriteFont& spriteFont)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Rect fillRect = { 0, 0, SCR_W, SCR_H };
	SDL_RenderFillRect(renderer, &fillRect);
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	double oldX = 0;
	double oldY = 0;
	double maxY = *std::max_element(m_y.begin(), m_y.end());
	double minY = *std::min_element(m_y.begin(), m_y.end());
	for (int i = 0; i < m_x.size(); ++i)
	{
		double newX = m_x[i] * ( SCR_W / (m_end - m_start)) - m_start * (SCR_W / (m_end - m_start));
		double newY = SCR_H - 0.5 * (m_y[i] * ( SCR_H / (maxY - minY)) - minY * 0.5 * (SCR_H / (maxY - minY)) + SCR_H / 2);
		SDL_RenderDrawLine(renderer, oldX, oldY, newX, newY);
		oldX = newX;
		oldY = newY;
	}
}

void Graph::onTouch(int x, int y)
{

}

void Graph::createPoints(Namescope *ns)
{
	Namescope *local = new Namescope(ns);
	Parser parser;
	parser.operatorMapInit();

	for (double x = m_start; x < m_end; x += m_h)
	{
		m_x.push_back(x);
		local->setVar(std::make_shared<TypedValue<double>>(x), "x");
		m_y.push_back(parser.parse(m_expression, local));
	}
	delete local;
}
