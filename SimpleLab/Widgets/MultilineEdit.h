#pragma once
#include <list>
#include "Widget.h"
#include "Cursor.h"

class MultilineEdit : public Widget
{
public:
	MultilineEdit(Widget *parent = nullptr);
	~MultilineEdit();

	void init(int symbolWidth, int symbolHeight);
	void writeLine(const std::string& text = "");
	void insertToCursor(const std::string& text);
	void onUpdate(float deltaTime) override;
	void onTouch(int x, int y) override;
	void onSwipe(int x, int y, float dx, float dy) override;
	void onTextInput(const char *text) override;
	void onKeyDown(int key) override;
	void render(SDL_Renderer *renderer, SpriteFont& font) override;
	const std::string& getLastLine() const;
	std::string& getLastLine();

	void shiftCursor(int n);

	std::list < std::string >::const_iterator begin() const { return m_lines.begin(); }
	std::list < std::string >::const_iterator end() const { return m_lines.end(); }

private:
	void slideLines();
	Cursor m_cursor;
	int m_symbolWidth;
	int m_symbolHeight;
	vec2 m_contentShift;
	bool m_pressed = false;

	std::list < std::string > m_lines;
};

