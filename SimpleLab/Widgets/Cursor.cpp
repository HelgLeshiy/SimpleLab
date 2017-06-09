#include "Cursor.h"
#include "../prefs.h"

Cursor::Cursor()
{
}


Cursor::~Cursor()
{
}

void Cursor::update(float deltaTime)
{
	m_blink += BLINK_SPEED * deltaTime;
	if (m_blink > 1.f)
	{
		m_show = !m_show;
		m_blink = 0.f;
	}
}

void Cursor::goTo(int pos)
{
	m_pos = pos;
}
