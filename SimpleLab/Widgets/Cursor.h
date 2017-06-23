#pragma once

class Cursor
{
public:
	Cursor();
	~Cursor();

	void update(float deltaTime);
	void goTo(int pos);
	int getPos() const { return m_pos; }
	bool show() const { return m_show; }

private:
	int m_pos = 0;
	float m_blink = 0.f;
	bool m_show = true;
};
