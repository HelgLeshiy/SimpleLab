#pragma once

#include <cmath>

struct vec2
{
	vec2() = default;
	vec2(float X, float Y) : x(X), y(Y) { }
	float x, y;
};

struct ColorRGBA8
{
	ColorRGBA8() : r(0), g(0), b(0), a(0) { }
	ColorRGBA8(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a = 0) : r(_r), g(_g), b(_b), a(_a) { }
	unsigned char r, g, b, a;
};

static vec2& operator+= (vec2& lhs, const vec2& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}

static vec2 operator+ (const vec2& lhs, const vec2& rhs)
{
	vec2 res(lhs.x + rhs.x, lhs.y + rhs.y);
	return res;
}

static float distance(const vec2& a, const vec2& b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
